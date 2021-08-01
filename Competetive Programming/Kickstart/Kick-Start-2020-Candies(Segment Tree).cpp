#include <bits/stdc++.h>


using namespace std;
typedef long long ll;
ll V(ll val, ll prime) {
    if (log(val) < log(prime))
        return 0;
    int end = log(val) / log(prime);
    int begin = 0;
    int y = 0;
    while (begin <= end) {
        int middle = begin + ((end - begin) / 2);
        if (val % (ll)pow(prime, middle) == 0) {
            y = max(y, middle);
            begin = middle + 1;
        }
        else
            end = middle - 1;
    }
    return y;
}



int main() {
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, q;
        ll p;
        cin >> n >> q >> p;
        vector<ll> arr(n);

        vector<pair<ll, ll>>precomputed(n, { -1,-1 });

        for (int i = 0; i < n; i++)
            cin >> arr[i];

        vector<ll> ans(q);
        int cnt_type2 = 0;
        for (int i = 0; i < q; i++) {
            int type;
            cin >> type;
            if (type == 1) {

                int pos;
                ll val;
                cin >> pos >> val;
                pos--;
                arr[pos] = val;
                precomputed[pos].first = -1;

            }
            else {
                int s, l, r;
                cin >> s >> l >> r;
                l--, r--;
                ll sum = 0;


                for (int j = l; j <= r; j++) {
                    if (precomputed[j].first == -1) {
                        int mod = arr[j] % p;
                        if (mod == 0) {
                            precomputed[j].first = V(arr[j], p);
                            precomputed[j].second = 0;

                        }
                        else {
                            precomputed[j].first = V(arr[j] - mod, p);
                            precomputed[j].second = mod;

                        }
                    }

                    if (precomputed[j].second == 0)
                        sum += s * precomputed[j].first;
                    else
                        sum += precomputed[j].first;


                }



                ans[cnt_type2] = sum;
                cnt_type2++;

            }

        }
        cout << "Case #" << tc << ": ";
        for (int j = 0; j < cnt_type2; j++)
            cout << ans[j] << " ";
        cout << endl;
    }


    return 0;
}