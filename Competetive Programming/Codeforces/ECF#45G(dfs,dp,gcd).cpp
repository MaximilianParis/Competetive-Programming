#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//O(MaxN*log(MaxN)) only if there are not to many duplicate values, because dfs gets expensive then
//Problem Link:https://codeforces.com/contest/990/my
typedef long long ll;
ll n;
vector<pair<int, vector<int>>> graph;
int p;
vector<ll> ans;
int MaxN = 2e5;


vector<bool> visited;

ll cnt = 0;
ll sum = 0;

void dfs(int pos) {
    if (visited[pos] || graph[pos].first % p != 0)
        return;
    visited[pos] = true;
    cnt++;
    for (int it : graph[pos].second) {
        dfs(it);
    }


}





int main() {

    scanf("%d", &n);

    graph = vector<pair<int, vector<int>>>(n);
    vector<vector<int>> arr(MaxN + 1);
    visited = vector<bool>(n);
    ans = vector<ll>(MaxN + 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &graph[i].first);
        arr[graph[i].first].push_back(i);
    }

    for (int i = 0; i < n - 1; i++) {
        int x1, x2;
        scanf("%d%d", &x1, &x2);
        x1--, x2--;
        graph[x1].second.push_back(x2);
        graph[x2].second.push_back(x1);
    }
    if (n == 1)
        printf("%d %d\n", graph[0].first, 1);
    else {
        //calc();
        for (int i = MaxN; i >= 2; i--) {
            p = i;
            for (int j = i; j <= MaxN; j += i) {
                for (int it : arr[j]) {
                    cnt = 0;
                    dfs(it);
                    visited[it] = false;
                    if (cnt > 1)
                        ans[i] += cnt * (cnt - 1) / 2;
                }
            }
            for (int j = i * 2; j <= MaxN; j += i)
                ans[i] -= ans[j];

            sum += ans[i];
        }
        ans[1] = n * (n - 1) / 2 - sum;
        printf("\n");
        for (int i = 1; i <= MaxN; i++) {
            if (ans[i] + arr[i].size() > 0) {
                printf("%d %lld\n", i, ans[i] + arr[i].size());
            }
        }
    }
    return 0;
}