#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//Problem Link:https://codeforces.com/blog/entry/58210
//O(n*k^2 +m*n*k)
typedef long long ll;
int n, k, l, m,t;
void recurr(int i, int j, vector<vector<int>>& dp, vector<vector<int>>& lessons, vector<vector<int>>& dp1) {
  
    int r = lessons[i].size() - 1;
    dp[i][j] = 1e9;
    for (int s = j; s >= 0; s--) {
        if(i-1>=0&&dp[i-1][s]==-1)
        recurr(i - 1, s, dp, lessons,dp1);
        int diff = j - s;
        dp[i][j] = min(dp[i][j], ((i-1>=0)?dp[i - 1][s]:0) + dp1[i][diff]);
    }

}

int main() {
    scanf("%d%d%d", &n,&m,&k);
    vector<vector<int>> lessons(n);
    for (int i = 0; i < n; i++) {
        char c;
        scanf("%c", &c);
        for (int j = 0; j < m; j++) {
            
            scanf("%c", &c);
            if (c == '1')
                lessons[i].push_back(j);
        }
    }
    vector<vector<int>> dp(n, vector<int>(k+1,-1));
    vector<vector<int>> dp1(n, vector<int>(k + 1, 1e9));
    for (int i = 0; i < n; i++) {
        int r = lessons[i].size() - 1;
        dp1[i][0] = ((r>=0)?lessons[i][r] - lessons[i][0] + 1:0);
        for (int j = 1; j <= k; j++) {
            if (j >= r + 1)
                dp1[i][j] = 0;
            else {
                int window = r  - j;
                for (int s = 0; s + window <= r; s++) {
                    dp1[i][j] = min(dp1[i][j], lessons[i][s+window] - lessons[i][s] + 1);
                }
            }
        }
    }
    recurr(n - 1, k, dp, lessons,dp1);
    printf("%d\n", dp[n - 1][k]);
    return 0;
}