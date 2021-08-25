#include <bits/stdc++.h>
//Author: Max Pairs
//Problem Link: https://codeforces.com/problemset/problem/1155/D
using namespace std;
typedef long long ll;




int main() {
	int n, x;
	cin >> n >> x;
	vector<ll>arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	vector<ll> bestsumleft(n);
	vector<ll> bestsumright(n);
	

	for (int i = 0; i < n; i++) {
		
		if (i == 0)
			bestsumleft[i] = 0;
		else 
			bestsumleft[i] = max(0LL, bestsumleft[i - 1] + arr[i-1]);
		
		if (n-i == n)
			bestsumright[n - i-1] = 0;
		else
			bestsumright[n - i-1] = max(0LL, bestsumright[n - i] + arr[n - i]);
	}
	ll maxsum = 0;
	ll best = 0;
	ll last1 = 0;
	ll last2 = 0;
	for (int i = 0; i < n; i++) {
		
	    last1 = best + bestsumright[i] + arr[i];
		maxsum = max(maxsum, last1);
		last2 = best + bestsumright[i] + arr[i] * x;
		maxsum = max(maxsum, last2);
		if(i<n-1)
		best = max(bestsumleft[i+1], best+ arr[i] * x);
		
	}
	
	cout << maxsum << endl;

}