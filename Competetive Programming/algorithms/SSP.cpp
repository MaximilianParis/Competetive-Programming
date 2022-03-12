#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//O(m*log(log(N))+N+n)
typedef long long ll;
int n, k,l;

struct VanEmdeBoasTree {

    vector<VanEmdeBoasTree> childs;
    VanEmdeBoasTree* summary;
    int Tmax;
    int Tmin;
    int universe;
    int childsize;
    bool empty = false;



    VanEmdeBoasTree(int size) {
        Tmax = -1;
        Tmin = size;
        universe = size;
        if (universe > 2) {
            childsize = ceil(sqrt(universe * 1.0));

            summary = (new VanEmdeBoasTree(childsize));
            childs = vector<VanEmdeBoasTree>(childsize, NULL);

            for (int i = 0; i < childsize; i++)
                childs[i] = VanEmdeBoasTree(childsize);
        }
        else empty = true;
       

    }

    void insert(int x) {
        //Baum leer
        if (Tmin > Tmax) {
            Tmax = Tmin = x;
            return;
        }
        // wichtig nur Element größer als Tmin werden propagiert nach unten, deswegen
        //hier swap
        else if (x < Tmin) {
            swap(x, Tmin);
        }
        else if (x > Tmax)
            Tmax = x;
        else if (x == Tmax || x == Tmin)
            return;
        if (!empty) {
            int childIndex = x / childsize;
            int next = x % childsize;

            childs[childIndex].insert(next);
            if (childs[childIndex].Tmax == childs[childIndex].Tmin)
                summary->insert(childIndex);

        }
    }

    bool find(int x) {
        if (x == Tmin || x == Tmax)
            return true;
        else if (x < Tmin || x>Tmax)
            return false;
        else {
            int childIndex = x / childsize;
            int next = x % childsize;
            return childs[childIndex].find(next);
        }
    }

    void erase(int x) {
        if (Tmin == -1)
            return;
        if (x == Tmin && x == Tmax) {
            Tmax = -1;
            Tmin = universe;
            return;
        }
        else if (x == Tmin) {
            if (!empty) {
                int index = summary->Tmin;
                int value = childs[index].Tmin;
                x = Tmin = value + index * childsize;
            }
            else Tmin = Tmax;
        }
       
        if (!empty) {
            int childIndex = x / childsize;
            int next = x % childsize;

            childs[childIndex].erase(next);
            bool childEmpty = childs[childIndex].Tmax < childs[childIndex].Tmin;
            if (childEmpty)
                summary->erase(childIndex);

            if (x == Tmax) {
                if (childEmpty)
                    Tmax = Tmin;
                else {
                    int index = summary->Tmax;
                    int value = childs[index].Tmax;
                    Tmax = value + index * childsize;
                }
            }
        }
        else if (x == Tmax) 
            Tmax = Tmin;
        
           
        

    }

};

int main() {
    int n, s,m,N;
    scanf("%d%d%d%d", &n,&m, &s,&N);
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int x1, x2, x3;
        scanf("%d%d%d", &x1, &x2, &x3);
        graph[x1].push_back({ x2,x3 });
        graph[x2].push_back({ x1,x3 });
    }
    vector<int> cost(n, N);
    cost[s] = 0;
    VanEmdeBoasTree tree(N);
    
    vector<stack<int>> nodesMn(N);
    for (int i = 0; i < graph[s].size(); i++) {
        if(nodesMn[graph[s][i].second].empty())
        tree.insert(graph[s][i].second);
        nodesMn[graph[s][i].second].push(graph[s][i].first);
    }

    while (tree.Tmin!=N) {
        int mn = tree.Tmin;
        int cur = nodesMn[mn].top();
        nodesMn[mn].pop();
        if(nodesMn[mn].empty())
        tree.erase(mn);
        if (cost[cur] > mn) {
            cost[cur] = mn;
            int size = graph[cur].size();
            for (int j = 0; j < size; j++) {
                int newCost = cost[cur] + graph[cur][j].second;
                int index = graph[cur][j].first;
                if (newCost < cost[index]) {
                    if (nodesMn[newCost].empty())
                        tree.insert(newCost);

                    nodesMn[newCost].push(index);
                }
            }
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("%d ", cost[i]);

    return 0;
}