#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris

typedef long long ll;
int n, k,l;


int main() {
    int n, s,N;
    scanf("%d", &n);
    if (n == 1)
        printf("%d", 0);
   
    vector<vector<int>> graph(n,vector<int>(n));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++)
              scanf("%d", &graph[i][j]);
       
    if (n == 2)
        printf("%d", graph[0][1]+ graph[1][0]);
    
    vector<vector<pair<int, int>>> dp((1 << (n - 1)), vector<pair<int, int>>(n, { 1e9,1e9 }));
   
    vector<int> prefix(n);
    prefix[0] = 1;
    for (int i = 1, j = 2; i < n; i++, j *= 2) {
        prefix[i] += prefix[i - 1] + j;
        dp[j>>1][i].first = graph[0][i];
        dp[j >> 1][i].second = 0;
    }
    vector<int> ans(n+1);
       
    
    int next = 1;
    for (int i = 1,k=2; i < n-1; i++,k*=2) {
        next += k;
        int bits = next;
        int count = 0;
        int potenz = 2;
       
        while (true) {
            for (int a = 1, curr = 1; a < n; curr *= 2, a++) {
                if ((bits & curr)) {
                    for (int m = 1,cur=1; m < n; m++,cur*=2) {
                        if (m != a&&(cur&bits)) {
                            pair<int, int> mn = { dp[bits - curr][m].first + graph[m][a],m };
                            dp[bits][a] = min(dp[bits][a], mn);
                        }
                    }
                }
            }
            if (count == n - i-2)
                break;
            if (!(bits & potenz)) {
                count++;
                bits += potenz>>1;
                potenz *= 2;

            }
            else {
                bits += (potenz >> 1);
                int cnt = __popcnt(bits);
                bits += prefix[i - cnt];
                potenz = 2;
                count = 0;
            }
        }
        if (i == n - 2) {
            pair<int, int> mn = { 1e9,1e9 };
            for (int j = 1; j < n; j++) {
                pair<int, int> curr = { dp[bits][j].first + graph[j][0],j };
                mn = min(mn, curr);
            }
            printf("\n%d", mn.first);
            for (int j = n - 1; j > 0; j--) {
                ans[j] = mn.second;
                mn = dp[bits][ans[j]];
                bits -= 1 << (ans[j] - 1);
            }
        }
    }
    return 0;
}