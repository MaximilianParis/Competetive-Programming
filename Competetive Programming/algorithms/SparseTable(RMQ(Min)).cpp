#include <bits/stdc++.h>


using namespace std;
typedef long long ll;
vector<vector<ll>> minima;

ll logofn;
int n, q;
ll processquery(int l,int r) {
	ll diff = r - l+1;
	
		ll log2diff = log2(diff);
		return min(minima[l][log2diff], minima[r - (1 << log2diff)+1][ log2diff]);
	
	
	
}
void precompute() {
	ll val = 1;
	for (int j = 1; j < logofn; j++) {
		
		for (int i = 0; i+ val < n; i++) {
		
			minima[i][j] = min(minima[i][j - 1], minima[i + val][j - 1]);
			
		}
		val = val << 1;
	}
}
int main() {
	
	cin >> n >> q;
	
	logofn = log2(n)+1;
	minima = vector<vector<ll>>(n, vector<ll>(logofn));
	for (int i = 0; i < n; i++)
		cin >> minima[i][0];
	precompute();
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		cout << processquery(l, r) << endl;
	}

}