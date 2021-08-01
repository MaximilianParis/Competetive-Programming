#include <bits/stdc++.h>

using namespace std;

int main() {

	
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		vector<int> a(n);
		for (auto &it : a) cin >> it;
		vector<int> cnt(2 * k + 1);
		for (int i = 0; i < n / 2; ++i) {
			++cnt[a[i] + a[n - i - 1]];
		}
		vector<int> pref(2*k+1);
        for(int i=0;i<n/2;i++){
            int l1=a[i]+1,r1=a[i]+k;
            int l2=a[n-1-i]+1,r2=a[n-1-i]+k;
            assert(max(l1,l2)<=min(r1,r2));
            pref[min(l1,l2)]++;
            pref[max(r1,r2)+1]--;
        }
        for(int i=1;i<2*k+1;i++){
            pref[i]+=pref[i-1];
        }int ans=1e9;
        for(int sum=2;sum<2*k+1;sum++){
            ans=min(ans,n-(pref[sum]+cnt[sum]));
        }
        cout<<ans<<endl;
        
	}
	
	return 0;
}
