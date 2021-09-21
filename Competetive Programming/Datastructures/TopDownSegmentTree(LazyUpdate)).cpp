#include <bits/stdc++.h>
using namespace std;
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
     T(*add)(T, T);
     // default Value
     T defaultValue;
    

     //construct segment tree with specific default value and merge function
     TopDownSegmentTree(int n, T defaultValue, T(*merge)(T, T), T(*add)(T, T)) {
         this->n = n;
         this->N = 2 * n-1;
         this->merge = merge;
         this->defaultValue = defaultValue;
         this->add = add;
         tree = vector<T>(N, defaultValue);
         lazyUpdate= vector<T>(N, defaultValue);
     }

     //construct segment tree with specific array
     TopDownSegmentTree(vector<T>& arr,T defaultValue, T(*merge)(T, T), T(*add)(T, T)):
         TopDownSegmentTree(arr.size(), defaultValue, merge, add) {
         build(arr,0,n-1,0);
     }

     int getMiddle(int l, int r) {

         return l + (r - l) / 2;

     }

    // function to build the tree
    void build(vector<T>& arr,int l, int r, int pos)
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
            build(arr,l, mid, pos * 2 + 1);
            build(arr,mid + 1, r, pos * 2 + 2);
            tree[pos] = merge(tree[2*pos+1], tree[2 * pos + 2]);
            lazyUpdate[pos] = defaultValue;
        }
        
    }
    // function to perfom update
    void update_Range_util(int l, int r, int& l1, int& r1, T& diff, int pos) {
        //continue updating
        if (lazyUpdate[pos] != defaultValue) {

            tree[pos] = add(tree[pos],lazyUpdate[pos]);
            if (l != r) {
                lazyUpdate[pos * 2 + 1] = add(lazyUpdate[pos * 2 + 1], lazyUpdate[pos]);
                lazyUpdate[pos * 2 + 2] = add(lazyUpdate[pos * 2 + 2], lazyUpdate[pos]);

            }
            lazyUpdate[pos] = defaultValue;
        }
        //out of range
        if (r < l1 || l > r1)return;
        //in range
        if (l1 <= l && r <= r1) {
            //not at child then add und postpone update
            if (l != r) {

                tree[pos] = add(tree[pos],diff);
                lazyUpdate[pos * 2 + 1] = add(lazyUpdate[pos * 2 + 1],diff);
                lazyUpdate[pos * 2 + 2] = add(lazyUpdate[pos * 2 + 2], diff);

            }
            // At child then add
            else
                tree[pos] = add(tree[pos], diff);

            return;
        }
        // merge childs
        int mid = getMiddle(l, r);
        update_Range_util(l, mid, l1, r1, diff, 2 * pos + 1);
        update_Range_util(mid + 1, r, l1, r1, diff, 2 * pos + 2);
        tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);

    }

    void update_Range(int l1, int r1, T difference) {
      return update_Range_util(0, n - 1, l1, r1, difference, 0);
       }

    // function to get merge values on interval [l, r]
    T query(int begin, int end, int& l, int& r, int pos)
    {  //continue updating
        if (lazyUpdate[pos] != defaultValue) {

            tree[pos] = add(tree[pos], lazyUpdate[pos]);
            if (l != r) {
                lazyUpdate[pos * 2 + 1] = add(lazyUpdate[pos * 2 + 1], lazyUpdate[pos]);
                lazyUpdate[pos * 2 + 2] = add(lazyUpdate[pos * 2 + 2], lazyUpdate[pos]);

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
int merge(int x1,int x2) {
    return min(x1,x2);
}
int add(int x1, int x2) {
    return x1+x2;
}




// driver program to test the above function
int main()
{
    vector<int> a = {234,3212,220,232,676,344,656,2534};
    TopDownSegmentTree<int> tree(a,(int)1e9,merge,add);
   

   

    // print the min in range(1,5) index-based
    cout << tree.query(1, 5) << endl;

    // modify elements at 2nd ans 3rd index
    tree.update_Range(2, 3,300);

    // print the min in range(1,5) index-based
    cout << tree.query(1, 5) << endl;

    return 0;
}
