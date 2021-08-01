#include <bits/stdc++.h>

using namespace std;

int main() {

	
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<set<int>> segs;
		for (int i = 0; i < n - 1; ++i) {
			set<int> cur;
			int k;
			cin >> k;
			for (int j = 0; j < k; ++j) {
				int x;
				cin >> x;
				cur.insert(x);
			}
			segs.push_back(cur);
		}
		for (int fst = 1; fst <= n; ++fst) {
			vector<int> ans;
			bool ok = true;
			vector<set<int>> cur = segs;
			for (auto &it : cur) if (it.count(fst)) it.erase(fst);
			ans.push_back(fst);
			for (int i = 1; i < n; ++i) {
				int cnt1 = 0;
				int nxt = -1;
				for (auto  &it : cur) if (it.size() == 1) {
					++cnt1;
					nxt = *it.begin();
				}
				if (cnt1 != 1) {
					ok = false;
					break;
				}
				for (auto &it : cur) if (it.count(nxt)) it.erase(nxt);
				ans.push_back(nxt);
			}
			if (ok) {
				set<set<int>> all(segs.begin(), segs.end());
				for (int i = 1; i < n; ++i) {
					set<int> seg;
					seg.insert(ans[i]);
					bool found = false;
					for (int j = i - 1; j >= 0; --j) {
						seg.insert(ans[j]);
						if (all.count(seg)) {
							found = true;
							all.erase(seg);
							break;
						}
					}
					if (!found) ok = false;
				}
			}
			if (ok) {
				for (auto it : ans) cout << it << " ";
				cout << endl;
				break;
			}
		}
	}
	
	return 0;
}