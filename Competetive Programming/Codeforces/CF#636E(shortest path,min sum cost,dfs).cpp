#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

vector<vector<int>> g;

void bfs(int s, vector<int> &d) {
d[s]=0;
queue <int> q;
q.push(s);
while(!q.empty()){
    int v= q.front();
    q.pop();
    for(auto it: g[v]){
        if(d[it]==INF){
            d[it]=d[v]+1;
            q.push(it);
        }
    }
    
    
}
	
	
}

int main() {

	
	int t;
	cin >> t;
	while (t--) {
		int n, m, a, b, c;
		cin >> n >> m >> a >> b >> c;
		--a, --b, --c;
		
		vector<int> p(m);
		for (auto &it : p) cin >> it;
		sort(p.begin(), p.end());
		vector<long long> pref(m + 1);
		for (int i = 0; i < m; ++i) {
			pref[i + 1] = pref[i] + p[i];
		}
		
		g = vector<vector<int>>(n);
		for (int i = 0; i < m; ++i) {
			int x, y;
			cin >> x >> y;
			--x, --y;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		
		vector<int> da(n, INF), db(n, INF), dc(n, INF);
		bfs(a, da);
		bfs(b, db);
		bfs(c, dc);
		
		long long ans = 1e18;
		for (int i = 0; i < n; ++i) {
            if(da[i]+db[i]+dc[i]>m)continue;
            ans=min(ans,pref[db[i]]+pref[da[i]+db[i]+dc[i]]);
			
		}
		cout << ans << endl;
	}
	
	return 0;
}