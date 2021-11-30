#include <bits/stdc++.h>

using namespace std;
//Author:Max Paris
//O(n*log(n))
//Problem Link: https://codeforces.com/problemset/problem/1601/B
int n;
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

pair<int, int> merge(pair<int, int> x1, pair<int, int> x2) {
    return min(x1,x2);
}
int main() {
   
	scanf("%d", &n);

    
	vector<pair<int, int>> points(n);
   
    BottomUpSegmentTree <pair<int, int>> tree(n+1, { 1e9 ,1e9}, merge);
   
    for (int i = 0; i < n; i++) 
        scanf("%d", &points[i].first);
        
    for (int i = 0; i < n; i++)
        scanf("%d", &points[i].second);

    if (n == 1) {
        if(points[0].first>=0)
        printf("%d\n%d", 1, 0);
        else  printf("-1");
        return 0;
    }

  
    tree.updateTreeNode(max(n- points[n-1].first,0), { 0,n });
    vector<int> jumps(n);
    int ans = 1e9;
    int ans1;
    for (int i = n-2; i>=0; i--) {
        pair<int, int> mn = tree.query(0, i + 1);
        if (mn.first != 1e9) {
            int index = i +points[i].second;
            int reach=index+1- points[index].first;
            if (tree.tree[max(0, reach) + n+1].first > mn.first + 1) {
                tree.updateTreeNode(max(0, reach), { mn.first + 1,i + 1 });
                jumps[i] = mn.second - 1;
                if(max(0, reach)==0)
                ans = min(ans, mn.first + 2),ans1= i;

            }
            
        }
    }
    
    printf("%d", (ans==1e9?-1:ans));
    if (ans != 1e9) {
        printf("\n");
        int k = ans1;
        vector<int> answer(ans);
        int cnt = 2;
        answer[ans-1] = 0;
       
            answer[ans - 2] = ans1+1;
            while (cnt < ans) {

                k = jumps[k];
                answer[ans - cnt - 1] = k + 1;
                cnt++;
            }
        
        for (int i = 0; i <ans; i++)
            printf("%d ", answer[i]);
    }
    
}