#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: https://codeforces.com/contest/1567/problem/F
//O(n*m)
using namespace std;
typedef long long ll;
vector<vector<char>> grid;
vector<vector<bool>> visited;
vector<bool> visited1;
vector<int> color;
vector<vector<int>> GridIndexing;
vector<set<int>> graph;
vector<int> connectedComponentIndize;
int n,m,t,q;
int index = 0;
bool bad;
void dfs(int i,int currentcolor) {
    if (!bad) {
        visited1[i] = true;
        color[i] = currentcolor ^ 3;
        for (auto it : graph[i]) {
            if (bad)break;
            if (color[i] == color[it]) {
                cout << "NO" << endl;
                bad = true;
                break;
            }
            else if (!visited1[it])
                dfs(it, color[i]);
        }

    }
}

void findConnectedComponents(int x1, int x2) {
  
        visited[x1][x2] = true;
        GridIndexing[x1][x2] = index;
        if (x1 + 1 < n && grid[x1+1][x2] == '.' && !visited[x1+1][x2])
            findConnectedComponents(x1 + 1, x2);
        if (x2 + 1 < m && grid[x1][x2+1] == '.' && !visited[x1][x2+1])
            findConnectedComponents(x1, x2 + 1);
        if (x1 - 1>=0 && grid[x1-1][x2] == '.' && !visited[x1-1][x2])
            findConnectedComponents(x1 - 1, x2);
        if (x2 - 1 >= 0 && grid[x1][x2-1] == '.' && !visited[x1][x2-1])
            findConnectedComponents(x1, x2 - 1);
        if (x1 + 1 < n&&x2+1<m && grid[x1 + 1][x2+1] == '.' && !visited[x1 + 1][x2+1])
            findConnectedComponents(x1 + 1, x2+1);
        if (x1 - 1 >= 0 && x2 + 1<m && grid[x1-1][x2 + 1] == '.' && !visited[x1-1][x2 + 1])
            findConnectedComponents(x1-1, x2 + 1);
        if (x1 + 1 < n && x2 - 1>=0 && grid[x1 + 1][x2-1] == '.' && !visited[x1 + 1][x2-1])
            findConnectedComponents(x1 + 1, x2-1);
        if (x1 - 1 >= 0 && x2 - 1 >= 0 && grid[x1-1][x2 - 1] == '.' && !visited[x1-1][x2 - 1])
            findConnectedComponents(x1-1, x2 - 1);
    
}

   int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    grid = vector<vector<char>>(n, vector<char>(m));
   
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
     bad = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'X') {
                int check = (grid[i][j - 1] == '.') + (grid[i][j + 1] == '.') + (grid[i - 1][j] == '.') + (grid[i + 1][j] == '.');
                if (check == 1 || check == 3) {
                    cout << "NO" << endl, bad = true;
                    j = m, i = n;
                }
                
            }
        }
    }
    if (bad == false) {
        visited= vector<vector<bool>>(n, vector<bool>(m,false));
        GridIndexing = vector<vector<int>>(n, vector<int>(m, 0));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == '.') {
                    
                    findConnectedComponents(i, j);
                    index++;
                    
                }
            }
        }
        graph = vector<set<int>>(index);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'X') {
                    bool horizontal = (grid[i + 1][j] == '.') && (grid[i - 1][j] == '.');
                    bool vertical = (grid[i][j+1] == '.') && (grid[i][j-1] == '.');
                    if (horizontal && GridIndexing[i + 1][j] != GridIndexing[i - 1][j]) {
                        graph[GridIndexing[i + 1][j]].insert(GridIndexing[i - 1][j]);
                        graph[GridIndexing[i - 1][j]].insert(GridIndexing[i + 1][j]);
                    }

                    if (vertical && GridIndexing[i][j + 1] != GridIndexing[i][j - 1]) {
                        graph[GridIndexing[i][j-1]].insert(GridIndexing[i][j+1]);
                        graph[GridIndexing[i][j+1]].insert(GridIndexing[i][j-1]);
                    }
                }
            }

        }
        visited1 = vector<bool>(index);
        color = vector<int>(index);
       
            dfs(0,2);
        
        if (bad == false) {
            cout << "YES" << endl;
            vector<vector<int>>ans (n, vector<int>(m, 0));
            int lastColor=0;
            int lastValue = 0;
                for (int j = 0; j < m; j++) {
                    for (int i = 0; i < n; i++) {
                       
                            if (grid[i][j] == '.') {
                                if (i == 0) {
                                    lastColor = color[GridIndexing[i][j]];
                                    if (j % 2 == 0)
                                        ans[i][j] = 4, lastValue = 4;
                                    else
                                        ans[i][j] = 1, lastValue = 1;
                                }
                                else {
                                    if (lastColor == color[GridIndexing[i][j]]) {
                                        ans[i][j] = lastValue;
                                        lastColor = color[GridIndexing[i][j]];
                                    }
                                    else {
                                        lastValue = (lastValue == 1) ? 4 : 1;
                                        ans[i][j] = lastValue;
                                        lastColor = color[GridIndexing[i][j]];
                                    }
                                }
                            }
                        }
                    
                }
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        if (grid[i][j] == 'X') {
                            if (grid[i - 1][j] == '.') { ans[i][j] += ans[i - 1][j]; }
                            if (grid[i + 1][j] == '.') { ans[i][j] += ans[i + 1][j]; }
                            if (grid[i][j - 1] == '.') { ans[i][j] += ans[i][j - 1]; }
                            if (grid[i][j + 1] == '.') { ans[i][j] += ans[i][j + 1]; }
                        }
                    }
                }
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        cout << ans[i][j] << ' ';
                    }
                    cout << endl;
                }
            
        }


    }
      
    
       
    

}