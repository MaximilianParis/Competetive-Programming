

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
ll sz[N], a[N], ans, mod = ll(1e9 + 7), b[N];
vector<int> G[N];
void dfs(int p, int fa)
{
    sz[p] = 1;
    for (int i = 0; i < G[p].size(); i++) if (G[p][i] != fa) dfs(G[p][i], p), sz[p] += sz[G[p][i]];
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, x, y;
        cin >> n;
        ans = 0;
        for (int i = 1; i <= n; i++) G[i].clear(), a[i] = 1;
        for (int i = 1; i < n; i++) cin >> x >> y, G[x].push_back(y), G[y].push_back(x);
        dfs(1, 0);
        cin >> m;
        for (int i = 1; i <= m; i++) cin >> a[i];
        m = max(n - 1, m);
        sort(a + 1, a + 1 + m);
        if (m > n - 1) for (int i = n; i <= m; i++) a[n - 1] = a[n - 1] % mod * a[i] % mod, a[n - 1] %= mod;
        for (int i = 1; i < n; i++) b[i] = (n - sz[i + 1]) * sz[i + 1];
        sort(b + 1, b + n);
        for (int i = 1; i < n; i++) ans = ans % mod + (b[i] % mod * a[i] % mod) % mod, ans %= mod;
        cout << ans % mod << "\n";
    }
}