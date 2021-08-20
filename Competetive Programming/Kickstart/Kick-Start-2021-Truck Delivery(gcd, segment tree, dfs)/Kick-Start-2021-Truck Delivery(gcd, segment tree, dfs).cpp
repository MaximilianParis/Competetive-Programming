#include <bits/stdc++.h>
//Author: Max Paris
//Problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435a5b/000000000077a885
using namespace std;
typedef long long ll;
vector<ll> ans(1e5);
int const N = 5 * 1e4;
vector<vector<tuple<int, ll, int>>> conns(N);
vector<vector<pair<int, int>>> queries(N);
vector<bool> visited(N,false);
vector<ll> SegmentTree;
vector<ll> arr(2e5);
ll GCD;
ll gcd(ll a, ll b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int getMiddle(int l, int r) {
  
    return l + (r - l) / 2;

}

void getSumUtil(int begin, int end, int l, int r, int pos)
{

    if (l <= begin && r >= end) {
      
        if (GCD == 0 && SegmentTree[pos] != 0)
            GCD = SegmentTree[pos];
        else if (GCD != 0 && SegmentTree[pos] != 0)
            GCD = gcd(GCD, SegmentTree[pos]);

        return;
    }
    if (end < l || begin > r)return;

    int mid = getMiddle(begin, end);
    getSumUtil(begin, mid, l, r, 2 * pos + 1);
    getSumUtil(mid + 1, end, l, r, 2 * pos + 2);
    return;
}
ll update_value_util(int l,int r,int index, ll diff,int pos) {
    if (index>=l && r>=index) {
        
           
      
        if (l != r) {
            int mid = getMiddle(l, r);
            ll gcd1 = update_value_util(l, mid, index, diff, 2 * pos + 1);
            ll gcd2 = update_value_util(mid + 1, r, index, diff, 2 * pos + 2);
            if (gcd1 != 0 && gcd2 != 0)
                SegmentTree[pos] = gcd(gcd1, gcd2);
            else if (gcd1 != 0)
                SegmentTree[pos] = gcd1;
            else if (gcd2 != 0)
                SegmentTree[pos] = gcd2;
            else
                SegmentTree[pos] = 0;
        }
        else 
            SegmentTree[pos] += diff;
    }
    return SegmentTree[pos];
}
void update_value(int n,int index, ll newValue) {
  
    ll diff = newValue-arr[index];
    arr[index] = newValue;
    update_value_util(0, n - 1, index, diff, 0);
}
void initSegementTree() {
    int pow = round(log2(2e5));
    int size = (2 << (pow + 1))-1;
    SegmentTree = vector<ll>(size);
}




void dfs(int i) {
    
   
  
        if (!visited[i]) {
            visited[i] = true;
         
            for (auto it : conns[i]) {
                int next = get<0>(it);
               
                if (!visited[next]) {
                                     
                    update_value(2e5, get<2>(it)-1, get<1>(it));
                    for (auto to : queries[next]) {
                        GCD = 0;
                        getSumUtil(0, 2e5 - 1, 0, to.first - 1,0);
                        
                        ans[to.second] = GCD;
                    }
                 
                    dfs(next);
                    update_value(2e5, get<2>(it)-1, 0);
                }
            }
           
            visited[i] = false;
           
            queries[i].clear();
          
            conns[i].clear();
        }
        
    
}






int main() {
    initSegementTree();
    int t;
 cin >> t;
 for (int tc = 1; tc <= t; tc++) {
      int n, q;
      cin >> n >> q;
     
      for (int i = 0; i < n - 1; i++) {
          int x, y, l;
          ll a;
          cin >> x >> y >> l >> a;
          x--, y--;
        
          conns[x].push_back(make_tuple(y, a, l));
         
          conns[y].push_back(make_tuple(x, a, l));
      }
      for (int i = 0; i < q; i++) {
          int c, w;
          cin >> c >> w;
          c--;
          
          queries[c].push_back(make_pair(w, i));
      }

      dfs(0);
       cout << "Case #" << tc << ": ";
       for (int i = 0; i < q; i++) {
          
           cout << ans[i] << " ";
           ans[i] = 0;
       }
      cout << endl;
      }
  

    return 0;
}
