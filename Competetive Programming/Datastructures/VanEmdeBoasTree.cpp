#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris

typedef long long ll;
int n, k, l;

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
            childs = vector<VanEmdeBoasTree>(childsize, NULL);

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

long long rand(long long a, long long b) {
    return a + (rand()) % (b - a + 1);
}

int main() {


    return 0;
}
