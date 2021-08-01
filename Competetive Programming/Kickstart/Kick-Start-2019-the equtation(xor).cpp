#include <bits/stdc++.h>
#include <unordered_map>
typedef long long ll;
using namespace std;
vector<ll> pow_2(65);
void calc_2_pow() {
	pow_2[0] = 1;
	for (int i = 1; i <= 50; i++) {
		pow_2[i] = pow_2[i - 1] * 2;
	}
}
//O(t*(n+n*50+remaining of(50))+50)
int main() {
	calc_2_pow();
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		ll n, m;
		cin >> n >> m;
		unordered_map<ll, ll> cnt_nums;
		vector<bitset<50>> s(n);
		ll sum = 0;

		for (int i = 0; i < n; i++) {
			ll input;
			cin >> input;
			sum += input;
			bitset<50> p(input);
			s[i] = p;
		}
		map<ll, ll, greater<ll>> cnt_nums_1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 50; j++) {
				if (s[i][j] == 1)
					cnt_nums[pow_2[j]]++;
				else cnt_nums[pow_2[j]];

			}
		}
		ll k = 0;

		for (auto it : cnt_nums) {
			ll add = it.first * (n - it.second) - it.first * it.second;
			if (add <= 0) {
				sum += add;
				k += it.first;

			}
			else cnt_nums_1[it.first] = it.second;
		}

		for (auto it : cnt_nums_1) {
			ll add = it.first * (n - it.second) - it.first * it.second;
			if ( add + sum <= m) {
				sum += add;
				k += it.first;
			}
		}
		cout << "Case #" << tc << ": ";
		if (sum <= m)cout << k << endl;
		else cout << -1 << endl;





	}


	return 0x0;
}