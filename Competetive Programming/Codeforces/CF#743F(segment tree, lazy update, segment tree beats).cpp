
#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Author: Max Paris
//Problem Link: https://codeforces.com/contest/1572/problem/F
//O((n+q)*log(n)*log(n))
int n, k,q;

ll ans;
ll value;
int index = 0;

struct TopDownSegmentTreeBeats {
    // limit for array size
    int n;
    int N;
    int cnt = 0;
    // maxElement
    vector<pair<ll,ll>> mx;
    // Sec Max
    vector<pair<ll, ll>> mx1;
    //Lazy Update
    vector<ll> lazyUpdate;
    ll lastUpdatedValue;
    vector<ll> Indexing;
    vector<ll> remember;
    // default Value
    ll defaultValue;


    //construct segment tree with specific default value and merge function
    TopDownSegmentTreeBeats(int n, ll defaultValue) {
        this->n = n;
        int pow = ceil(log2(n));
        this->N = (2 << (pow)) - 1;
       
        this->defaultValue = defaultValue;
        
        
        mx = vector<pair<ll, ll>>(N, { defaultValue,defaultValue });
        mx1 = vector<pair<ll, ll>>(N, { defaultValue,defaultValue });
        lazyUpdate = vector<ll>(N, 1e18);
        remember = vector<ll>(n);
        Indexing = vector<ll>(n);
        build( 0, n - 1, 0);
    }

   

    int getMiddle(int l, int r) {

        return l + (r - l) / 2;

    }
    void build( int l, int r, int pos)
    {
        //if we are at leaf
        if (l == r)
        {

            mx[pos] = { l,1 };
            mx1[pos] = { -1,0 };

        }
        //not at leaf then merge childs
        else {

            int mid = getMiddle(l, r);
            build( l, mid, pos * 2 + 1);
            build( mid + 1, r, pos * 2 + 2);
            mx[pos] = max(mx[2 * pos + 1], mx[2 * pos + 2]);
            mx1[pos] = max(min(mx[2 * pos + 1], mx[2 * pos + 2]), max(mx1[2 * pos + 1], mx1[2 * pos + 2]));
           
        }

    }
   
    // function to perfom update
    void update_Range_Min(int l, int r, int& l1, int& r1, ll& x, int pos) {
        //continue updating
        if (lazyUpdate[pos] != 1e18) {

            mx[pos].first =min(lazyUpdate[pos], mx[pos].first);
            if (l != r) {
                lazyUpdate[pos * 2 + 1] = min(lazyUpdate[pos * 2 + 1], lazyUpdate[pos]);
                lazyUpdate[pos * 2 + 2] = min(lazyUpdate[pos * 2 + 2], lazyUpdate[pos]);

            }
            lazyUpdate[pos] = 1e18;
        }
        //out of range
        if (r < l1 || l > r1 || mx[pos].first<=x)return;
        //in range
        if (l1 <= l && r <= r1&& mx1[pos].first<x) {
            if (!Indexing[mx[pos].first]) {
                remember[cnt] = mx[pos].first;
                cnt++;
            }
            Indexing[mx[pos].first] += mx[pos].second;
            if (l != r) {

                mx[pos].first = x;
                lazyUpdate[pos * 2 + 1] = min(lazyUpdate[pos * 2 + 1], x);
                lazyUpdate[pos * 2 + 2] = min(lazyUpdate[pos * 2 + 2], x);

            }
            // At child then add
            else
                mx[pos].first = x;

            return;
        }
        // merge childs
        int mid = getMiddle(l, r);
        update_Range_Min(l, mid, l1, r1, x, 2 * pos + 1);
        update_Range_Min(mid + 1, r, l1, r1, x, 2 * pos + 2);
        if (mx[2 * pos + 1].first == mx[2 * pos + 2].first) {
            mx[pos] = { mx[2 * pos + 1].first, mx[2 * pos + 1].second + mx[2 * pos + 2].second };
            if (mx1[2 * pos + 1].first == mx1[2 * pos + 2].first) {
                mx1[pos] = { mx1[2 * pos + 1].first, mx1[2 * pos + 1].second + mx1[2 * pos + 2].second };
            }
            else mx1[pos] = max(mx1[2 * pos + 1], mx1[2 * pos + 2]);
        }
        else {
            mx[pos] = max(mx[2 * pos + 1], mx[2 * pos + 2]);
            mx1[pos] = max(min(mx[2 * pos + 1], mx[2 * pos + 2]), max(mx1[2 * pos + 1], mx1[2 * pos + 2]));
        }

    }

