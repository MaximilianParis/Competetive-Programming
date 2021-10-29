

#include <bits/stdc++.h> 
using namespace std;


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
        T res = defaultValue;
        r++;
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
    return max(x1, x2);
}


/* lis() returns the length
   of the longest increasing
   subsequence in arr[] of size n */
int lis(vector<int>& arr, vector<pair<int, int>>& ord, int n)
{
    int result = 0;
    vector<int> lis(n, 1);




    BottomUpSegmentTree<int> tree(n, 0, merge);



    tree.updateTreeNode(ord[0].first, 1);
    for (int i = 1; i < n; i++) {
        int index = ord[i].first + ord[i].second;
        int val;
        if (index >= 0)
            val = tree.query(0, index);
        else val = 0;

        if (lis[i] <= val)
            lis[i] = val + 1;


        tree.updateTreeNode(ord[i].first, lis[i]);
    }



    for (int i = 0; i < n; i++)
        if (result < lis[i])
            result = lis[i];

    return result;
}




int main()
{
    int n; scanf("%d", &n);
    vector<int> arr(n);
    vector<pair<int, int>> ordered(n);
    vector<pair<int, int>> ordering(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        ordered[i] = { arr[i],i };
    }

    sort(ordered.begin(), ordered.end());
    int cnt = -1;
    for (int i = 0; i < n; i++) {
        ordering[ordered[i].second].first = i;
        if (i == 0)
            ordering[ordered[i].second].second = -1;
        else {
            if (ordered[i].first == ordered[i - 1].first)
                cnt--;
            else cnt = -1;

            ordering[ordered[i].second].second = cnt;
        }
    }

    printf("%d", lis(arr, ordering, n));
    return 0;
}
