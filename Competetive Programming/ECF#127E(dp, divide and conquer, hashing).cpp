#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int m, n, k;
const int Mod = 998244353;
//Problem link:https://codeforces.com/problemset/problem/1671/E
//O((2^n)*n)
pair<string,ll> recurr(int index, vector<string>& tree) {
	if (2 * index + 2 >= m) {
		return {tree[index], 1};
	}
	else {
		pair<string, ll> x1 = recurr(index * 2 + 1, tree);
		pair<string, ll> x2 = recurr(index * 2 + 2, tree);
		pair<string, ll> ans;
		if (x1.first == x2.first) {
			ans.second = (x1.second * x2.second)%Mod;
			ans.first = tree[index] + x1.first + x2.first;
		}
		else {
			ans.second = (((x1.second * x2.second)%Mod)*2)%Mod;
			int size = min(x1.first.size(), x2.first.size());
			bool finished = false;
			for (int i = 0; i < size; i++) {
				if (x1.first[i] != x2.first[i]) {
					finished = true;
					if (x1.first[i] == 'A') {
						ans.first = tree[index] + x1.first + x2.first;
					}
					else 
						ans.first = tree[index] + x2.first + x1.first;
					break;
				}
			}
			if (!finished) {
				if(x1.first.size()<x2.first.size())
					ans.first = tree[index] + x1.first + x2.first;
				else 
					ans.first = tree[index] + x2.first + x1.first;
			}

		}

		return ans;
	}
}


int main() {


	
	scanf("%d", &n);
    m = (1 << n) - 1;
	vector<string> tree(m);
	for (int i = 0; i < m+1; i++) {
		char c;
		scanf("%c", &c);
		if(i>0)
		tree[i-1] = c;
	}
        
	
	printf("%d\n", recurr(0, tree).second);


	return 0;
}