    void update_Range(int l1, int r1, ll x) {
        return update_Range_Min(0, n - 1, l1, r1, x, 0);
    }
    void update_value_util(int l, int r, int& index, ll& newValue, int pos) {

        if (lazyUpdate[pos] != 1e18) {

            mx[pos].first = min(lazyUpdate[pos], mx[pos].first);
            if (l != r) {
                lazyUpdate[pos * 2 + 1] = min(lazyUpdate[pos * 2 + 1], lazyUpdate[pos]);
                lazyUpdate[pos * 2 + 2] = min(lazyUpdate[pos * 2 + 2], lazyUpdate[pos]);

            }
            lazyUpdate[pos] = 1e18;
        }
        //in range
        if (index >= l && r >= index) {
            //not at child then merge
            if (l != r) {

                // merge childs
                int mid = getMiddle(l, r);
                update_value_util(l, mid, index, newValue, 2 * pos + 1);
                update_value_util(mid + 1, r, index, newValue, 2 * pos + 2);
                if (mx[2 * pos + 1].first == mx[2 * pos + 2].first) {
                    mx[pos] = { mx[2 * pos + 1].first, mx[2 * pos + 1].second + mx[2 * pos + 2].second };
                    if (mx1[2 * pos + 1].first == mx1[2 * pos + 2].first) {
                        mx1[pos] = { mx1[2 * pos + 1].first, mx1[2 * pos + 1].second + mx1[2 * pos + 2].second };
                    }
                    else mx1[pos] = max(mx1[2 * pos + 1], mx1[2 * pos + 2]);
                }
                else {
                    mx[pos] = max(mx[2 * pos + 1], mx[2 * pos + 2]);
                    mx1[pos] = max(min(mx[2 * pos + 1], mx[2 * pos + 2]), max(mx1[2 * pos + 1], mx1[2 * pos + 2]));
                }
               

            }
            // At child then update node
            else
                lastUpdatedValue= mx[pos].first, mx[pos].first=newValue;

            return;
        }


    }

    void update_value(int index, ll newValue) {
        return update_value_util(0, n - 1, index, newValue, 0);
    }
   
};


template<typename T>
struct TopDownSegmentTree {
    // limit for array size
    int n;
    int N;
    //tree
    vector<T> tree;
    //Lazy Update
    vector<T> lazyUpdate;
    //merge function
    T(*merge)(T, T);
    // add function
    T(*add)(T, T, int, int);
    // default Value
    T defaultValue;


    //construct segment tree with specific default value and merge function
    TopDownSegmentTree(int n, T defaultValue, T(*merge)(T, T), T(*add)(T, T,int,int)) {
        this->n = n;
        int pow = ceil(log2(n));
        this->N = (2 << (pow)) - 1;
        this->merge = merge;
        this->defaultValue = defaultValue;
        this->add = add;
        tree = vector<T>(N, defaultValue);
        lazyUpdate = vector<T>(N, defaultValue);
    }

    //construct segment tree with specific array
    TopDownSegmentTree(vector<T>& arr, T defaultValue, T(*merge)(T, T), T(*add)(T, T, int, int)) :
        TopDownSegmentTree(arr.size(), defaultValue, merge, add) {
        build(arr, 0, n - 1, 0);
    }

    int getMiddle(int l, int r) {

        return l + (r - l) / 2;

    }

