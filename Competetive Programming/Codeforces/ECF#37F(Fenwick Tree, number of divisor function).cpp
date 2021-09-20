#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
typedef long double ld;
using namespace std;
//Author:Max Paris
//Problem Link: https://codeforces.com/contest/920/problem/F
//O(MaxN*log(MaxN)+m*log(n)+n*T(x)*log(n))
//where T(x) denotes the worst possible value for the number of calls of the number of divisors function
//the formula is T(x)=1+T(d(x)) for x>1, else 1
int t, n, m, q, d, k;
const int MaxN = 1e6;
vector<int> D(MaxN + 1, 2);
vector<int>Indexing;
struct FenwickTree {
    vector<ll> bit;
    int n;

     FenwickTree(int n,ll defaultValue=0) {
        this->n = n;
        bit.assign(n, defaultValue);
   }
    FenwickTree(vector<int>& arr) : FenwickTree(arr.size()) {
        for (int i = 0; i < n; i++)
            add(i, arr[i]);

    }
    ll sum(int pos) {
        ll queryVal = 0;
        for(;pos>=0;pos=(pos&(pos+1))-1)
            queryVal +=bit[pos];
        return queryVal;
    }


    ll sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, ll val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += val;
    }

};
int next(int pos) {
    return Indexing[pos]=(pos == Indexing[pos]) ? pos : next(Indexing[pos]);
}
void precompute() {
    D[1] = 1;


    for (int p = 2; p <= MaxN; p++)
    {

        for (int num = 2 * p; num <= MaxN; num += p)
            D[num]++;
    }
}

int main()
{
   
    precompute();
    scanf("%d%d", &n, &m);
    FenwickTree tree(n);
    vector<int> arr(n);
    Indexing=vector<int>(n+1);
    for (int i = 0; i < n; i++) {
        int x1;
        scanf("%d", &x1);
        Indexing[i] = i;
        tree.add(i, x1);
        arr[i] = x1;
    }
    Indexing[n] = n;
;    for (int i = 0; i < m; i++) {
        int x1, x2, x3;
        scanf("%d%d%d", &x1, &x2, &x3);
        x2--, x3--;
        if (x1==1) {
            for (int j = next(Indexing[x2]); j <= x3;) {
               
                int diff = D[arr[j]] - arr[j];
               
                tree.add(j, diff);
                arr[j] = D[arr[j]];
                if (arr[j] < 3)
                    Indexing[j] = j + 1;
                if (Indexing[j] == next(Indexing[j]))
                    j++;
                else j = Indexing[j];

               
            }
        }
        else {
            printf("%lld\n", tree.sum(x2, x3));
        }
    }

    return 0;

}