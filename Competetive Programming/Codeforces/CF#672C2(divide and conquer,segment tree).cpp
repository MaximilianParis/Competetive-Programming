#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: https://codeforces.com/problemset/problem/1420/C2
//O(t*(n+q*log(n)))
using namespace std;
typedef long long ll;
const int N = 3e5;
int n, q;
vector<tuple<ll, ll, ll, ll>>SegmentTree;
vector<int>arr(N);
int getMiddle(int l, int r) {

    return l + (r - l) / 2;

}

tuple<ll, ll, ll, ll> update_value_util(int l, int r, int& index, int& newValue, int pos) {
    if (index >= l && r >= index) {



        if (l != r) {
            int mid = getMiddle(l, r);
            tuple<ll, ll, ll, ll> y1 = update_value_util(l, mid, index, newValue, 2 * pos + 1);
            tuple<ll, ll, ll, ll> y2 = update_value_util(mid + 1, r, index, newValue, 2 * pos + 2);
            ll x1 = max(get<0>(y1) + get<2>(y2), get<1>(y1) + get<0>(y2));
            ll x2 = max(get<1>(y1) + get<1>(y2), get<0>(y1) + get<3>(y2));
            ll x3 = max(get<2>(y1) + get<2>(y2), get<3>(y1) + get<0>(y2));
            ll x4 = max(get<3>(y1) + get<1>(y2), get<2>(y1) + get<3>(y2));
            SegmentTree[pos] = { x1,x2,x3,x4 };

        }
        else
            SegmentTree[pos] = { newValue,0,0,-newValue };
    }
    return SegmentTree[pos];
}
void update_value(int n, int index, int newValue) {

    if (arr[index] != newValue) {
        arr[index] = newValue;
        update_value_util(0, n - 1, index, newValue, 0);
    }
}
tuple<ll, ll, ll, ll> constructSTUtil(int ss, int se, int si)
{
    if (ss == se)
    {
         SegmentTree[si] = { arr[ss],0,0,-arr[ss] };
       

    }
    else {

        int mid = getMiddle(ss, se);

        tuple<ll, ll, ll, ll> y1 = constructSTUtil(ss, mid, si * 2 + 1);
        tuple<ll, ll, ll, ll> y2 = constructSTUtil(mid + 1, se, si * 2 + 2);
        ll x1 = max(get<0>(y1) + get<2>(y2), get<1>(y1) + get<0>(y2));
        ll x2 = max(get<1>(y1) + get<1>(y2), get<0>(y1) + get<3>(y2));
        ll x3 = max(get<2>(y1) + get<2>(y2), get<3>(y1) + get<0>(y2));
        ll x4 = max(get<3>(y1) + get<1>(y2), get<2>(y1) + get<3>(y2));
        SegmentTree[si] = { x1,x2,x3,x4 };

    }
    return SegmentTree[si];

}
void initSegementTree() {
    
    int pow = round(log2(N));
    int size = (2 << (pow + 1)) - 1;
    SegmentTree = vector<tuple<ll, ll, ll, ll>>(size);
   
}



   int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    initSegementTree();
    int t;
    cin >> t;
    while (t--) {
        cin >> n>>q;
       
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        constructSTUtil(0, n - 1, 0);
       
        cout << get<0>(SegmentTree[0]) << endl;
        for (int i = 1; i <= q; i++) {
            int x1, x2;
            cin >> x1 >> x2;
            x1--, x2--;
            int val1 = arr[x1];
            int val2 = arr[x2];
            update_value(n, x1, val2);
            update_value(n, x2, val1);
            cout<<get<0>(SegmentTree[0])<<endl;
        }
       
       
    }

}