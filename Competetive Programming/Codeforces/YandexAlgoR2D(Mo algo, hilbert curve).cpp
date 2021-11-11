#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long ld;
int n, m, q, k, t;
const int upperlogOfN = 21;
string s;
vector<int> arr;
vector<int> Mo;
ll sum = 0;


//Author: Max Paris
//Problem Link:https://codeforces.com/contest/86/problem/D
//O((n)*sqrt(m))
void remove(int idx) {
    int index = arr[idx] - 1;
    sum -= (1ll * 2 * Mo[index] - 1) * arr[idx];
    Mo[index]--;

}
void add(int idx) {
    int index = arr[idx] - 1;

    Mo[index]++;
    sum += (1ll * 2 * Mo[index] - 1) * arr[idx];
}
ll get_answer() {
    return sum;
}




inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? (
        (y < hpow) ? 0 : 3
        ) : (
            (y < hpow) ? 1 : 2
            );
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = { 3, 0, 0, 1 };
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    ll subSquareSize = ll(1) << (2 * pow - 2);
    ll ans = seg * subSquareSize;
    ll add = gilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

struct Query {
    int l, r, idx;
    int64_t ord;

    inline void calcOrder() {
        ord = gilbertOrder(l, r, 21, 0);
    }
};
inline bool operator<(const Query& a, const Query& b) {
    return a.ord < b.ord;
}

void mo_s_algorithm(vector<Query> queries) {
    vector<ll> answers(queries.size());
    sort(queries.begin(), queries.end());
    Mo = vector<int>(1e6);


    int cur_l = 0;
    int cur_r = -1;
  

    for (auto q : queries) {

        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }

    for (auto it : answers) {
        printf("%I64d\n", it);
    }
}
int main()
{
    scanf("%d%d", &n, &m);

    arr = vector<int>(n);


    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);


    vector<Query> queries(m);
   
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &queries[i].l, &queries[i].r);
        queries[i].l--;
        queries[i].r--;
        queries[i].idx= i;
        queries[i].ord= gilbertOrder(queries[i].l, queries[i].r, upperlogOfN, 0);
    }

  


}