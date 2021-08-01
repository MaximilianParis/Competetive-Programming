 #include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int n;
vector<int> w, c, cnt;
vector<vector<pair<int, int>>> g;

long long getdiff(int i) {
	return w[i] * 1ll * cnt[i] - (w[i] / 2) * 1ll * cnt[i];
}

void dfs(int v, int p = -1) {
	if (g[v].size() == 1) cnt[p] = 1;
	for (auto [to, id] : g[v]) {
		if (id == p) continue;
		dfs(to, id);
		if (p != -1) cnt[p] += cnt[id];
	}
}

vector<long long> get(int clr) {
	set<pair<long long, int>> st;
	long long cur = 0;
	for (int i = 0; i < n - 1; ++i) {
		if (c[i] == clr) {
			st.insert({getdiff(i), i});
			cur += w[i] * 1ll * cnt[i];
		}
	}
	vector<long long> res;
	res.push_back(cur);
	while (cur > 0 && !st.empty()) {
		int id = st.rbegin()->second;
		st.erase(prev(st.end()));
		cur -= getdiff(id);
		res.push_back(cur);
		w[id] /= 2;
		st.insert({getdiff(id), id});
	}
	return res;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	int t;
	cin >> t;
	while (t--) {
		long long s;
		cin >> n >> s;
		w = c = cnt = vector<int>(n - 1);
		g = vector<vector<pair<int, int>>>(n);
		for (int i = 0; i < n - 1; ++i) {
			int x, y;
			cin >> x >> y >> w[i] >> c[i];
			--x, --y;
			g[x].push_back({y, i});
			g[y].push_back({x, i});
		}
		dfs(0);
		vector<long long> v1 = get(1), v2 = get(2);
		int pos = int(v2.size()) - 1;
		int ans = INF;
		for (int i = 0; i < int(v1.size()); ++i) {
			while (pos > 0 && v1[i] + v2[pos - 1] <= s) --pos;
			if (v1[i] + v2[pos] <= s) {
				ans = min(ans, i + pos * 2);
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}