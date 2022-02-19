#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//Problem Link:http://codeforces.com/contest/1625/problem/D
//O(n*max(log(arr[i])))
typedef long long ll;
int n, k;

struct node {
    node* left=NULL;
    node* right=NULL;
    int mx;
    int index;
};

typedef struct node node;
int main() {
    scanf("%d%d", &n, &k);
    if (k == 0) {
        printf("\n %d \n", n);
        for (int i = 0; i < n; i++)
            printf("%d ", i + 1);

        return 0;
    }
    
    vector<pair<int,int>> arr(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i].first), arr[i].second = i;

    sort(arr.begin(), arr.end());
    vector<pair<int, int>> dp(n,{1,-1});
    int index = -1;
    int mx = 0;
    node* root = new node();
    int logmax = 30;
    int mnbit = 1;
    while (!(k & mnbit))
        mnbit = mnbit << 1;
    for (int i = 0; i < n; i++) {
        node* current = root;
        for (int j = 0,m=1<< logmax; j <= logmax; j++,m=m>>1) {
            if (k & m) {
                if (arr[i].first & m) {
                    if (current->left != NULL) {
                        if (m == mnbit) {
                            if (dp[i].first < current->left->mx + 1) {
                                dp[i].first = current->left->mx + 1;
                                dp[i].second = current->left->index;
                                if (mx < dp[i].first) {
                                    mx = dp[i].first;
                                    index = i;
                                }
                            }
                        }
                        current = current->left;
                        

                    }
                    else break;

                }
                else {
                    if (current->right != NULL) {
                        if (m == mnbit) {
                            if (dp[i].first < current->right->mx + 1) {
                                dp[i].first = current->right->mx + 1;
                                dp[i].second = current->right->index;
                                if (mx < dp[i].first) {
                                    mx = dp[i].first;
                                    index = i;
                                }
                            }
                        }
                        current = current->right;
                    }
                    else break;
                }
               
            }
            else {
                if (arr[i].first & m) {
                    if (current->left != NULL) {
                        
                        if (dp[i].first < current->left->mx+1) {
                            dp[i].first = current->left->mx+1;
                            dp[i].second = current->left->index;
                            if (mx < dp[i].first) {
                                mx = dp[i].first;
                                index = i;
                            }
                        }
                       
                    }
                    if (current->right != NULL)
                        current = current->right;
                    else break;
                }
                else {
                    if (current->right != NULL) {
                        if (dp[i].first < current->right->mx + 1) {
                            dp[i].first = current->right->mx + 1;
                            dp[i].second = current->right->index;
                            if (mx < dp[i].first) {
                                mx = dp[i].first;
                                index = i;
                            }
                        }
                        
                    }
                    if (current->left != NULL)
                        current = current->left;
                    else break;
                }
                
            }
        }
        current = root;
        for (int j = 0, m = 1 << logmax; j <= logmax; j++, m = m >> 1) {
            if (arr[i].first & m) {
                if (current->right != NULL) {
                    current = current->right;
                    if(current->mx<dp[i].first){
                        current->mx = dp[i].first;
                        current->index = i;
                    }
                    
                }
                else {
                    current->right = new node();
                    current = current->right;
                    current->mx = dp[i].first;
                    current->index = i;
                }
            }
            else {
                if (current->left != NULL) {
                    current = current->left;
                    if (current->mx < dp[i].first) {
                        current->mx = dp[i].first;
                        current->index = i;
                    }

                }
                else {
                    current->left = new node();
                    current = current->left;
                    current->mx = dp[i].first;
                    current->index = i;
                }
            }

        }
        
    }


    if (mx == 0) {
         printf("\n -1");
    }
    else {
        printf("\n %d \n", mx);
        while (index != -1) {
           printf("%d ", arr[index].second+1);
          index = dp[index].second;
        }

    }
    return 0;
}
