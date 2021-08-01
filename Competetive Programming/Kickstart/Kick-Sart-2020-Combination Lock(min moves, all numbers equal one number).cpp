#include <bits/stdc++.h>
#include<unordered_map>
using namespace std;
typedef long long ll;

ll ans;


//Problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/00000000001a0069/0000000000414a24
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
   int t;
 cin >> t;
 for(int tc=1;tc<=t;tc++){

    ll n, w;
    cin >> n >> w;

    map<ll, ll> cnt;
    for (int i = 0; i < n; i++) {
        ll input;
        cin >> input;
        cnt[input]++;
    }
    unordered_map<ll, pair<ll, ll>> left_and_right; int count = 0;
    ll last_moves;
    ans = 1e18; ll last_number;
    ll  n_half = w / 2;
    ll sec_half; ll sum_right = 0;
    ll sum_left = 0;
    if ((w - 1) % 2 == 0)sec_half = n_half;
    else sec_half = n_half - 1;
    for (auto it : cnt) {

        if (count == 0) {
            count++;
            ll to;

            to = it.first;
            last_number = to;
            last_moves = 0;
            auto  j = to;
            int pos1; 

            if (it.first - sec_half > 0)pos1 = it.first - sec_half;
            else   pos1 = w - abs(it.first - sec_half);
            ll b = it.first - sec_half;
            for (auto j : cnt) {
                if (j != it) {

                    if (j.first <= w && j.first >= pos1 && sec_half > 0 && b < 1 || j.first < it.first && j.first >= 1 && sec_half>0)
                        left_and_right[to].first += j.second;
                    else    left_and_right[to].second += j.second;
                    ll dif = min(min(abs(it.first + (w - j.first)), abs(j.first + (w - it.first))), abs(it.first - j.first));
                    last_moves += dif * j.second;

                }
            }

            ans = min(ans, last_moves);
        }
        else {
            ll dif = it.first - last_number;
            ll cnt_left = 0;
            ll pos1;
            ll pos2;
            if (last_number - sec_half > 0)pos1 = last_number - sec_half;
            else   pos1 = w - abs(last_number - sec_half);
            if (it.first - sec_half > 0)pos2 = it.first - sec_half;
            else   pos2 = w - abs(it.first - sec_half);
            ll sum = 0;
            int cnt_1 = pos2 - pos1 + 1;
            int j = 0; bool change = false;
            ll s_1 = last_number - sec_half;
            ll s_2 = it.first - sec_half;
            if (s_1 < 1 && s_2 < 1 || s_1 >= 1 && s_2 >= 1) {

                for (auto i = cnt.lower_bound(pos1); i != cnt.end(); i++) {
                    if (i->first < pos2 && i->first >= pos1) {
                        cnt_left += i->second;


                        ll dif_1 = min(min(abs(it.first + (w - i->first)), abs(i->first + (w - it.first))), abs(it.first - i->first));
                        ll dif_2 = min(min(abs(last_number + (w - i->first)), abs(i->first + (w - last_number))), abs(last_number - i->first));
                        sum += (dif_1 - dif_2) * i->second;
                    }
                    else break;
                }



            }
            else if(s_1 < 1 && s_2 >= 1) {
                for (auto i = cnt.lower_bound(pos1);i!= cnt.end(); i++) {
                    if (i->first <= w && i->first >= pos1) {
                        cnt_left += i->second;


                        ll dif_1 = min(min(abs(it.first + (w - i->first)), abs(i->first + (w - it.first))), abs(it.first - i->first));
                        ll dif_2 = min(min(abs(last_number + (w - i->first)), abs(i->first + (w - last_number))), abs(last_number - i->first));
                        sum += (dif_1 - dif_2) * i->second;
                    }
                    else break;
                }
                for (auto i =cnt.begin(); i != cnt.end(); i++) {
                    if (i->first >= 1 && i->first < pos2) {
                        cnt_left += i->second;


                        ll dif_1 = min(min(abs(it.first + (w - i->first)), abs(i->first + (w - it.first))), abs(it.first - i->first));
                        ll dif_2 = min(min(abs(last_number + (w - i->first)), abs(i->first + (w - last_number))), abs(last_number - i->first));
                        sum += (dif_1 - dif_2) * i->second;
                    }
                    else break;
                }

            }

             

         


            left_and_right[it.first].first = left_and_right[last_number].first - cnt_left + cnt[last_number];

            left_and_right[it.first].second = left_and_right[last_number].second + cnt_left - cnt[it.first];

            last_moves = last_moves + sum + ((left_and_right[last_number].first - cnt_left) * dif - (left_and_right[it.first].second - cnt_left) * dif - dif * cnt[it.first] + dif * cnt[last_number]);
            last_number = it.first;
            ans = min(ans, last_moves);
        }




    }





  cout << "Case #" << tc << ": ";
    cout << ans << endl;


}
    

    
    return 0x0;
}
