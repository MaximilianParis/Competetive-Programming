#include <bits/stdc++.h>
using namespace std;
template<typename T>
struct TopDownSegmentTree {
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
    TopDownSegmentTree(int n, T defaultValue, T(*merge)(T, T)) {
        this->n = n;
        int pow = ceil(log2(n));
        this->N = (2 << (pow)) - 1;
        this->merge = merge;
        this->defaultValue = defaultValue;
        tree = vector<T>(N, defaultValue);

    }

    //construct segment tree with specific array
    TopDownSegmentTree(vector<T>& arr, T defaultValue, T(*merge)(T, T)) :
        TopDownSegmentTree(arr.size(), defaultValue, merge) {
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

        }
        //not at leaf then merge childs
        else {

            int mid = getMiddle(l, r);
            build(arr, l, mid, pos * 2 + 1);
            build(arr, mid + 1, r, pos * 2 + 2);
            tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);

        }

    }
    // function to perfom update
    void update_value_util(int l, int r, int& index, T& newValue, int pos) {


        //in range
        if (index >= l && r >= index) {
            //not at child then merge
            if (l != r) {

                // merge childs
                int mid = getMiddle(l, r);
                update_value_util(l, mid, index, newValue, 2 * pos + 1);
                update_value_util(mid + 1, r, index, newValue, 2 * pos + 2);
                tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);

            }
            // At child then update node
            else
                tree[pos] = newValue;

            return;
        }


    }

    void update_value(int index, T newValue) {
        return update_value_util(0, n - 1, index, newValue, 0);
    }

    // function to get merge values on interval [l, r]
    T query(int begin, int end, int& l, int& r, int pos)
    {
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
int merge(int x1, int x2) {
    return min(x1, x2);
}





// driver program to test the above function
int main()
{
    vector<int> a = { 234,3212,220,232,676,344,656,2534 };
    TopDownSegmentTree<int> tree(a, (int)1e9, merge);




    // print the min in range(1,5) index-based
    cout << tree.query(1, 5) << endl;

    // modify element at 2nd index
    tree.update_value(2, 300);

    // print the min in range(1,5) index-based
    cout << tree.query(1, 5) << endl;

    return 0;
}
