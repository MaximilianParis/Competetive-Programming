#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: http://codeforces.com/problemset/problem/9/D
using namespace std;
typedef long long ll;


ll dp(vector<vector<vector<ll>>>& cntBinaryTrees,int n,int h1,int h,int k){
    if (n <= 1)
        cntBinaryTrees[n][h1][k] = 1;
    else if (n == 2)
        cntBinaryTrees[n][h1][k] = 2;
   
    else if(cntBinaryTrees[n][h1][k] ==-1){
        cntBinaryTrees[n][h1][k] = 0;
        for (int i = 1; i <= n; i++) {
            if ((i - 1 >= h - 1 || n - i >= h - 1) && k == 1) {
                if (i - 1 >= h - 1 && n - i >= h - 1) {
                    cntBinaryTrees[n][h1][k] +=
                        dp(cntBinaryTrees, i - 1, h1 - 1, 0, 0) * dp(cntBinaryTrees, n - i, h1 - 1, h - 1, 1)
                        + dp(cntBinaryTrees, i - 1, h1 - 1, h - 1, 1) * 
                        (dp(cntBinaryTrees, n - i, h1 - 1, 0, 0)- dp(cntBinaryTrees, n - i, h1 - 1, h - 1, 1));

                }
                else if (i - 1 < h - 1)
                    cntBinaryTrees[n][h1][k] += dp(cntBinaryTrees, i - 1, h1 - 1, 0, 0) * dp(cntBinaryTrees, n - i, h1 - 1, h - 1, 1);
                else if (n - i < h - 1)
                    cntBinaryTrees[n][h1][k] += dp(cntBinaryTrees, i - 1, h1 - 1, h - 1, 1) * dp(cntBinaryTrees, n - i, h1 - 1, 0, 0);
               
            }
            else if (k == 0)
                cntBinaryTrees[n][h1][k] +=
                dp(cntBinaryTrees, i - 1, h1 - 1, h - 1, 0) *
                dp(cntBinaryTrees, n - i, h1 - 1, h - 1, 0);
          
            

        }
    }
    return cntBinaryTrees[n][h1][k];
}






int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, h;
    cin >> n>>h;
    vector<vector<vector<ll>>> cntBinaryTrees(n + 1, vector<vector<ll>>(n + 1, vector<ll>(2,-1)));
    
    cout << dp(cntBinaryTrees, n,n,h,1) << endl;
}