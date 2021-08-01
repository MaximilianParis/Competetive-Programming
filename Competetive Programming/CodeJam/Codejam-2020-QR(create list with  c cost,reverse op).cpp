
#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
	cout << "Case #" << t << ": ";
	int n, c;
	cin >> n >> c;
	c += 1;
	if (c < n || c > n * (n + 1) / 2) {
		cout << "IMPOSSIBLE" << '\n';
		return;
	}
	c -= n;
	vector<int> res(n);
	for (int i = 0; i < n; i++) res[i] = i;
	for (int j = n - 1; j >= 0; j--) {
		int extra = min(c, n - 1 - j);
		c -= extra;
		reverse(res.begin() + j, res.begin() + j + extra + 1);
	}
	for (int i = 0; i < n; i++) {
		cout << (res[i] + 1) << " \n"[i == (n - 1)];
	}
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) solve(t);
}