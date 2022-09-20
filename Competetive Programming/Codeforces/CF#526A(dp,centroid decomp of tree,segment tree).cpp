#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
//Author: Max Paris
//Problem Link:https://codeforces.com/contest/1083/problem/A
//O(n*(Log(n)^2))

typedef long long ll;

int  k, l, m,t,d;
ll ans = 0;

struct node {
	vector<pair<node*,int>> con;
	int index=0;
	int subtreeSize=0;
	int fuel=0;
	bool wasCentroid = false;
};
typedef struct node node;

vector<vector<tuple<ll, ll, node*>>> groups;
vector<ll> mxs;
vector< tuple<ll, ll, node*>> sorted;


void dfs(node* curr,node* parent) {
	 curr->subtreeSize = 1;
	 for (auto it : curr->con) {
		 if (it.first != parent&&it.first->wasCentroid==false) {
			 dfs(it.first, curr);
			 curr->subtreeSize += it.first->subtreeSize;
		 }

	 }
}
node* centriodDecomp_internal(node* curr, int half, node* parent = NULL) {
	node* heaviestChild = NULL;
	bool isCentroid = true;

	for (auto it : curr->con) {
		if (it.first != parent&&it.first->wasCentroid==false) {
			if (it.first->subtreeSize > half)
				isCentroid = false;
			if (heaviestChild == NULL || heaviestChild->subtreeSize < it.first->subtreeSize)
				heaviestChild = it.first;
		}
	}

	if (isCentroid) {
		curr->wasCentroid = true;
		return curr;
	}
	else
		centriodDecomp_internal(heaviestChild, half, curr);
}
node* centriodDecomp(node* curr,node* parent=NULL) {
	dfs(curr,parent);
	return centriodDecomp_internal(curr, curr->subtreeSize/2,parent);
}



void computeDist(node* curr, ll& mx, queue<tuple<ll, ll, node*>>& group, node* parent,ll dist=0,ll dist1=0,ll lowpoint=0,ll lowpoint1=0) {
	
	
		for (auto it : curr->con) {
			if (it.first == parent) {
				dist1 = dist1 + curr->fuel - it.second;
				lowpoint1 = min(1ll*0, curr->fuel - it.second + lowpoint1);
				if (lowpoint1 >= 0)
					mx = max(mx, dist1);
			}
		}
	

	dist += curr->fuel;
	
	group.push({ -lowpoint,dist ,curr});
	for (auto it : curr->con) {
		if (it.first != parent && it.first->wasCentroid==false ) {
			
			lowpoint = min(dist - it.second, lowpoint);
			
			computeDist(it.first, mx,group, curr, dist- it.second, dist1, lowpoint, lowpoint1);
		}
		
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
tuple<ll, ll, node*> merge(tuple<ll, ll, node*> x1, tuple<ll, ll, node*> x2) {
	if (get<1>(x1) >= get<1>(x2))
		return x1;
	else
		return x2;
}


void recurr(node* curr,node* parent=NULL) {
	node* centroid = centriodDecomp(curr, parent);
	int m = centroid->con.size() - (centroid == curr && parent != NULL);
	if (m > groups.size()) {
		groups.resize(m);
		mxs.resize(m);
	}
	vector< tuple<ll, ll, node*>> sorted;
	int i = 0;
	int sum = 0;
	for (auto it : centroid->con) {
		if (it.first != parent) {
			ll mx = 0;
			queue<tuple<ll, ll, node*>> group;
			ll dist = -it.second;
			ll lowpoint = dist;
			ll dist1 = centroid->fuel;
			ll lowpoint1 = 0;
			computeDist(it.first, mx, group, centroid, dist, dist1, lowpoint, lowpoint1);
			groups[i].resize(group.size());
			int j = 0;
			sum += group.size();
			while (!group.empty()) {
				groups[i][j++] = group.front();
				group.pop();
			}

			mxs[i] = mx;

			i++;
		}
	}

	
	if (sum > sorted.size())
	    sorted.resize(sum);
	for (i = 0, k=0; i < m; i++) {
		for (int j = 0; j < groups[i].size();j++) {
			sorted[k++] = groups[i][j];
		}
	}
	
	sort(sorted.begin(), sorted.begin()+sum);
	BottomUpSegmentTree<tuple<ll, ll, node*>> tree(sorted, { ll(-1e18),ll(-1e18),NULL}, merge);
	tuple<ll, ll, node*> a = { centroid->fuel,ll(-1e18), (NULL) };
	int index = upper_bound(sorted.begin(), sorted.begin() + sum, a) - sorted.begin();
	if (index > 0) {
		index--;
		ans = max(ans, centroid->fuel + get<1>(tree.query(0, index)));
	}

	
	for (i = 0; i < sum; i++) {
		get<2>(sorted[i])->index = i;
	}
	for (i = 0; i < m; i++) {
		a = { ll(-1e18),ll(-1e18), (NULL) };
		for (int j = 0; j < groups[i].size(); j++) {
			
			tree.updateTreeNode(get<2>(groups[i][j])->index,a);
		}

		ll mx = mxs[i];
		if (mx > 0) {
			ans = max(ans, mx);
			a = { mx,ll(1e18), (NULL) };
			int index = upper_bound(sorted.begin(), sorted.begin() + sum, a) - sorted.begin();
			if (index > 0) {
				index--;
				ans = max(ans, mx + get<1>(tree.query(0, index)));
			}
		}
		if (i + 1 < groups.size()) {
			for (int j = 0; j < groups[i].size(); j++) {

				tree.updateTreeNode(get<2>(groups[i][j])->index, groups[i][j]);
			}
		}
	}
	for (auto it : centroid->con) {
		if (it.first != parent&& it.first->wasCentroid==false) {
			recurr(it.first, centroid);
		}
	}

}




int main() {
	int n;
	scanf("%d", &n);
	
	 
	
	vector<node*> nodes(n);
	for (int i = 0; i < n; i++) {
		nodes[i] = new node();
		scanf("%d", &nodes[i]->fuel);
		ans = max(ans, 1ll* nodes[i]->fuel);
	}

	
	for (int i = 0; i < n - 1; i++) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		u--, v--;
		nodes[u]->con.push_back({ nodes[v],c });
		nodes[v]->con.push_back({ nodes[u],c });
		
	}
	
	recurr(nodes[0]);
	printf("%lld", ans);

}