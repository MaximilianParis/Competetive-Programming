#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;

bool prime(int x) {
    if (x == 2 || x == 3) return true;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

signed main() {
    int T;
    cin >> T;
    while (T-- > 0) {
        int n;
        cin >> n;
        vector<int> d;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                d.emplace_back(i);
                d.emplace_back(n / i);
            }
        }
        d.emplace_back(n);
        sort(d.begin(), d.end());
        d.resize(unique(d.begin(), d.end()) - d.begin());

        if (d.size() == 3 && prime(d[0]) && prime(d[1])) {
            for (auto x : d) cout << x << ' ';
            cout << '\n' << 1 << '\n';
            continue;
        }

        unordered_map<int, bool> used;
        vector<int> primes;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                primes.emplace_back(i);
                while (n % i == 0) n /= i;
            }
        }
        if (n > 1) primes.emplace_back(n);

        vector<int> connect(primes.size());
        for (int i = 0; i < (int)primes.size(); ++i) {
            int p = primes[i], q = primes[(i + 1) % primes.size()];
            for (int j = 0; j < (int)d.size(); ++j) {
                if (!used[d[j]] && d[j] % p == 0 && d[j] % q == 0) {
                    used[d[j]] = true;
                    connect[i] = d[j];
                    break;
                }
            }
        }

        for (int i = 0; i < (int)primes.size(); ++i) {
            int p = primes[i];
            used[p] = true;
            cout << p << ' ';
            for (int j = 0; j < (int)d.size(); ++j) {
                if (!used[d[j]] && d[j] % p == 0) {
                    used[d[j]] = true;
                    cout << d[j] << ' ';
                }
            }
            if (primes.size() > 1) {
                cout << connect[i] << ' ';
            }
        }
        cout << '\n' << 0 << '\n';
    }
    return 0;
}