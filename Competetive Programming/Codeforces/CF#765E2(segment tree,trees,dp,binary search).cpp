#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//O(q*log(n)
//Problem Link:https://codeforces.com/contest/1625/problem/E2
typedef long long ll;
int n, q;
vector<char> curr;
char s[(int)3e5 + 1];
int cnt = 0;
int cnt1 = 0;
vector<int> depthInGraph;
vector<bool> visited;
vector<pair<ll,ll>> sum;
vector<int> parent;
int maxdepth = 0;;
void constructRBS() {
    
    for (int i = 0; i < n; i++) {
        if (s[i] == '(')
            cnt++;
        else {
            cnt--;
            if (cnt < -cnt1)
                cnt1++;
        }
       
    }
    
        cnt=cnt1+cnt;
    curr = vector<char>(n+cnt+cnt1);
   
    for (int i = 0; i < (cnt1); i++)
        curr[i] = '(';
    for (int i = cnt1; i < n+cnt1; i++)
        curr[i] = s[i-cnt1];
    for (int i = n + cnt1; i < curr.size(); i++)
        curr[i]= ')';

}

void constructTree(int p,int j,bool start=true,int depth=0) {
    if (depth == 0 && !start||visited[j])
        return;
    visited[j] = true;
    maxdepth = max(maxdepth, depth);
    parent[j] = p;
    if (curr[j] == '(') {
      
       
          constructTree(j,j + 1, false, depth + 1);
       
      
       if (j >= cnt1 && j < n + cnt1) {
           depthInGraph[j - cnt1] = depth;
           cnt++;
           sum[j - cnt1].first=1;
          
       }
       
    }
    else {
        if (parent[p] >= cnt1 && parent[p] < n + cnt1) {
            sum[parent[p] - cnt1].second++;
           
        }
        
         constructTree(parent[p], j + 1, false, depth - 1);
    }

    
}
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
ll merge(ll x1, ll x2) {
    return x1 + x2;
}




int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", &s);
    constructRBS();
    depthInGraph = vector<int>(n,-1);
    visited=vector<bool> (curr.size());
    sum = vector<pair<ll,ll>>(n);
    parent= vector<int>(curr.size(),-1);
    cnt = 0;
    for(int i=0;i<curr.size();i++)
    constructTree(-1,i);
    
    vector<int> count(cnt);
    vector<ll> arr(cnt);
    vector<int>pos(cnt);
    vector<int> countdepth(maxdepth);
    vector<vector<int>> elementsAtdepth(maxdepth);
    vector<BottomUpSegmentTree<ll>> trees(maxdepth, BottomUpSegmentTree<ll>(0,0,merge));
    for (int i = cnt1, j = 0; i < n + cnt1; i++) {
        if (curr[i] == '(') {
            int index = i - cnt1;
            countdepth[depthInGraph[index]]++;
            count[j] = sum[index].second;
            pos[j] = index;
            arr[j] = 1 + 1ll * count[j] * (count[j] - 1) / 2;
            j++;

        }
    }
        for (int i = cnt1, j = 0; i < n + cnt1; i++) {
            if (curr[i] == '(') {
                int index = i - cnt1;
                if (elementsAtdepth[depthInGraph[index]].size() == 0) {
                    elementsAtdepth[depthInGraph[index]] = vector<int>(countdepth[depthInGraph[index]]);
                    vector<ll>def(countdepth[depthInGraph[index]], 1);
                    trees[depthInGraph[index]] = BottomUpSegmentTree<ll>(def, 0, merge);
                    countdepth[depthInGraph[index]] = 0;
                }
                elementsAtdepth[depthInGraph[index]][countdepth[depthInGraph[index]]++] = index;
        }

    }
    BottomUpSegmentTree<ll> tree(arr,0, merge);
    while (q--) {
        int x1, x2, x3;
        scanf("%d%d%d", &x1, &x2, &x3);
        x2--, x3--;
        if (x1 == 2) {
            int x4 = lower_bound(pos.begin(), pos.end(),x2) - pos.begin();
            int x5 = lower_bound(pos.begin(), pos.end(), x3) - pos.begin()-1;
            int x6 = lower_bound(elementsAtdepth[depthInGraph[x2]].begin(), elementsAtdepth[depthInGraph[x2]].end(), x2)
                - elementsAtdepth[depthInGraph[x2]].begin();
            int x7= lower_bound(elementsAtdepth[depthInGraph[x2]].begin(), elementsAtdepth[depthInGraph[x2]].end(), x3)
                - elementsAtdepth[depthInGraph[x2]].begin()-1;

            ll diff = trees[depthInGraph[x2]].query(x6,x7);
            printf("%lld\n", tree.query(x4,x5)+diff*(diff-1)/2);
        }
        else {
            int x4 = lower_bound(pos.begin(), pos.end(), x2) - pos.begin();
            tree.updateTreeNode(x4, 0);
            int x5 = lower_bound(elementsAtdepth[depthInGraph[x2]].begin(), elementsAtdepth[depthInGraph[x2]].end(), x2)
                - elementsAtdepth[depthInGraph[x2]].begin();
           
            trees[depthInGraph[x2]].updateTreeNode(x5, 0);
            if (parent[x2 + cnt1]-cnt1 > -1) {
                int index = parent[x2 + cnt1] - cnt1;
                int x6 = lower_bound(pos.begin(), pos.end(), index) - pos.begin();
                sum[index].second--;
                ll val = 1ll * sum[index].second * (sum[index].second - 1) / 2;
                tree.updateTreeNode(x6, val+1);
            }
        }
    }

    return 0;
}