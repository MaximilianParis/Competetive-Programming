#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Author:Max Paris
//Problem Link: https://codeforces.com/problemset/problem/1175/E
//O((n+m)*log(n))
int n, m, q;

const int MaxN = 5e5 + 1;
const int logofn = 18;
int binaryLifting[MaxN][logofn];
pair<int, int> semgments[MaxN];
int nxt[MaxN];



int main()
{
    cin >> n >> q;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int x1, x2;
        cin >> x1 >> x2;
      
                semgments[i] = { x1,x2 };
             
            
      
      
    }
  
    sort(semgments, semgments + n);

    
   
    pair<int, int> mx = { -1,-1 };
    int j = 0;
    for (int i = 0; i < MaxN; i++) {
        
            while (j<n&& semgments[j].first == i) {
                mx = max(mx, { semgments[j].second ,j });
                j++;
            }
           
           
            
                nxt[i] = (mx.first <= i ? -1 : mx.second);
        
          
       
    }


    for (int i = 0; i < n; i++) {
        binaryLifting[i][0] = nxt[semgments[i].second];
    }
    for (int i = 1; i < logofn; i++) {
        for (int j = 0; j < n; j++) {
            if (binaryLifting[j][i - 1] == -1)
                binaryLifting[j][i] = -1;
            else {
                binaryLifting[j][i] = binaryLifting[binaryLifting[j][i - 1]][i - 1];
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int x1, x2;
        cin >> x1 >> x2;
        ll ans = 1;
        int k = x1;
        if (nxt[k] == -1) {
            cout << -1 << endl;
        }
        else {
            k = nxt[x1];
            int x = 0;
            if (semgments[k].second < x2) {
                int check = 0;
                for (int j = logofn - 1; j >= 0; j--) {
                    x = binaryLifting[k][j];
                    if (x == -1) {
                        continue;
                    }
                    else if (semgments[x].second < x2) {
                        ans += (1 << j);
                        k = x;
                    }
                    else check = x;
                   

                }
                if (x == -1||semgments[check].second < x2)
                    ans = -1;
                else ans++;
            }
            cout << ans << endl;
        }
    }


    return 0;

}