#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//Problem Link:https://codeforces.com/problemset/problem/527/D
//O(n*log(n))
typedef long long ll;
int n, k, l, m,t;
void recurr(int index, vector<pair<int, int>>& segments,vector<int>& dp) {
    if (index>=n||dp[index] != 0)
        return;

    int j = lower_bound(segments.begin() + index + 1, segments.end(), make_pair(segments[index].second, 0)) - segments.begin();
    recurr(j, segments, dp);
    recurr(index+1, segments, dp);
    dp[index] = max(1 + ((j < n) ? dp[j] : 0),((index+1)<n? dp[index+1] :0));
}

int main() {
    scanf("%d", &n);
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        int x,w;
        scanf("%d%d", &x,&w);
        segments[i] = { x - w,x + w };
    }
    sort(segments.begin(), segments.end());
    vector<int>dp(n);
    recurr(0, segments, dp);
    printf("%d\n", dp[0]);
    return 0;
}