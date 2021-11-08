#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, q, k,t;
string s;
vector<int> arr;

//Author: Max Paris
//Problem Link:https://codeforces.com/contest/220/problem/B
//O((n+m)*log(n))

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
    TopDownSegmentTree(int n, T defaultValue, T(*merge)(T, T), T(*add)(T, T, int, int)) {
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

            tree[pos] = add(tree[pos], lazyUpdate[pos], l, r);
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

                tree[pos] = add(tree[pos], diff, l, r);
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
        return update_Range_util(0, n - 1, l1, r1, difference, 0);
    }

    // function to get merge values on interval [l, r]
    T query(int begin, int end, int& l, int& r, int pos)
    {  //continue updating
        if (lazyUpdate[pos] != defaultValue) {

            tree[pos] = add(tree[pos], lazyUpdate[pos], begin, end);
            if (begin != end) {
                lazyUpdate[pos * 2 + 1] = add(lazyUpdate[pos * 2 + 1], lazyUpdate[pos], l, l);
                lazyUpdate[pos * 2 + 2] = add(lazyUpdate[pos * 2 + 2], lazyUpdate[pos], l, l);

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

int merge(int x1, int x2) {
    return max(x1, x2);
}

int add(int x1, int x2, int l, int r) {
    return x1 +x2;
}



int main()
{
	scanf("%d%d", &n,&m);
	
	vector<int> arr(n);
	vector<int> cnt(n);
	vector<vector<int>> Occurences(n);
    TopDownSegmentTree<int> tree(n, 0, merge, add);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] <= n) {
			cnt[arr[i]-1]++;
		}
	}
	for (int i = 0; i < n; i++) {
		if (arr[i] <= n) {
			int index = arr[i] - 1;
			if (Occurences[index].size() == 0) {
				Occurences[index] = vector<int>(cnt[index]);
				Occurences[index][0] = i;
				cnt[index] = 1;
			}
			else Occurences[index][cnt[index]] = i, cnt[index]++;
		}
	}
    for (int i = 0; i < n; i++) {
        if (arr[i] <= n) {
            int index = arr[i] - 1;
           
            if (i == Occurences[index][0]) {
               
                if (Occurences[index].size() >= arr[i]) {
                    cnt[index] = 0;
                    int l = Occurences[index][index];
                    int r= (Occurences[index].size() == arr[i])?n-1: Occurences[index][index+1]-1;
                    tree.update_Range(l, r, 1);
                    
                }
           }
        }
    }
    vector<vector<int>> queries(m,vector<int>(3));

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &queries[i][0], &queries[i][1]);
        queries[i][0]--;
        queries[i][1]--;
        queries[i][2] = i;
    }
    
    sort(queries.begin(), queries.end());
    vector<int> ans(m);
    for (int i = 0,j=0; i < n&&j<m; i++) {
        while (j<m&&queries[j][0] == i) {
            ans[queries[j][2]] = tree.query(queries[j][1], queries[j][1]);
            j++;
        }
        if (j < m) {
            int index = arr[i] - 1;
            if (Occurences[index].size()-(cnt[index]) >= arr[i]) {
                int l = Occurences[index][index+ cnt[index]];
                int r = (Occurences[index].size()- cnt[index] == arr[i]) ? n - 1 : Occurences[index][index + 1+ cnt[index]]-1;
                tree.update_Range(l, r, -1);
                cnt[index]++;
                if (Occurences[index].size() - (cnt[index]) >= arr[i]) {
                    l = Occurences[index][index + cnt[index]];
                    r = (Occurences[index].size() - cnt[index] == arr[i]) ? n - 1 : Occurences[index][index + 1 + cnt[index]]-1;
                    tree.update_Range(l, r, 1);
                }
            }
        }


    }

    for (auto it : ans) {
        printf("%d\n", it);
    }


}
