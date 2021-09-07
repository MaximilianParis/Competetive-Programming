#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: https://codeforces.com/problemset/problem/1446/C
//O(n)
using namespace std;
typedef long long ll;
vector<int> arr;
ll ans = 0;
int n,m,t,q;
ll dp(int bit,vector<int>& values) {
    if (values.size() == 1)
        return 1;
   
    int cntBitOn = 0;
    int cntBitOff = 0;
    int value = (1 << bit);
    for (auto it : values) {
        if ((it & value) == value) {
            cntBitOn++;
        }
        else
            cntBitOff++;

    }
   
       
        if (cntBitOn > 0 && cntBitOff > 0) {
            vector<int> BitOn(cntBitOn);
            vector<int> BitOff(cntBitOff);
            cntBitOn = 0;
            cntBitOff = 0;
            for (auto it : values) {
                if ((it & value) == value) {
                    BitOn[cntBitOn] = it, cntBitOn++;
                }
                else
                    BitOff[cntBitOff] = it, cntBitOff++;
            }

            ll y1 = dp(bit - 1, BitOn);
            ll y2= dp(bit - 1, BitOff);
            ll add = min(y1, y2) - 1;
            ans += add;
            return max(y1, y2) + 1;


        }
        else 
            return dp(bit - 1, values);
        
    
   
   
}



   int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    arr = vector<int>(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    dp(30, arr);
    cout << ans << endl;

}