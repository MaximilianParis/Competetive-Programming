#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Problem Link: https://codeforces.com/contest/1400/problem/E
//Author: Max Paris
//O(n*log(n))

int n, M, K;
vector<vector<pair<int,int>>> minima;
ll logofn;
ll ans;
ll value;
double cnt = 0;

pair<int, int> getMin(int l, int r) {
    ll diff = r - l + 1;

    ll log2diff = log2(diff);
    return min(minima[l][log2diff], minima[r - (1 << log2diff) + 1][log2diff]);



}
void precompute() {
    ll val = 1;
    for (int j = 1; j < logofn; j++) {

        for (int i = 0; i + val < n; i++) {

            minima[i][j] = min(minima[i][j - 1], minima[i + val][j - 1]);

        }
        val = val << 1;
    }
}

ll dp(int l, int r, int lastMin) {
    ll ans = 0;
   
    int l1, r1;
    l1 = l;
    r1 = l;
    int currMin = 1e9;
    while(r1<r)  {
        pair<int, int> minElement = getMin(l1, r-1);
        if(l1==l)
        currMin = minElement.first;
        if (currMin == minElement.first) {
            r1 = minElement.second;
            if(r1-l1>0)
            ans+=dp(l1, r1, currMin);
            l1 = r1;
            while (l1<r&&minima[l1][0].first == currMin)
                l1++;
            r1 = l1;

        }
        else {
            r1 = r;
            if (r1 - l1 > 0)
            ans+=dp(l1, r1, currMin);
        }
    }
   


    return min(1ll * r - l, ans + currMin - lastMin);



}


int main()
{
    cin >> n;

    logofn = log2(n) + 1;
    minima = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(logofn,{1e9,0}));
    for (int i = 0; i < n; i++) {
        cin >> minima[i][0].first;
        minima[i][0].second = i;
    }
    precompute();

    cout << dp(0, n, 0) << endl;
    return 0;

}
