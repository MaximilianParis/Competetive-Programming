#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int dp[1001][1001][2];
int n;
int mod = 1e9 + 7;

int solve(int pos,int k, int dir,bool unique) {
    if (k == 1)return 1;
    else if (dir == 0 && n == pos)return unique;
    else if (dir == 1 && pos == 0)return unique;
    else if (dp[pos][k][dir] != -1)
        return dp[pos][k][dir] + unique;
    else {
        dp[pos][k][dir] = (solve(pos, k - 1, 1 - dir,true) + solve(pos + (dir == 0 ? 1 : -1), k, dir,false)) % mod;
            return dp[pos][k][dir]+unique;
    }




}





int main() {
    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> n >> k;
        memset(dp, -1, sizeof(dp));
        cout << solve(0, k, 0,true) << endl;
   }
       
    

   
}