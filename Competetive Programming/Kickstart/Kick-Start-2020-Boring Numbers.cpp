#include <bits/stdc++.h>
//Author: Maximilian Paris
using namespace std;
typedef long long ll;
ll ans;

vector<ll> bor_nums(22);
vector<ll> cnt_1(22);
void calc_nums() {
	bor_nums[1] = 5;
	cnt_1[1] = 5;
	for (int i = 2; i <= 18; i++) {
		bor_nums[i] = bor_nums[i-1]*5;
		cnt_1[i] = bor_nums[i] + cnt_1[i - 1];
	}
}
int main() {

	calc_nums();
	

		ll l, r;
		ans = 0;
		cin >> l >> r;
		string r1, l1;
		l1 = to_string(l);
		r1 = to_string(r);
		int digit_lenght_l1 = l1.size();
		ll ways_1 = 0;
		ll add = 0;
		int cnt = 0;
		for (int i = 0; i < digit_lenght_l1; i++) {
			ll g = 0; ll add1, add2;
			add1 = 0; add2 = 0;
			if ((i + 1) % 2 == 0)g = 0, add2 = 1;
			else g = -1, add2 = 0;
			if (i == 0) g = -1;
			if (i == 0 || (l1[i - 1] - '0') % 2 == (i) % 2) {

				if ((l1[i] - '0') % 2 == 1) {
					if (i == digit_lenght_l1 - 1)ways_1 += ((l1[i] - '0') / 2 + 1);
					else ways_1 += ((l1[i] - '0') / 2 + g + 1) * bor_nums[digit_lenght_l1 - i - 1];
				}
				else {
					if (i == digit_lenght_l1 - 1)ways_1 += ((l1[i] - '0') / 2 + add2);
					else ways_1 += ((l1[i] - '0') / 2) * bor_nums[digit_lenght_l1 - i - 1];
				}
			}
			else break;
		}bool bad = false;
		for (int i = 0; i < digit_lenght_l1; i++) {
			if ((l1[i] - '0') % 2 == (i + 1) % 2);
			else { bad = true; break; }
		}
		if (bad == false)add++;
		int digit_lenght_r1 = r1.size();
		ll ways_2 = 0;

		for (int i = 0; i < digit_lenght_r1; i++) {
			if (i == 0 || (r1[i - 1] - '0') % 2 == (i) % 2) {
				ll g = 0; ll add1, add2;
				add1 = 0; add2 = 0;
				if ((i + 1) % 2 == 0) { g = 0; add2 = 1; }
				else g = -1, add2 = 0;
				if (i == 0) g = -1;
				if ((r1[i] - '0') % 2 == 1) {
					if (i == digit_lenght_r1 - 1)ways_2 += ((r1[i] - '0') / 2 + 1);
					else ways_2 += ((r1[i] - '0') / 2 + 1 + g) * bor_nums[digit_lenght_r1 - i - 1];
				}
				else {
					if (i == digit_lenght_r1 - 1)ways_2 += ((r1[i] - '0') / 2 + add2);
					else ways_2 += ((r1[i] - '0') / 2) * bor_nums[digit_lenght_r1 - i - 1];
				}
			}
			else break;
		}

		ll ans = ways_2 - (ways_1 + cnt_1[digit_lenght_l1 - 1]) + add + cnt_1[digit_lenght_r1 - 1];
		
		cout << ans << endl;

	
	return 0x0;
}
