#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
int calc(const string &s, char c) {
	if (s.size() == 1) {
		return s[0] != c;
	}
	int mid = s.size() / 2;
	int cntl = calc(string(s.begin(), s.begin() + mid), c + 1);
	cntl += s.size() / 2 - count(s.begin() + mid, s.end(), c);
	int cntr = calc(string(s.begin() + mid, s.end()), c + 1);
	cntr += s.size() / 2 - count(s.begin(), s.begin() + mid, c);
	return min(cntl, cntr);
}

int main() {

	int t;
	cin >> t;
	while (t--) {
		int n;
		string s;
		cin >> n >> s;
		cout << calc(s, 'a') << endl;
	}
	
	return 0;
}