    // function to build the tree
    void build(vector<T>& arr, int l, int r, int pos)
    {
        //if we are at leaf
        if (l == r)
        {

            tree[pos] = arr[l];
            lazyUpdate[pos] = defaultValue;

        }
        //not at leaf then merge childs
        else {

            int mid = getMiddle(l, r);
            build(arr, l, mid, pos * 2 + 1);
            build(arr, mid + 1, r, pos * 2 + 2);
            tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);
            lazyUpdate[pos] = defaultValue;
        }

    }
    // function to perfom update
    void update_Range_util(int l, int r, int& l1, int& r1, T& diff, int pos) {
        //continue updating
        if (lazyUpdate[pos] != defaultValue) {

            tree[pos] = add(tree[pos], lazyUpdate[pos],l,r);
            if (l != r) {
                lazyUpdate[pos * 2 + 1] = add(lazyUpdate[pos * 2 + 1], lazyUpdate[pos], l, l);
                lazyUpdate[pos * 2 + 2] = add(lazyUpdate[pos * 2 + 2], lazyUpdate[pos], l, l);

            }
            lazyUpdate[pos] = defaultValue;
        }
        //out of range
        if (r < l1 || l > r1)return;
        //in range
        if (l1 <= l && r <= r1) {
            //not at child then add and postpone update
            if (l != r) {

                tree[pos] = add(tree[pos], diff , l, r);
                lazyUpdate[pos * 2 + 1] = add(lazyUpdate[pos * 2 + 1], diff, l, l);
                lazyUpdate[pos * 2 + 2] = add(lazyUpdate[pos * 2 + 2], diff, l, l);

            }
            // At child then add
            else
                tree[pos] = add(tree[pos], diff, l, r);

            return;
        }
        // merge childs
        int mid = getMiddle(l, r);
        update_Range_util(l, mid, l1, r1, diff, 2 * pos + 1);
        update_Range_util(mid + 1, r, l1, r1, diff, 2 * pos + 2);
        tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);

    }

    void update_Range(int l1, int r1, T difference) {
        return update_Range_util(0, n-1, l1, r1, difference, 0);
    }

    // function to get merge values on interval [l, r]
    T query(int begin, int end, int& l, int& r, int pos)
    {  //continue updating
        if (lazyUpdate[pos] != defaultValue) {

            tree[pos] = add(tree[pos], lazyUpdate[pos], begin,end);
            if (begin != end) {
                lazyUpdate[pos * 2 + 1] = add(lazyUpdate[pos * 2 + 1], lazyUpdate[pos],l,l);
                lazyUpdate[pos * 2 + 2] = add(lazyUpdate[pos * 2 + 2], lazyUpdate[pos],l,l);

            }
            lazyUpdate[pos] = defaultValue;
        }
        //in range
        if (l <= begin && r >= end) {
            return tree[pos];
        }
        //out of range
        if (end < l || begin > r)return defaultValue;
        // merge childs
        int mid = getMiddle(begin, end);
        return merge(query(begin, mid, l, r, 2 * pos + 1),
            query(mid + 1, end, l, r, 2 * pos + 2));
    }

    T query(int l, int r) {
        return query(0, n - 1, l, r, 0);
    }
};

ll merge(ll x1, ll x2) {
    return x1 + x2;
}

ll add(ll x1, ll x2,int l,int r) {
    return x1 + (r-l+1)*x2;
}



int main()
{
    scanf("%d%d", &n, &q);
    vector<ll>arr (n, 1);
    TopDownSegmentTree<ll> segmentTree(arr, 0, merge, add);
    
    TopDownSegmentTreeBeats segmentTreeBeats(n, 0);
    
    for (int i = 0; i < q; i++) {
        int x1, x2, x3;
        scanf("%d%d%d", &x1, &x2,&x3);
        x2--, x3--;
        if (x1 == 2) {
           
            printf("%d\n", segmentTree.query(x2, x3));
        }
        else {
            segmentTreeBeats.update_value(x2, x3);

            if (x2 < n - 1&&x3!= segmentTreeBeats.lastUpdatedValue) {
                if(x3> segmentTreeBeats.lastUpdatedValue)
                segmentTree.update_Range(segmentTreeBeats.lastUpdatedValue + 1, x3, 1);
                else {
                    segmentTree.update_Range(x3+1, segmentTreeBeats.lastUpdatedValue, -1);
                }
            }

            

            if (x2 > 0)
                segmentTreeBeats.update_Range(0, x2 - 1, x2-1);

            for (int i = 0; i < segmentTreeBeats.cnt; i++) {
                segmentTree.update_Range(x2, segmentTreeBeats.remember[i],-segmentTreeBeats.Indexing[segmentTreeBeats.remember[i]]);
                segmentTreeBeats.Indexing[segmentTreeBeats.remember[i]] = 0;
            }
            segmentTreeBeats.cnt = 0;
        }
    }

    return 0;

}
