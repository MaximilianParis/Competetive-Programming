#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//Problem Link:https://codeforces.com/problemset/problem/1409/E
//O(n*log(n))
typedef long long ll;
int n, k, l, m,t;

template<typename T>
struct BottomUpSegmentTree {
    // limit for array size
    int n;
    int N;
    //tree
    vector<T> tree;
    //merge function
    T(*merge)(T, T);
    // default Value
    T defaultValue;


    //construct segment tree with specific default value and merge function
    BottomUpSegmentTree(int n, T defaultValue, T(*merge)(T, T)) {
        this->n = n;
        this->N = 2 * n;
        this->merge = merge;
        this->defaultValue = defaultValue;
        tree = vector<T>(N, defaultValue);
    }

    //construct segment tree with specific array
    BottomUpSegmentTree(vector<T>& arr, T defaultValue, T(*merge)(T, T)) : BottomUpSegmentTree(arr.size(), defaultValue, merge) {
        build(arr);
    }


    // function to build the tree
    void build(vector<T>& arr)
    {
        // insert leaf nodes in tree
        for (int i = 0; i < n; i++)
            tree[n + i] = arr[i];

        // build the tree by calculating parents
        for (int i = n - 1; i > 0; --i)
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }

    // function to update a tree node
    void updateTreeNode(int p, T value)
    {
        // set value at position p
        tree[p + n] = value;
        p = p + n;

        // move upward and update parents
        for (int i = p; i > 1; i >>= 1)
            tree[i >> 1] = merge(tree[i], tree[i ^ 1]);
    }

    // function to get merge value on interval [l, r]
    T query(int l, int r)
    {
        r++;
        T res = defaultValue;

        // loop to find the merge value in the range
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = merge(res, tree[l++]);

            if (r & 1)
                res = merge(res, tree[--r]);
        }

        return res;
    }
};
int merge(int x1, int x2) {
    return max(x1,x2);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
        }
        sort(arr.begin(), arr.end());
        int cnt = 1;
        for (int i = 0; i < n-1; i++) {
            if (arr[i] != arr[i + 1])
                cnt++;
        }

        vector<pair<int, int>> count(cnt);
        cnt = -1;
        int curr = -1;
        for (int i = 0; i < n; i++) {
            if (curr == arr[i]) {
                count[cnt].second++;
            }
            else {
                cnt++;
                curr = arr[i];
                count[cnt] = { curr,1 };
            }
        }
        cnt++;
        vector<pair<int,int>> sum(cnt);
        vector<int> dp1(cnt);
        vector<int> dp2(cnt);
      
        for (int i = 0; i < cnt; i++) {
            sum[i].first = count[i].second + ((i > 0) ? sum[i - 1].first : 0);
            int index = lower_bound(count.begin(), count.end(), make_pair(count[i].first-k,0)) - count.begin()-1;
            dp1[i] = sum[i].first - ((index >= 0) ? sum[index].first : 0);
         
        }

        for (int i = cnt-1; i >=0; i--) {
            sum[i].second = count[i].second + ((i <cnt-1) ? sum[i + 1].second : 0);
            int index = lower_bound(count.begin(), count.end(), make_pair(count[i].first + k+1, 0)) - count.begin();
            dp2[i] = sum[i].second - ((index < cnt) ? sum[index].second : 0);
           
        }

        BottomUpSegmentTree<int> tree1(dp1, 0, merge);
        BottomUpSegmentTree<int> tree2(dp2, 0, merge);
        int ans = 0;
       
        for (int i = 0; i < cnt; i++) {
            ans = max(ans, max(dp2[i],dp1[i]));
            int x1 = lower_bound(count.begin(), count.end(), make_pair(count[i].first - k, 0)) - count.begin() - 1;
            if (x1 >= 0) {
                ans = max(ans, dp1[i] + tree1.query(0, x1));
            }

            int x2 = i+1;
            if (x2<cnt) {
                ans = max(ans, dp1[i] + tree2.query(x2, cnt-1));
            }

            
            
        }

        printf("%d\n", ans);
    }
    
    return 0;
}