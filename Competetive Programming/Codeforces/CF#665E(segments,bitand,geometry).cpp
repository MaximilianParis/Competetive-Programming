

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1e6 + 5;
int tree[maxn];
inline void add(int n, int dx) {
    while (n < maxn) {
        tree[n] += dx, n += n & -n; 
    }
}
inline int query(int n) {
    if (n < 0) return 0;
    int ans = 0; while (n) {
        ans += tree[n], n -= n & -n; //n wird immer zu einer 2 Potenz
    } return ans;
}
int main() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> pre(maxn), V(maxn);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int y, l, r; cin >> y >> l >> r;
        V[l].push_back({ y,1 });
        V[r].push_back({ y,0 });
        if (l == 0 && r == 1e6) ans++;
    }
    for (int i = 1; i <= m; i++) {
        int x, l, r; cin >> x >> l >> r;
        if (l == 0 && r == 1e6) ans++;
        pre[x].push_back({ l,r });
    }
    for (int i = 0; i <= 1e6; i++) {//i steht für x wenn x1<=i<=x2 ist der punkt im x Bereich dann wird mit V nach unten vom oberen punkt
        // gegangen und makiert im tree, dann wird in query geschaut ob der punkt im y Bereich ist und der untere Teil wird noch abgezogen
        for (auto x : V[i]) if (x.second)
            add(x.first, 1);
        for (auto x : pre[i]) ans += query(x.second) - query(x.first - 1);
        for (auto x : V[i]) if (!x.second)
            add(x.first, -1);
    }
    cout << ans + 1 << endl;
    return 0;
}