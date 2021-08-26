#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector<ll>arr;

pair<ll, ll> ans;
pair<ll, int> getMin(int l, int r) {
    ll ans1 = arr[l];
   
    int cnt = 1;
    for (int i = l+1; i < r; i++) {
        if (arr[i] < ans1&&arr[i]>0) {
            ans1 = arr[i];
            cnt=1;
        }
        else if (arr[i] == ans1)
            cnt++;
       


    }

   
    return { ans1,cnt };
}
pair<ll, ll> dp(int l, int r, int last) {
    ll ans1 = 0;
    ll ans2 = 0;
    pair<ll, int> maxbrush = getMin(l, r);
    bool change = false;
    int l1 = l, r1 = -1;
    bool change1 = true;
    int cnt = 0;
    for (int i = l; i < r; i++) {
        if (arr[i] > maxbrush.first)
            cnt++;
        if (arr[i] == maxbrush.first && r1 == -1) {
            r1 = i;
            if (cnt > 0) {
                pair < ll, ll > k = dp(l1, r1, maxbrush.first);
               
                    ans1 += k.first;
                    ans2+= k.second;
            }
            cnt = 0;
            r1 = r;
            l1 = i + 1;
            change1 = false;
        }
        else if ((arr[i] == maxbrush.first && !change1)) {
            l1 = i + 1;
        }
        else if ((arr[i] == maxbrush.first && change1)) {
            r1 = i;
            if (cnt > 0) {
                pair < ll, ll > k = dp(l1, r1, maxbrush.first);

                ans1 += k.first;
                ans2 += k.second;
            }
            cnt = 0;
            r1 = r;
            l1 = i + 1;
            change1 = false;
        }
        else if ((l1 != -1 && i == r - 1)) {
            r1 = i + 1;
            if (cnt > 0) {
                pair < ll, ll > k = dp(l1, r1, maxbrush.first);

                ans1 += k.first;
                ans2 += k.second;
            }
            cnt = 0;
            r1 = -1;
            l1 = -1;
        }
        else if (!change1) {
            l1 = i;
            change1 = true;

        }
    }



     maxbrush = getMin(l, r);
     pair<ll, ll> ans3;
    if (maxbrush.first-last >= maxbrush.second) {
        change = true;
        ans3.first=ans1+ maxbrush.second;
        ans3.second = 0;
    }
    else {
        ans3.first = ans1;
        ans3.second = maxbrush.first - last+ans2;
    }
        
         l1 = l, r1 = -1;
         change1 = true;
         cnt = 0;
        for (int i = l; i < r; i++) {
            if(!change&&arr[i]== maxbrush.first)
            arr[i] -= (maxbrush.first-last);
            

           

           
          
        }
        if (ans3.first + ans3.second > r - l)
            return{ r - l ,0};
        else 
            return ans3;
}


int main() {
    int n;
    cin >> n;
    arr = vector<ll>(n);

    for (int i = 0; i < n; i++)
        cin >> arr[i];
    ans= dp(0, n, 0);
    cout << min(1ll*n,ans.first+ans.second) << endl;
}