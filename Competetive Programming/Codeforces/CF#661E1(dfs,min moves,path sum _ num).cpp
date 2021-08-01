  #include <bits/stdc++.h>

using namespace std;

vector<int> w, cnt;
vector<vector<pair<int, int>>> g;
void dfs(int v,int p=-1){
    if(g[v].size()==1)cnt[p]=1;
    for(auto [to,id]: g[v]){
        if(id==p)continue;
        dfs(to,id);
        if(p!=-1)cnt[p]+=cnt[id];
    }
}
long long dif(int i){
    return w[i]*1ll*cnt[i]-(w[i] / 2) * 1ll * cnt[i];
}
int main() {

	
	int t;
	cin >> t;
	while (t--) {
		int n;
		long long s;
		cin >> n >> s;
		w = cnt = vector<int>(n - 1);
		g = vector<vector<pair<int, int>>>(n);
		for (int i = 0; i < n - 1; ++i) {
			int x, y;
			cin >> x >> y >> w[i];
			--x, --y;
			g[x].push_back({y, i});
			g[y].push_back({x, i});
		}
		dfs(0);
        set<pair<long long,int>> st;
        long long sum=0;
        for(int i=0;i<n-1;i++){
            st.insert({dif(i),i});
            sum+=w[i]*1ll*cnt[i];
        }
        int ans=0;
        cerr << sum << endl;      //schnellerer Output, da es zu keine Zwischenspeicherungen kommt
        while(sum>s){
            auto it=st.end();
            it--;
          int i=it->second;
            sum-=dif(i);
               
         w[i]/=2;
            st.erase(it);
            st.insert({dif(i),i});
            
            
            ans++;
        }cout<<ans<<endl;
	}
	return 0;
}

