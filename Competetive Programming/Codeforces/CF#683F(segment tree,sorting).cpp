#include <bits/stdc++.h>
//Author: Max Paris
//O(t*n*log(n))
//Problem Link:https://codeforces.com/contest/1454/problem/F
using namespace std;
typedef long long ll;
int n, q,t;

vector<pair<int, int>> arr;


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
    return max(x1,x2);
}
int merge1(int x1, int x2) {
    return min(x1, x2);
}


int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		arr=vector<pair<int,int>>(n);
        vector<int> nums(n);
        vector<int> Indices(n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i].first), arr[i].second = i;
            nums[i] = arr[i].first;
            Indices[i] = i;
		}
        BottomUpSegmentTree <int> treeMaxIndex(Indices,-1,merge);
        BottomUpSegmentTree <int> treeMinIndex(Indices,n, merge1);
        BottomUpSegmentTree <int> treeMin(nums,2e9, merge1);
        BottomUpSegmentTree <int> treeMax(nums, 0, merge);
		sort(arr.begin(), arr.end());
	
		vector<int> ans;
	
		int i = 0,j=0;
		while (i < n) {
            while (j < n && arr[i].first == arr[j].first) {
                
                treeMaxIndex.updateTreeNode(arr[j].second, -1);
                treeMinIndex.updateTreeNode(arr[j].second, n);
                j++;
            }
            
			if (j - i >= 3) {
                int val = arr[i].first;
                int minIndex;
                for (int k = i + 1; k < j; k++) {
                    if (arr[i].second + 1 <= arr[k].second - 1)
                        minIndex = treeMinIndex.query(arr[i].second + 1, arr[k].second - 1);
                    else minIndex = arr[i].second;

                    if (minIndex == n)
                        minIndex = arr[k].second - 1;
                    else if (val < nums[minIndex])
                        minIndex--;

                    
                    int MaxIndex;
                    if (arr[k].second + 1 <= arr[j - 1].second - 1)
                        MaxIndex = treeMaxIndex.query(arr[k].second + 1, arr[j - 1].second - 1);
                    else MaxIndex = arr[j - 1].second;

                    if (MaxIndex == -1)
                        MaxIndex = arr[k].second + 1;
                    else if (val < nums[MaxIndex])
                        MaxIndex++;

                    if (val == treeMax.query(0, minIndex) && val == treeMax.query(MaxIndex, n - 1) && val == treeMin.query(minIndex + 1, MaxIndex - 1)) {
                        ans = { minIndex + 1,MaxIndex - minIndex - 1,n - MaxIndex };
                        i = n + 1;
                        break;
                    }
                }
               
			}

            if (i < j) {
                i = j;
               
            }
			
		}

		if (i == n + 1) {
          
			printf("YES %d %d %d\n", ans[0], ans[1], ans[2]);
		}
		else
            printf("NO \n");
	}
	

}