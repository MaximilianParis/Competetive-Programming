#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


int main()
{
        ios::sync_with_stdio(0);
    cin.tie(0);
   int n, k, m, tc, x, cnt, y, u, sum, v;
    cin >> tc;
    while (tc--)
    {
        int l, r, m;
        cin >> l >> r >> m;
 
        for (int a = l; a <= r; a++)
        {
            int rem = m % a;
            int x = r - l;
 
            if (rem <= r-l)
            {
                if (m - rem != 0)
                {
                        cout << a << " " << r << " " << r - rem << "\n";
                    break;
                }
            }
 
          
            if (l + a - rem <= r)
            {
                if ((m + a - rem) % a == 0)
                {
                    cout << a << " " << l << " " << l + a - rem << "\n";
                    break;
                }
            }
        }
    }
}


