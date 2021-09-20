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
     BottomUpSegmentTree(vector<T>& arr,T defaultValue, T(*merge)(T, T)): BottomUpSegmentTree(arr.size(), defaultValue, merge) {
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
            tree[i] = merge(tree[i << 1],tree[i << 1 | 1]);
    }

    // function to update a tree node
    void updateTreeNode(int p, T value)
    {
        // set value at position p
        tree[p + n] = value;
        p = p + n;

        // move upward and update parents
        for (int i = p; i > 1; i >>= 1)
            tree[i >> 1] = merge(tree[i],tree[i ^ 1]);
    }

    // function to get merge value on interval [l, r)
    T query(int l, int r)
    {
        T res = defaultValue;

        // loop to find the merge value in the range
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = merge(res,tree[l++]);

            if (r & 1)
                res = merge(res,tree[--r]);
        }

        return res;
    }
};
int merge(int x1,int x2) {
    return x1 + x2;
}




// driver program to test the above function
int main()
{
    vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8};
    BottomUpSegmentTree<int> tree(a,0,merge);
   

   

    // print the sum in range(0,3) index-based
    cout << tree.query(0, 4) << endl;

    // modify element at 2nd index
    tree.updateTreeNode(2, 1);

    // print the sum in range(0,3) index-based
    cout << tree.query(0, 4) << endl;

    return 0;
}
