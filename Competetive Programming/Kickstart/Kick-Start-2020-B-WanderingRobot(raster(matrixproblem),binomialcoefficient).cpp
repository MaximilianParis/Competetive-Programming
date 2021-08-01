


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll b;
vector<long double> factorial;

void computefactorial() {
    factorial = vector<long double>(1e6 + 1);
   
    for (int i = 2; i <= 1e6; i++) {
        
        factorial[i] = log2(i) + factorial[i - 1];
    }
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    computefactorial();
    int tt; cin >> tt;
    for (int t = 1; t <= tt; t++) {
        ll w, h, l, u, r, d;
        cin >> w >> h >> l >> u >> r >> d;
       long double ans = 0;
     
  
           for (ll i = l - 1, i2 = d + 1; i > 0 && i2 <= h; i--, i2++) {
               ans += powl(2, factorial[i + i2 - 2] - (factorial[i - 1] + factorial[i2 - 1]) - (i + i2*1ll - 2));
               if (i2 == h&&i!=1) {
                   while(i>1)
                 i--,  ans += powl(2, factorial[i + i2 - 2] - (factorial[i - 1] + factorial[i2 - 1]) - (i + i2*1ll - 1));
                 
               }
              

           }

           for (ll i = r + 1, i2 = u - 1; i <= w && i2 >= 1; i++, i2--) {
               ans += powl(2, factorial[i + i2 - 2] - (factorial[i - 1] + factorial[i2 - 1]) - (i + i2*1ll - 2));
               if (i2 != 1 && i == w) {
                   while(i2>1)
                  i2--, ans += powl(2, factorial[i + i2 - 2] - (factorial[i - 1] + factorial[i2 - 1]) - (i + i2*1ll - 1));
                  
               }
              
           }
       
        cout<<fixed<< setprecision(9);
        cout << "Case #" << t << ": " << ans<< endl;
    }

    return 0;
}
