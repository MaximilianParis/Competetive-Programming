#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: http://codeforces.com/problemset/problem/372/B
using namespace std;
typedef long long ll;
vector<vector<char>> grid;
int n, m, q, r1, r2, c1, c2;
vector<vector<int>> countAbove;
vector<vector<vector<vector<int>>>> answers;
vector<int>SegmentTree;
vector<int>arr;
int getMiddle(int l, int r) {

    return l + (r - l) / 2;

}

int getMaxUtil(int begin, int end, int& l, int& r, int pos)
{

    if (l <= begin && r >= end) {


        return SegmentTree[pos];
    }
    if (end < l || begin > r)return -1;

    int mid = getMiddle(begin, end);
    return max(getMaxUtil(begin, mid, l, r, 2 * pos + 1),
        getMaxUtil(mid + 1, end, l, r, 2 * pos + 2));

}
int update_value_util(int l, int r, int& index, int& newValue, int pos) {
    if (index >= l && r >= index) {



        if (l != r) {
            int mid = getMiddle(l, r);
            int val1 = update_value_util(l, mid, index, newValue, 2 * pos + 1);
            int val2 = update_value_util(mid + 1, r, index, newValue, 2 * pos + 2);

            SegmentTree[pos] = max(val1, val2);

        }
        else
            SegmentTree[pos] = newValue;
    }
    return SegmentTree[pos];
}
void update_value(int n, int index, int newValue) {

    if (arr[index] != newValue) {
        arr[index] = newValue;
        update_value_util(0, n - 1, index, newValue, 0);
    }
}
void initSegementTree() {
    arr = vector<int>(m);
    int pow = round(log2(m));
    int size = (2 << (pow + 1)) - 1;
    SegmentTree = vector<int>(size, -1);
}


void getCountAbove(vector<int>& count) {
    //O(m*n*log(m))
    for (int k = 0; k < m; k++) {
        if (k == 0) {
            //einspaltig
              for (int i = 0; i < n; i++) {
                if (grid[i][k] == '0') {
                   count[i] = 1;
                           
                }
                else {
                  count[i] = 0;
                }
            }
        }
        else {
            int lasti = -1;
            for (int i = 0; i < n; i++) {
                

                int cnt1 = 0;
              
                
                
               
                if (grid[i][k - 1] == '0' && grid[i][k] == '0') {
                    int l = 0;
                    int r = count[i]-1;
                    int index = max(lasti, getMaxUtil(0, m - 1, l, r, 0));

                    countAbove[i][k] = i - 1 - index;
                    count[i]++;
                    if(i<n-1)
                    update_value(m, count[i] - 2, i);
                }
                else if (grid[i][k] == '1') {
                    
                    for (int j = lasti+1; j < i; j++)
                        update_value(m, count[j] - 2, -1);
                    count[i] = 0, lasti = i;
                }
                else {
                    for (int j = lasti+1; j < i; j++)
                        update_value(m, count[j] - 2, -1);
                    count[i] = 1, lasti = i;
                }
            }
            for (int j = lasti+1; j <= n - 1; j++)
                update_value(m, count[j] - 2, -1);
        }
    }
    
}
//berechnet Alle möglichen Queries
void precompute(vector<int>& count, vector<int>& prevSum) {
    //O(n*n*m*m)
    for (int r = 0; r < m; r++){
        for (int l = 0; l < n; l++) {
            for (int k = r; k <= m - 1; k++) {
                if (k == r) {
                  
                    int cnt = 0;
                    for (int i = l; i <= n - 1; i++) {
                        if (grid[i][k] == '0') {
                            cnt++, count[i] = 1;
                            
                            if (i > 0)
                                answers[r][l][k][i] = cnt + answers[r][l][k][i - 1];
                            else
                                answers[r][l][k][i] = cnt;
                        }
                        else {
                         
                            if(i>0)
                            answers[r][l][k][i] =answers[r][l][k][i - 1];
                           

                            cnt = 0, count[i] = 0;
                        }
                    }

                }
                else {

                   
                    int cnt = 0;
                  
                    ll sum = 0;

                    int lasti = l - 1;
                    for (int i = l; i <= n - 1; i++) {
                        if (grid[i][k - 1] == '0' && grid[i][k] == '0') {


                            cnt++;
                           
                           
                            if (sum > 0 && count[i] < count[i - 1] - 1) {
                                int consecutiveAbove = countAbove[i][k];
                                int index = i - 1 - consecutiveAbove;
                                if (index > lasti)
                                    sum = count[i] * consecutiveAbove + prevSum[index];
                                else
                                    sum = count[i] * min(i - lasti - 1, consecutiveAbove);

                            }
                            sum += count[i];
                            prevSum[i] = sum;
                            count[i]++;

                           
                           

                        }
                        else if (grid[i][k] == '1') {
                            lasti = i;
                            sum = 0;
                            count[i] = 0;
                            cnt = 0;
                            prevSum[i] = 0;

                        }
                        else if (grid[i][k - 1] == '1' && grid[i][k] == '0') {
                            prevSum[i] = 0;
                            lasti = i;
                            sum = 0;
                            cnt++;
                           
                            count[i] = 1;

                        }
                        
                        if (k > 0 && i > 0)
                            answers[r][l][k][i] = sum + cnt + answers[r][l][k - 1][i] + answers[r][l][k][i - 1] - answers[r][l][k - 1][i - 1];
                        else if (k > 0)              
                            answers[r][l][k][i] = sum + cnt + answers[r][l][k - 1][i];
                        else if(i>0)
                            answers[r][l][k][i] = sum + cnt + answers[r][l][k][i - 1];
                    }


                }
            }
        }
}

}
          
   int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> q;


    grid = vector<vector<char>>(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            cin >> grid[i][j];
        }
    }
    answers=vector<vector<vector<vector<int>>>>(m, vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(n))));
    countAbove= vector<vector<int>>(n, vector<int>(m));
    vector<int>prevSum(n);
    vector<int> cnt(n);
    vector<ll> query(q);
    initSegementTree();
    getCountAbove(cnt);
    precompute(cnt, prevSum);
    for (int i = 0; i < q; i++) {
        cin >> r1 >> c1 >> r2 >> c2;
        r1--, r2--, c1--, c2--;
        
       
        query[i] = answers[c1][r1][c2][r2];
    }
    
    for (int i = 0; i < q; i++)
        cout << query[i] << endl;

}
