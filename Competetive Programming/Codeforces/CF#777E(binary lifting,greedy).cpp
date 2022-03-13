#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//O(log((max(a[i])-n)/cntZeroIndegree)*n)
//problem Link: https://codeforces.com/contest/1647/problem/E
typedef long long ll;
int n, k, l;
int K = 1;
struct VanEmdeBoasTree {


    vector<VanEmdeBoasTree> childs;
    VanEmdeBoasTree* summary;
    int Tmax;
    int Tmin;
    int universe;
    int childsize;
    bool empty = false;
    int size = 0;


    VanEmdeBoasTree(int size) {
        Tmax = -1;
        Tmin = size;
        universe = size;
        if (universe > 2) {
            childsize = ceil(sqrt(universe * 1.0));

            summary = (new VanEmdeBoasTree(childsize));
            childs = vector<VanEmdeBoasTree>(childsize,NULL);
            for (int i = 0; i < childsize; i++)
                childs[i] = VanEmdeBoasTree(childsize);
        }
        else empty = true;


    }
    int lower_bound(int x) {
        if (Tmax < Tmin)
            return -1;
        else if (x <= Tmin)
            return Tmin;
        else if (Tmax == x)
            return x;
        else if (empty && Tmax > x)
            return Tmax;
        else if (x > Tmax)
            return -1;
        else if (!empty) {
            int childIndex = x / childsize;
            int next = x % childsize;

            if (childs[childIndex].Tmax >= next) {
                return childs[childIndex].lower_bound(next) + childsize * childIndex;
            }

            else {
                int index = summary->lower_bound(childIndex);
                if (index != -1) {
                    return childsize * index + childs[index].Tmin;
                }
            }
        }

        return -1;
    }

    void insertSize(int x) {
        if (!find(x)) {
            size++;
            insert(x);
        }

    }

    void eraseSize(int x) {
        if (find(x)) {
            size--;
            erase(x);
        }

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
                if (summary->Tmax < summary->Tmin)
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
    scanf("%d", &n);

    vector<bool> cnt(n);
    vector<vector<int>> lift(n, vector<int>(1));
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        x--;
        cnt[x] = true;
        lift[i][0] = x;
    }
    vector<int> a(n);
    int mx = 0;
    int cntZeroIndegree = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        mx = max(a[i], mx);
        a[i]--;
        if (!cnt[i])
            cntZeroIndegree++;
    }
    int k = (mx - n) / cntZeroIndegree;

    for (int i = 1; i <= k; i = i << 1)
        K++;

    for (int i = 0; i < n; i++)
        lift[i].resize(K);

    for (int j = 1; j < K; j++) {
        for (int i = 0; i < n; i++) {
            lift[i][j] = lift[lift[i][j - 1]][j - 1];
        }
    }

    vector<queue<int>> Vi(n);
    for (int i = 0; i < n; i++) {
        int vertex = i, level = k;
        for (int j = K - 1; j >= 0; j--) {
            int bit = (1 << j);
            if (level & bit) {
                level -= bit;
                vertex = lift[vertex][j];
            }
        }
        Vi[a[vertex]].push(i);
    }

    VanEmdeBoasTree remaining(n);
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        if (!Vi[i].empty()) {
            int mn = 1e9;
            while (!Vi[i].empty()) {
                int val = Vi[i].front();
                mn = min(mn, val);
                Vi[i].pop();
                remaining.insert(val);
                assert(remaining.find(val));
            }
            remaining.erase(mn);
            assert(!remaining.find(mn));
            ans[mn] = i + 1;

        }
        else {
            int val = remaining.Tmin;
            assert(val >= 0);
            ans[val] = i + 1;
            remaining.erase(val);
            assert(!remaining.find(val));
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);

    return 0;
}