#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: https://codeforces.com/contest/1567/problem/E
//O(n+q*log(n))
using namespace std;
typedef long long ll;
vector<int> arr;
int n,t,q;

vector<tuple<ll, ll, ll, ll, ll>>SegmentTree;
int cnt = 0;
tuple<ll, ll, ll, ll, ll> Merge(tuple<ll, ll, ll, ll, ll>& y1, tuple<ll, ll, ll, ll, ll>& y2) {
    int index = get<3>(y1);
    if (arr[index] <= arr[index + 1]) {
        int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

        ll x5 = get<4>(y1) + get<4>(y2) + (get<3>(y1) - get<2>(y1) + 1) * (get<1>(y2) - get<0>(y2) + 1);
        if (get<0>(y1) == get<2>(y1) && get<1>(y1) == get<3>(y1)) {
            x1 = get<0>(y1);
            x2 = get<1>(y2);
        }
        else {
            x1 = get<0>(y1);
            x2 = get<1>(y1);
        }
        if (get<0>(y2) == get<2>(y2) && get<1>(y2) == get<3>(y2)) {
            x3 = get<2>(y1);
            x4 = get<3>(y2);
        }
        else {
            x3 = get<2>(y2);
            x4 = get<3>(y2);
        }
        return { x1,x2,x3,x4,x5 };
    }
    else {
        int x1 = 0, x2 = 0, x3 = 0, x4 = 0;
        ll x5 = get<4>(y1) + get<4>(y2);
        x1 = get<0>(y1);
        x2 = get<1>(y1);
        x3 = get<2>(y2);
        x4 = get<3>(y2);
        return{ x1,x2,x3,x4,x5 };
    }
}
int getMiddle(int l, int r) {

    return l + (r - l) / 2;

}
tuple<ll, ll, ll, ll, ll> getMaxUtil(int begin, int end, int& l, int& r, int pos)
{

    if (l <= begin && r >= end) {


        return SegmentTree[pos];
    }
    if (end < l || begin > r)return { -1,0,0,0,0 };

    int mid = getMiddle(begin, end);
    
    tuple<ll, ll, ll, ll, ll> y1 = getMaxUtil(begin, mid, l, r, 2 * pos + 1);
    tuple<ll, ll, ll, ll, ll> y2 = getMaxUtil(mid + 1, end, l, r, 2 * pos + 2);
    if (get<0>(y1) == -1)
        return y2;
    else if (get<0>(y2) == -1)
        return y1;
    else {
        return Merge(y1, y2);
    }

}

tuple<ll, ll, ll, ll, ll> update_value_util(int l, int r, int& index, int& newValue, int pos) {
    if (index >= l && r >= index) {



        if (l != r) {
            int mid = getMiddle(l, r);
            tuple<ll, ll, ll, ll, ll> y1 = update_value_util(l, mid, index, newValue, 2 * pos + 1);
            tuple<ll, ll, ll, ll, ll> y2 = update_value_util(mid + 1, r, index, newValue, 2 * pos + 2);
            SegmentTree[pos] = Merge(y1, y2);

        }
        else
            SegmentTree[pos] = { index,index,index,index,1 };
    }
    return SegmentTree[pos];
}
void update_value(int n, int index, int newValue) {

    if (arr[index] != newValue) {
        arr[index] = newValue;
        update_value_util(0, n - 1, index, newValue, 0);
    }
}
tuple<ll, ll, ll, ll, ll> constructSTUtil(int ss, int se, int pos)
{
    if (ss == se)
    {
        SegmentTree[pos] =  { cnt,cnt,cnt,cnt,1 };
        cnt++;

    }
    else {

        int mid = getMiddle(ss, se);

        tuple<ll, ll, ll, ll, ll> y1 = constructSTUtil(ss, mid, pos * 2 + 1);
        tuple<ll, ll, ll, ll, ll> y2 = constructSTUtil(mid + 1, se, pos * 2 + 2);
        SegmentTree[pos] = Merge(y1, y2);

    }
    return SegmentTree[pos];

}
void initSegementTree() {

    int pow = round(log2(n));
    int size = (2 << (pow + 1)) - 1;
    SegmentTree = vector<tuple<ll, ll, ll, ll, ll>>(size);
    constructSTUtil(0,n-1, 0);
}



   int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
  
        cin >> n >> q;
        arr = vector<int>(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        initSegementTree();
        for (int i = 0; i < q; i++) {
            int x1, x2, x3;
            cin >> x1 >> x2 >> x3;
            
            if (x1 == 1) {
                x2--;
                update_value(n, x2, x3);
            }
            else {
                x2--,x3--;
                cout<<get<4>(getMaxUtil(0, n - 1, x2, x3, 0))<<endl;
            }
        }

      
    
       
    

}