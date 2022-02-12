#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//O(MaxN*log(MaxN))
//Problem Link:https://codeforces.com/contest/1101/problem/D
typedef long long ll;
int n;
vector<pair<int, vector<int>>> graph;
int p;
int ans = 0;
int MaxN = 2e5;
int cntPrimeNums= 17984;
vector<int> primes(cntPrimeNums);
vector<bool> visited;
void calc() {
    int cnt = 0;
    vector<bool> values(MaxN+1);
    for (int i = 2; i <= 447; i++) {
        if (values[i] == false) {
            primes[cnt] = i;
            cnt++;
            for (int j = i * 2; j <= MaxN; j += i)
                values[j] = true;
        }
    }

    for (int i = 448; i <= MaxN; i++) {
        if (values[i] == false) {
            primes[cnt] = i;
            cnt++;
        }
    }
   

}
int dfs(int pos, int parent=-1) {
    if (graph[pos].first % p != 0||visited[pos])
        return 0;
    visited[pos] = true;
   
        int mx = 0;
        int mx1 = 0;
        for (int i : graph[pos].second) {
            if (i != parent) {
               int val= dfs(i, pos);
               if (val >= mx) {
                   mx1 = mx;
                   mx = val;
               }
               else if (val > mx1)
                   mx1 = val;


            }
        }
        ans = max(ans, mx + 1 + mx1);
        return mx + 1;
    

}





int main() {
    calc();
    scanf("%d", &n);

    graph = vector<pair<int,vector<int>>>(n);
    vector<vector<int>> arr(MaxN+1);
    visited = vector<bool> (n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &graph[i].first);
        arr[graph[i].first].push_back(i);
    }
                   
    for (int i = 0; i < n - 1; i++) {
        int x1,x2;
        scanf("%d%d", &x1, &x2);
        x1--, x2--;
        graph[x1].second.push_back(x2);
        graph[x2].second.push_back(x1);
   }
    if (n == 1 && graph[0].first == 1)
        printf("%d\n", 0);
    else if(n == 1)
        printf("%d\n", 1);
    else {
        for (int i = 0; i < primes.size(); i++) {
            p = primes[i];
            for (int i = p; i <= MaxN; i+=p) {
                for (int it : arr[i]) {
                    if(!visited[it])
                        dfs(it);

                    visited[it] = false;
                }
               
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}