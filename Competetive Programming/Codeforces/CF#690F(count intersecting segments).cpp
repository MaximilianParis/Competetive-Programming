#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, q,t;
//O(n*Log(n))
//Problem Link:https://codeforces.com/problemset/problem/1462/F
int main(){
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<pair<int, int>> segments(n);
        vector<int> segmentsSortBegin(n);
        vector<int> segmentsSortEnd(n);
        for (int i = 0; i < n; i++) {
            int x1, x2;
            scanf("%d%d", &x1, &x2);
            segments[i]= { x1,x2 };
            segmentsSortBegin[i] =  x1;
            segmentsSortEnd[i] = x2;
        }
        sort(segmentsSortBegin.begin(), segmentsSortBegin.end());
        sort(segmentsSortEnd.begin(), segmentsSortEnd.end());
        int ans = 1e9;
        for (int i = 0; i < n; i++) {
            int x1 = lower_bound(segmentsSortEnd.begin(), segmentsSortEnd.end(), segments[i].first)- segmentsSortEnd.begin();
            int x2 = n-(lower_bound(segmentsSortBegin.begin(), segmentsSortBegin.end(), segments[i].second+1) - segmentsSortBegin.begin());
            ans = min(ans, x1 + x2);
        }
        printf("%d\n", ans);

    }
    
}