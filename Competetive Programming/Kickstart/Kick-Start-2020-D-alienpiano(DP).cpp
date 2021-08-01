

#include<bits/stdc++.h>
#include <sstream>
int signum(int a) { return (a > 0) - (a < 0); }
int compare(int a, int b) { return signum(a - b); }

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	int T; cin >> T;
	for (int case_num = 1; case_num <= T; case_num++) {
		int N; cin >> N;
		vector<int> A(N);
		for (int i = 0; i < N; i++) cin >> A[i];
		vector<int> dp(4);
		for (int i = 1; i < N; i++) {
			vector<int> ndp(4,N+1);
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					int a = dp[x] + (compare(x, y) != compare(A[i - 1], A[i]));
					ndp[y] = min(ndp[y], dp[x] + (compare(x, y) != compare(A[i - 1], A[i])));
				}
			}
			dp = ndp;
		}

		int ans = std::min({ dp[0], dp[1], dp[2], dp[3] });

		cout << "Case #" << case_num << ": " << ans << '\n';
	}

	return 0;
}
