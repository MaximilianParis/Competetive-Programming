#include <bits/stdc++.h>

using namespace std;
//Author:Max Paris
//O(n*log(n)*k)
//Problem Link:http://codeforces.com/contest/868/problem/F
typedef long long ll;
int n,k;
vector<int> arr,cnt;
vector<ll> dp, dp1;
ll cost = 0;
int l1, r1;
void calc(int l, int r) {
	
	for (; l1 < l; l1++)
		cost -= --cnt[arr[l1] - 1];

	for (; r1 > r;r1--)
		cost -= --cnt[arr[r1] - 1];

	for (; l1 > l;)
		cost += cnt[arr[--l1] - 1]++;

	for (; r1 < r; r1)
		cost += cnt[arr[++r1] - 1]++;

	

}

void recur(int l, int r, int L, int R) {
	
	int mid = l + (r - l) / 2;
	int opt = L;
	
	dp[mid] = 1e18;
	int size = min(mid, R);
	if (mid == 0)dp[mid] = 0;
	for (int i = size; i >= L; i--) {
		calc(i, mid);
		ll val = cost + dp1[i-1];
		if (val < dp[mid])dp[mid] = val, opt = i;
		
	}
	if (l + 1 < r) {
		recur(l, mid, L, opt);
		recur(mid, r, opt, R);
	}
}
int main() {
	scanf("%d%d", &n, &k);
	arr = vector<int>(n);

	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	dp=vector<ll> (n);
	dp1=vector<ll> (n);
	cnt=vector<int>(n);
	for (int i = 0; i < n; i++) {
		cost += cnt[arr[i]-1]++;
		dp[i] = cost;
		dp1[i] = cost;
	}
	
	l1 =0;
	r1 = n - 1;
	
	for (int i = 1; i < k; i++) {
		recur(0,n,1, n-1);
		for (int i = 0; i < n; i++)dp1[i] = dp[i];
	}
	printf("%lld\n", dp[n - 1]);
}