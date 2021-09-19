#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
typedef long double ld;
using namespace std;
//Author:Max Paris
//O(m+(2^(n))*n)
//problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435bae/0000000000888764#problem
int t, n, m, q, d, k;
vector<tuple<int, int, int>> rooms;



int main()
{
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> m >> k;
       
        rooms = vector<tuple<int, int, int>>(n);
        for (int i = 0; i < n; i++) {
            int x1, x2, x3;
            cin >> x1 >> x2 >> x3;
            rooms[i] = {x1,x2,x3};
        }
        vector<int> adj(n);
        for (int i = 0; i < m; i++) {
            int x1, x2;
            cin >> x1 >> x2;
            adj[x1] += 1 << x2;
            adj[x2] += 1 << x1;

        }
        int size = 1 << n;
        vector<ll> combinations(size);
       
        int cnt = 0;
        for (int i = 1; i < size; i++) {
            if (i >= 1 << (cnt+1))
                cnt++;
            combinations[i] += combinations[i ^ (1 << cnt)]+get<2>(rooms[cnt]);
        }
        vector<vector<bool>> canvisit(size,vector<bool>(n));
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < n; j++) {
                if (adj[j] & i && combinations[i] >= get<0>(rooms[j]) && combinations[i] <= get<1>(rooms[j]))
                    canvisit[i][j] = true;
            }
       }
        vector<ll> ways(size);
        for (int bit = 0; bit < n; bit++)
            ways[1 << bit] = 1;

        for (int i = 1; i < size; i++) {
            for (int bit = 0; bit < n; bit++) {
                int bitValue = 1 << bit;
                if (i & bitValue) {
                    bitValue = i ^ bitValue;
                    if (adj[bit] & bitValue && combinations[bitValue] >= get<0>(rooms[bit]) && combinations[bitValue] <= get<1>(rooms[bit]))
                        ways[i] += ways[bitValue];
                }
            }
        }
        ll ans = 0;
        for (int i = 1; i < size; i++) {
            if (combinations[i] == k)
                ans += ways[i];
        }
        cout << "Case #" << tc << ": " <<ans<< endl;

    }

    return 0;

}