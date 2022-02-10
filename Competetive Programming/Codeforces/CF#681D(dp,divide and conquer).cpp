#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//Author:Max Paris
//O(k*n*log(n))
//Problem Link:http://codeforces.com/contest/1442/problem/D
int n, k;
vector<vector<int>> arr;
vector<ll> sum;
vector<ll> knappsack;
ll ans = 0;

void calc(vector<ll>& nums, int size, ll sum1) {

   for (int i = k - size-1; i >= 0; i--) {
       nums[i + size] = max(nums[i + size], sum1 + nums[i]);
    }
    
    
        nums[size - 1] = max(nums[size - 1], sum1);
}



void recur(int l, int r,vector<ll>&knappsack) {
    if (l >= r)
        return;
    else if (r - l == 1) {
        ll sum1 = 0;
        for (int i = 0; i < arr[l].size(); i++) {
            sum1 += arr[l][i];
            knappsack[k-1] = max(knappsack[k-1], sum1 + ((k-i-2==-1)?0:knappsack[k - i-2]));
            ans = max(ans, knappsack[k-1]);
        }
    }
    else {
        int mid = l + (r - l) / 2;
        vector<ll> curr = knappsack;
        for (int i = l; i < mid; i++)
            calc(curr, arr[i].size(), sum[i]);
      
        recur(mid, r,curr);

        for (int i = mid; i < r; i++)
            calc(knappsack, arr[i].size(), sum[i]);

        recur(l, mid, knappsack);

    }
}

int main() {
    scanf("%d%d", &n, &k);
    arr = vector<vector<int>>(n);
    sum = vector<ll>(n);
    vector<ll>knappsack(k);
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        arr[i] = vector<int>(min(t, k));
        ll sum1 = 0;
        for (int j = 0; j < t; j++) {
            int x;
            scanf("%d", &x);
            if (j < k) {
                sum1 += x;
                arr[i][j] = x;
            }

        }
        sum[i] = sum1;
    }
   
    recur(0, n, knappsack);


    printf("%lld\n", ans);


    return 0;
}