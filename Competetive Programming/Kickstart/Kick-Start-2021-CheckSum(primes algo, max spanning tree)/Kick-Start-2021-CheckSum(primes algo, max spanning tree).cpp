#include <bits/stdc++.h>
//Author: Max Paris
// Problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000436140/000000000068c2c3
using namespace std;
typedef long long ll;
vector<vector<int>> matrix;

int n;
ll ans;
int sum;


          
               





vector<vector<int>> adj; // adjacency matrix of graph
const int INF = -1000000000; // weight INF means there is no edge

struct Edge {
    int w = INF, to = -1;
};

int prim() {
    int total_weight = 0;
    vector<bool> selected(n, false);
    vector<Edge> min_e(n);
    min_e[0].w = 0;

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!selected[j] && (v == -1 || min_e[j].w > min_e[v].w))
                v = j;
        }

        if (min_e[v].w == INF) {
            cout << "No MST!" << endl;
            exit(0);
        }

        selected[v] = true;
        total_weight += min_e[v].w;
        

        for (int to = 0; to < n; ++to) {
            if (adj[v][to] > min_e[to].w)
                min_e[to] = { adj[v][to], v };
        }
    }

    return sum-total_weight;
}


        
    




int main() {

    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {

        cin >> n;
      
        sum = 0;
        ans = 0;
       
        matrix = vector<vector<int>>(n, vector<int>(n));
        int cnt = 0;
       
        vector<int> numberingRow(n,-1);
        vector<int> numberingColumn(n, -1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matrix[i][j];
                if (matrix[i][j] == -1) {
                    if (numberingRow[i] == -1) {
                      
                        numberingRow[i] = cnt;
                        cnt++;
                    }
                  

                    if (numberingColumn[j] == -1) {
                      
                        numberingColumn[j] = cnt;
                        cnt++;
                    }
                  
                }
                   

            }
        }
        adj = vector<vector<int>>(cnt, vector<int>(cnt, (0)));
       
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val;
                cin >> val;
               
                if (matrix[i][j] == -1) {
                    int x1 = 0, x2 = 0;
                     x1 = numberingRow[i];

                    x2 = numberingColumn[j];

                 
                    adj[x1][x2] = val;
                    adj[x2][x1] = val;
                    sum += val;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
        }
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
        }
       
               
        n = cnt;
        cout << "Case #" << tc << ": ";
        if(n>0)
        cout << prim();
        else 
        cout <<0;

        cout << endl;
    }


    return 0;
}
