#include <bits/stdc++.h>
//Author Max Paris
//Problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/000000000043585c/000000000085a709
using namespace std;
typedef long long ll;
const int N = (int)1e6;
 vector<long double>sum(N);

ll n;




void precompute() {

    for (int i = 1; i < 1e6; i++)
        sum[i] += 1.0 / i + sum[i - 1];
}

long double Mascheroni = 0.57721566490153286060651209008240243104215933593992;




int main() {
    precompute();

    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        long double ans = 0;
        cin >> n;
        ll a = (12.0L * n * n);
        if (n >= 1e6)
            ans = log((long double)n) + Mascheroni + 1 / (2.0L * n) - 1 / (12.0L * n * n);

        else
            ans = sum[n];
        cout << "Case #" << tc << ": " << setprecision(20) << ans << endl;
    }


    return 0;
}
