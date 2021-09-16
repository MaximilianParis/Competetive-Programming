
#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
map<ll, bool> palindromes;
vector<vector<bool>> adj;
int N, M, K;
ll ans;
ll value;
double cnt = 0;
void generatePossibleHamiltonPalindroms(vector<int>& palindrom,int usedDifferentLetters,int LastNeg) {
	int posOfFirstNegative = (find(palindrom.begin()+ LastNeg, palindrom.end(), -1) - palindrom.begin());
	int size = palindrom.size();
	bool doesntContainNegative = posOfFirstNegative == size;

	if (doesntContainNegative) {
		vector<vector<int>>subsetEndsAt(usedDifferentLetters, (vector<int>(1 << usedDifferentLetters)));
		vector<int> pos1(usedDifferentLetters);
		vector<int> pos2(usedDifferentLetters);
		for (int i = 0; i < size; i++) {
			pos1[palindrom[i]] = pos2[palindrom[i]];
			pos2[palindrom[i]] = i;
		}
		for (int i = 0; i < usedDifferentLetters; i++) 
             if (adj[pos1[i]][pos2[i]]) 
			       subsetEndsAt[i][1<<i] = true;
		int maxSubsets = 1 << usedDifferentLetters;
		for (int subset = 0; subset < maxSubsets; subset++) {
			for (int curr = 0; curr < usedDifferentLetters; curr++) {
				bool subsetContainsHamiltonPathEndingAtCurrent = subsetEndsAt[curr][subset];
				if (subsetContainsHamiltonPathEndingAtCurrent) {
					for (int newNode = 0; newNode < usedDifferentLetters; newNode++) {
						bool doesntContainNewNode = !((subset >> newNode) & 1);
						if (doesntContainNewNode) {
							int subsetWithNewNode = subset | (1 << newNode);
							subsetEndsAt[newNode][subsetWithNewNode] |= (adj[pos1[curr]][pos1[newNode]] && adj[pos2[curr]][pos2[newNode]]);
							subsetEndsAt[newNode][subsetWithNewNode] |= (adj[pos1[curr]][pos2[newNode]] && adj[pos2[curr]][pos1[newNode]]);
							if (subsetEndsAt[newNode][subsetWithNewNode] && maxSubsets == subsetWithNewNode)
								break;
						}
					}
				}

			}

		}
		for (int i = 0; i < usedDifferentLetters; i++) {
			bool graphContainsHamiltonPath = subsetEndsAt[i][(1 << usedDifferentLetters) - 1];
			if (graphContainsHamiltonPath) {
				int hashValue = 0;
				for (int letter : palindrom) {
					hashValue = hashValue * 6 + letter;
				}
				palindromes[hashValue] = true;
				break;
			}
		}
		


	}
	else {
		for (int letterPartner = posOfFirstNegative + 1; letterPartner < size; letterPartner++) {
			if (palindrom[letterPartner] == -1) {
				palindrom[letterPartner] = palindrom[posOfFirstNegative] = usedDifferentLetters;
				generatePossibleHamiltonPalindroms(palindrom, usedDifferentLetters + 1, posOfFirstNegative+1);
				palindrom[letterPartner] = palindrom[posOfFirstNegative] = -1;
			}
		}
	}
}
bool dfsTowardsValidPalindrom(vector<int> palindrom) {
	vector<int> used(int(palindrom.size()), -1);
	int cnt = 0;
	for(int i=0;i< palindrom.size();i++) if (used[palindrom[i]] == -1)
		used[palindrom[i]] = cnt++;
	long long num = 0;
	for (int& x : palindrom) {
		x = used[x];
		num = num * 6 + x;
	}
	if (palindromes.count(num)) return palindromes[num];
	bool res = false;
	vector<int> cur(cnt);
	for (int i = 0; i < palindrom.size(); i++)  ++cur[palindrom[i]];
	for (int i = 0; i < palindrom.size(); i++)  if (cur[palindrom[i]] > 2) {
		int x = palindrom[i];
		for (int j = i + 1; j < int(palindrom.size()); ++j) if (palindrom[j] == palindrom[i]) {
			palindrom[i] = palindrom[j] = cnt;
			if (dfsTowardsValidPalindrom(palindrom)) {
				res = true;
				break;
			}
			palindrom[i] = palindrom[j] = x;
		}
		break;
	}
	return palindromes[num] = res;
}




void generatePalindromsWithDuplikateLetters(vector<int>& palindrom, int usedDifferentLetters,int lastNeg) {
	
		int posOfFirstNegative = (find(palindrom.begin()+ lastNeg, palindrom.end(), -1) - palindrom.begin());
		int size = palindrom.size();
		bool doesntContainNegative = posOfFirstNegative == size;
		if (doesntContainNegative) {
			dfsTowardsValidPalindrom(palindrom);
			return;
		}
		else {
			for (int nextLetter = 0; nextLetter < usedDifferentLetters+1; nextLetter++) {
				for (int letterPartner = posOfFirstNegative + 1; letterPartner < size; letterPartner++) {
					if (palindrom[letterPartner] == -1) {
						palindrom[letterPartner] = palindrom[posOfFirstNegative] = nextLetter;
						generatePalindromsWithDuplikateLetters(palindrom, max(nextLetter + 1, usedDifferentLetters), posOfFirstNegative + 1);
						palindrom[letterPartner] = palindrom[posOfFirstNegative] = -1;
					}
				}
			}
		}


}


int main()
{
	cin >> N >> M >> K;
	adj = vector<vector<bool>>(N, vector<bool>(N));
	for (int i = 0; i < M; i++) {
		int x1, x2;
		cin >> x1 >> x2;
		x1--, x2--;
		adj[x1][x2] = true;
		adj[x2][x1] = true;
	}

	vector<int> palindrom(N,-1);
	generatePossibleHamiltonPalindroms(palindrom, 0,0);
	generatePalindromsWithDuplikateLetters(palindrom, 0, 0);
	vector<long long> fact(K + 1);
	fact[0] = 1;
	for (int i = 1; i <= K; ++i) fact[i] = fact[i - 1] * i;
	long long ans = 0;
	for (auto it : palindromes) if (it.second) {
		long long num = it.first;
		long long mx = 1;
		while (num) {
			mx = max(mx, num % 6 + 1);
			num /= 6;
		}
		if (mx <= K) {
			ans += fact[K] / fact[K - mx];
		}
	}
	printf("%lld\n", ans);
	return 0;
	
}