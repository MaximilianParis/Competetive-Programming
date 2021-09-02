#include<bits/stdc++.h>
#include<unordered_map>
//Author: Max Paris
//Problem Link: https://codeforces.com/problemset/problem/337/D

using namespace std;
typedef long long ll;
int n, m, d;

vector<vector<int>> graph;
vector<bool> pi;
vector<int> DistDown;
vector<int> DistUp;


void dfs2(int pos, int parent = -1) {

    int max1 = -1, max2 = -1;
    for (auto it : graph[pos]) {
        if (it != parent) {
            int x1 = max((DistDown[it] > 0) ? DistDown[it] + 1 : 0, int(pi[it]));
            if (x1 > max1) {
                max2 = max1;
                max1 = x1;
            }
            else if (x1 > max2)
                max2 = x1;
        }
    }

    for (auto it : graph[pos]) {
        if (it != parent) {
            int DistIt = max((DistDown[it] > 0) ? DistDown[it] + 1 : 0,int(pi[it]));
            if (DistIt != max1 ) {
                int x1 =(DistUp[pos]>0)? DistUp[pos] +1:0;
                int x2 = int(pi[pos]);
                int x3 = (max1 > 0) ? max1 + 1 : 0;
                DistUp[it] = max(x1,max(x2,x3));
            }
              
            else  {
                int x1 = (DistUp[pos] > 0) ? DistUp[pos] + 1 : 0;
                int x2 = int(pi[pos]);
                int x3 = (max2 > 0) ? max2 + 1 : 0;
                DistUp[it] = max(x1, max(x2, x3));
            }
               
           
        }
    }
    for (auto it : graph[pos])
        if (it != parent)
            dfs2(it, pos);
}
   
void dfs1(int pos,int parent=-1) {
   

    for (auto it : graph[pos]) {
        if (it != parent) {
            dfs1(it, pos);
            if (DistDown[it] > 0 || pi[it])
                DistDown[pos] = max(DistDown[pos], 1 + DistDown[it]);
        }
        
    }
  
   
}

int main() {
   
    cin >> n >> m >> d;
    pi=vector<bool> (n);
    DistDown = vector<int>(n);
    DistUp = vector<int>(n);
   
    graph = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        int val;
        cin >> val;
        pi[val-1]=true;
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs1(0);
   
    dfs2(0);
    int ans = 0;
 
    for (int i = 0; i < n; i++) {
       if(DistDown[i]<=d&& DistUp[i] <= d)
            ans++;
    }
    cout << ans << endl;
}