

using namespace std;
#include <bits/stdc++.h>
vector<vector<int>> ord;
vector<int> cnta;
vector<int> cntb;
vector<vector<int>> g;

void dfs(int v, vector <int> path, int p = -1) {
	path.push_back(v);
	for (auto to : g[v]) {
		if (to != p) dfs(to, path, v);
	}

	ord[v] = path;

	reverse(ord[v].begin(), ord[v].end());

}

int main() {


	int t;
	cin >> t;
	for (int t_ = 1; t_ <= t; t_++) {
		int n, a, b;
		cin >> n >> a >> b;
		g = vector<vector<int>>(n);

		for (int i = 0; i < n - 1; ++i) {
			int  x;
			cin >> x;
			--x;


			g[i + 1].push_back(x);
			g[x].push_back(i + 1);

		}



		ord = vector<vector<int>>(n);
			dfs(0, vector<int>(0));
		cnta = vector<int>(n);
		cntb = vector <int >(n);
		for (int i = 0; i<int(ord.size()); i++) {

			for (int j = 0; j<int(ord[i].size()); j += a)cnta[ord[i][j]] += 1 * 1ll;
			for (int j = 0; j<int(ord[i].size()); j += b)cntb[ord[i][j]] += 1 * 1ll;
		}
		double p1 = 0;
		double p2 = 0;
		double ans = 0;
		for (int i = 0; i < n; i++) {

			p1 = (1ll * double(cnta[i]) / double(n) * 1ll);
			p2 = (1ll * double(cntb[i]) / double(n) * 1ll);
			ans += (1ll * p1 + 1ll * p2 - p1 * 1ll * p2 * 1ll);
		}
		cout << "Case #" << t_ << ": " << setprecision(10) << ans * 1ll << endl;
		ord.clear();
	}return 0;
}