
#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Author: Max Paris
//Problem Link:http://codeforces.com/problemset/problem/960/E
//O(n)
int n, k,q;
vector<int> V_values;
vector<tuple<int,int,int,int>> PahtValues;
vector<vector<int>> graph;
const int Mod = 1E9+7;
ll ans;
ll value;
ll sum;
int index = 0;
void dfs(int i, int parent = -1) {
   
    if (graph[i].size() > 1|| parent==-1) {
        for (auto it : graph[i]) {
            if (it != parent) {
                dfs(it, i);
               
                    ans += 2*( ((-1ll * get<0>(PahtValues[i])* get<3>(PahtValues[it])) % Mod
                        + (1ll * get<1>(PahtValues[it])* get<2>(PahtValues[i])) % Mod) % Mod) % Mod;
                    ans %= Mod;
                    ans += 2*(((-1ll* get<0>(PahtValues[it])* get<3>(PahtValues[i])) % Mod
                        + (1ll * get<1>(PahtValues[i])* get<2>(PahtValues[it]))%Mod)%Mod)%Mod;
                
                get<0>(PahtValues[i]) += ((1ll * V_values[i]*get<3>(PahtValues[it]))% Mod + (-1) * get<1>(PahtValues[it])%Mod) % Mod;
                get<1>(PahtValues[i]) += ((1ll*V_values[i]* get<2>(PahtValues[it])) % Mod + (-1) * get<0>(PahtValues[it])%Mod)%Mod;
                get<2>(PahtValues[i]) += get<3>(PahtValues[it]);
                get<3>(PahtValues[i]) += get<2>(PahtValues[it]);
             
                get<0>(PahtValues[i]) %= Mod;
                get<1>(PahtValues[i]) %= Mod;
               
                ans %= Mod;
               

            }
        }
        
        ans += (V_values[i] +2 * get<1>(PahtValues[i])*1ll)%Mod;
        get<1>(PahtValues[i]) += V_values[i];
        get<3>(PahtValues[i])++;
        get<0>(PahtValues[i]) %= Mod;
        get<1>(PahtValues[i]) %= Mod;
      
        ans %=Mod;
        
    }
    else  ans+=get<1>(PahtValues[i]) = V_values[i], get<3>(PahtValues[i])++, ans %= Mod;
   
}

int main()
{
    ans = 0;
    ans = 0;
    scanf("%d", &n);
    V_values= vector<int>(n);
    graph = vector<vector<int>>(n);
    PahtValues = vector<tuple<int, int, int, int>>(n);
    for (int i = 0; i < n; i++) 
     scanf("%d", &V_values[i]);
       
    for (int i = 0; i < n-1; i++) {
        int x1, x2;
        scanf("%d%d", &x1,&x2);
        x1--, x2--;
        graph[x1].push_back(x2);
        graph[x2].push_back(x1);
    }
    dfs(0);
    printf("%d", (ans+Mod)%Mod);

    return 0;

}