#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, q, k,t;
string s;
vector<int> arr;
ll ans;
//Author: Max Paris
//Problem Link:http://codeforces.com/contest/1607/problem/G
//O(t*n)
int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		vector<pair<int, int>> arr(n);
		ll balance = 0;
		ll eatableA = 0;
		ll eatableB = 0;
		ll eat = 1ll*m * n;
		ll eatA = 0;
		ll eatB = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i].first), balance += arr[i].first;
			eatableA += min(arr[i].first, m);
			scanf("%d", &arr[i].second), balance -= arr[i].second;
			eatableB += min(arr[i].second, m);
			
		}
		ll x1 = eatableA;
		ll x2 = eatableB;
		
		if (balance >= 0) {
			if (eatableA <= balance) {
				balance -= eatableA;
				eatA = eatableA;
				
				eatB = eat - eatA;
				balance += eatB;
			}
			else {
				eatA += balance;
				eatableA -= balance;
				ll half = (eat - balance) / 2;
				
				if (eatableA < half) {

					eatA += eatableA;
					eatB = eat - eatA;
					balance += eatB - eatA;
					
				}
				else if (eatableB < half) {
					eatB = eatableB;
					eatA = eat - eatB;
					balance += eatB - eatA;
				}
				else {
					if ((eat - balance) % 2) {
						if (eatableA > half) {
							eatA += 1 + half;
							eatB = half;

						}
						else {
							eatA +=half;
							eatB = half+1;
						}


						balance = 1;
					}
					else {
						eatB = half;
						eatA = eat - eatB;
						balance = 0;
					}
				}
			}
			
		}
		else if (balance < 0) {
			balance *= -1;
			if (eatableB <= balance) {
				balance -= eatableB;
				eatB = eatableB;
				eatA = eat - eatB;
				balance += eatA;
			}
			else {
				eatB += balance;
				eatableB -= balance;
				ll half = (eat - balance) / 2;
				
				if (eatableB < half) {

					eatB += eatableB;
					eatA = eat - eatB;
					
					balance += eatA - eatB;
				}
				else if (eatableA < half) {
					eatA = eatableA;
					eatB = eat - eatB;
					
					balance += eatA - eatB;
				}
				else {
					
					if ((eat - balance) % 2) {
						if (eatableB > half) {
							eatB += 1 + half;
							eatA = half;

						}
						else {
							eatB += half;
							eatA = half + 1;
						}
						

						balance = 1;
					}
					else {
						eatA = half;
						eatB = eat - eatA;
						balance = 0;
					}
				}
			}
		}
		printf("%lld\n", balance);
		
		for (int i = 0; i < n;i++) {
			ll x5 = min(m, arr[i].first);
			ll x6 = min(m, arr[i].second);
			ll x3 = min(eatA, 1ll * min(m, arr[i].first));
			ll x4 = min(eatB, min(1ll * m - x3, 1ll * arr[i].second));
			ll diff=0;
			 if (x1 - x5 < eatA - x3) {
				 diff = (eatA - x3)- (x1 - x5);
				x3 += diff;
				x4 = m - x3;
			}
			else if(x2 - x6 < eatB - x4){
				 diff = (eatB - x4)-(x2 - x6);
				x4 += diff;
				x3 = m - x4;
			}
			 printf("%lld lld\n", x3,x4);
			 
			 eatA -= x3;
			 eatB -= x4;
			 x1 -=x5;
			 x2-= x6;
			
		}
		
		

	}
}