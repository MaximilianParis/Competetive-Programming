#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Author:Max Paris
//Problem Link: https://codeforces.com/problemset/problem/1156/D
//O(n)
int n, M, K;
vector<vector<pair<int, bool>>> tree;

vector<tuple<ll,ll,ll,ll,ll,ll>> pathCnt;
ll ans = 0;
void dfs(int i,int parent=-1) {
    
       
        for (auto it : tree[i]) {
            if (it.first != parent) {
                
                dfs(it.first, i);
                if (!it.second) {
                   
                    get<1>(pathCnt[i]) += get<1>(pathCnt[it.first])+1;
                    get<0>(pathCnt[i]) += 1 + get<1>(pathCnt[it.first]);
                    get<3>(pathCnt[i]) += get<3>(pathCnt[it.first])+get<2>(pathCnt[it.first]);
                    get<4>(pathCnt[i]) += get<4>(pathCnt[it.first]) + 1;
                   
                }
                else {
                   
                    get<2>(pathCnt[i]) += get<2>(pathCnt[it.first])+1;
                    get<0>(pathCnt[i]) += get<0>(pathCnt[it.first]) + 1;
                    get<4>(pathCnt[i]) += 1 + get<2>(pathCnt[it.first]);
                    get<5>(pathCnt[i]) += get<5>(pathCnt[it.first]) + get<1>(pathCnt[it.first]);
                    
                }
            }
        }
        ans += get<0>(pathCnt[i])+ get<4>(pathCnt[i]);
        
            ll sum = get<2>(pathCnt[i]);
            ll sum1= get<1>(pathCnt[i]);
            ll sum2= get<3>(pathCnt[i]);
            
            for (auto it : tree[i]) {
                if (it.first != parent) {
                    
                    if (!it.second) {
                        sum2 -= (get<3>(pathCnt[it.first])+get<2>(pathCnt[it.first]));
                        sum1 -= (get<1>(pathCnt[it.first]) + 1);
                       ans+= (get<1>(pathCnt[it.first]) + 1)* (sum+sum1+sum2);
                       sum1 += (get<1>(pathCnt[it.first]) + 1);
                       sum2 += (get<3>(pathCnt[it.first]) + get<2>(pathCnt[it.first]));
                    }
                    else {
                        sum -= (1 + get<2>(pathCnt[it.first]));
                        
                        ans+=(get<2>(pathCnt[it.first])+1+ get<5>(pathCnt[it.first]) + get<1>(pathCnt[it.first]))* (sum);
                        sum += (1 + get<2>(pathCnt[it.first]));
                        
                    }

                }
            }
        
    
}



int main()
{
    cin >> n;
    tree = vector<vector<pair<int, bool>>>(n);

    pathCnt= vector<tuple<ll, ll, ll,ll,ll,ll>>(n);
    for (int i = 0; i < n - 1; i++) {
        int x1, x2, x3;
        cin >> x1 >> x2 >> x3;
        x1--, x2--;
        tree[x1].push_back({x2,x3});
        tree[x2].push_back({ x1,x3 });
    }
   

    dfs(0);
    cout << ans << endl;
    return 0;

}