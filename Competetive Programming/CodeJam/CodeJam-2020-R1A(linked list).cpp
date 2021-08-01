
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int r, c;
int eliminated = 0;
vector<vector<ll>> s;
vector< vector<vector<pair<ll, ll>>>> linked_list;
vector<pair<ll, ll>> store;

void init_linked_list() {
	linked_list = vector< vector<vector<pair<ll, ll>>>>(r, vector<vector<pair<ll, ll>>>(c, vector<pair<ll, ll>>(4, { -1,-1 })));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (int z = 0; z < 4; z++) {
				if (z == 0 && i > 0)linked_list[i][j][z] = { i - 1,j };
				else  if (z == 1 && j < c - 1)linked_list[i][j][z] = { i,j + 1 };
				else if (z == 2 && i < r - 1)linked_list[i][j][z] = { i + 1,j };
				else if (z == 3 && j > 0)linked_list[i][j][z] = { i,j - 1 };
			}
		}

	}
}
double func() {
	eliminated = 0;
	vector< vector<vector<pair<ll, ll>>>> q; q = linked_list;
	ll sum = 0;
	if (int(store.size()) == 0) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (int(linked_list[i][j].size()) > 0) {
					double value = 0; int divisor = 0;
					for (int z = 0; z < 4; z++) {
						if (linked_list[i][j][z].first != -1 && linked_list[i][j][z].second != -1)
							value += s[linked_list[i][j][z].first][linked_list[i][j][z].second], divisor++;
					}double check = value / double(divisor);
					if (check > s[i][j]) {
						eliminated++, sum += s[i][j];
						if (i > 0) { if (q[i][j][0].first != -1 && q[i][j][0].second != -1)q[q[i][j][0].first][q[i][j][0].second][2] = q[i][j][2]; }
						if (i < r - 1) { if (q[i][j][2].first != -1 && q[i][j][2].second != -1)q[q[i][j][2].first][q[i][j][2].second][0] = q[i][j][0]; }
						if (j > 0) { if (q[i][j][3].first != -1 && q[i][j][3].second != -1)q[q[i][j][3].first][q[i][j][3].second][1] = q[i][j][1]; }
						if (j < c - 1) { if (q[i][j][1].first != -1 && q[i][j][1].second != -1) q[q[i][j][1].first][q[i][j][1].second][3] = q[i][j][3]; }
						q[i][j].clear();

					}
					else sum += s[i][j], store.push_back({ i,j });



				}
			}
		}
	}
	else {

		for (int it = 0; it<int(store.size()); it++) {
			if (it < 0)it = 0;
			else if (it >= int(store.size()))it = int(store.size()) - 1;
			int i = store[it].first;
			int j = store[it].second;
			if (int(linked_list[i][j].size()) > 0) {
				double value = 0; int divisor = 0;
				for (int z = 0; z < 4; z++) {
					if (linked_list[i][j][z].first != -1 && linked_list[i][j][z].second != -1)
						value += s[linked_list[i][j][z].first][linked_list[i][j][z].second], divisor++;
				}double check = value / double(divisor);
				if (check > s[i][j]) {
					eliminated++, sum += s[i][j];
					if (i > 0) { if (q[i][j][0].first != -1 && q[i][j][0].second != -1)q[q[i][j][0].first][q[i][j][0].second][2] = q[i][j][2]; }
					if (i < r - 1) { if (q[i][j][2].first != -1 && q[i][j][2].second != -1)q[q[i][j][2].first][q[i][j][2].second][0] = q[i][j][0]; }
					if (j > 0) { if (q[i][j][3].first != -1 && q[i][j][3].second != -1)q[q[i][j][3].first][q[i][j][3].second][1] = q[i][j][1]; }
					if (j < c - 1) { if (q[i][j][1].first != -1 && q[i][j][1].second != -1) q[q[i][j][1].first][q[i][j][1].second][3] = q[i][j][3]; }
					q[i][j].clear();
					store.erase(store.begin() + it); it--;

				}
				else sum += s[i][j];



			}

		}
	}
	linked_list = q;
	return sum;
}
int main() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {

		cin >> r >> c;
		store = vector<pair<ll, ll>>(0);
		s = vector<vector<ll>>(r, (vector<ll>(c)));
		ll ans = 0;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cin >> s[i][j];

			}
		}
		init_linked_list();
		while (true) {
			ll add = func();
			if (eliminated > 0)ans += add;
			else if (eliminated == 0) { ans += add; break; }

		}



		cout << "Case #" << tc << ": " << ans << endl;

	}
	return 0;
}
