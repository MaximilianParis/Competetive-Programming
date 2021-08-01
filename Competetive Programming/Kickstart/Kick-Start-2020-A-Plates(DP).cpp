


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll b;
vector<long double> factorial;

int main() {
    int tt;
    cin >> tt;
    for (int t = 1; t <= tt; t++) {
        ll ans = 0;
        int n, k,p;
        cin >> n >> k>>p;
        vector<vector<ll>> s(n, vector<ll>(k));
        vector<vector<ll>> sum(n, vector<ll>(k+1));
       
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                cin >> s[i][j];
                if (j == 0)sum[i][j] = s[i][j];
                else sum[i][j] = s[i][j] + sum[i][j-1];
           }
       }
        vector<vector<ll>> dp(n+1, vector<ll>(p+1));
       
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= p; j++) {
                if(i>0)
                dp[i][j] = dp[i - 1][j];
                for (int x = 1; x <= min(j, k); x++) {
                  if(i>0) dp[i][j] = max(dp[i][j], dp[i - 1][j - x] + sum[i][x-1]);
                  else  dp[i][j] = sum[i][x-1];
                  
                }
            }

        }

       
        cout << "Case #" << t << ": " <<dp[n-1][p] << endl;

    }
   
  
     
    return 0;
}
