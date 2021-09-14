
#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Author:Max Paris
//Problem Link: https://codeforces.com/problemset/problem/1484/E
//O(n*log(n))
int n, k;
vector<int>heights;
vector<int> beauty;
vector<vector<int>> dp2;
ll ans;
ll value;
int index = 0;
vector<int> lazyUpdate;
vector<ll> SegmentTree1;
vector<ll> SegmentTree2;

int cnt = 1;
int getMiddle(int l, int r) {

    return l + (r - l) / 2;

}

ll getMaxUtil(vector<ll>& segmentTree,int begin, int end, int& l, int& r, int pos)
{
 
    if (l <= begin && r >= end) {
        

        return segmentTree[pos];
    }
    if (end < l || begin > r)return -1e18;

    int mid = getMiddle(begin, end);
    return max(getMaxUtil(segmentTree,begin, mid, l, r, 2 * pos + 1),
        getMaxUtil(segmentTree,mid + 1, end, l, r, 2 * pos + 2));

}
ll update_values_util(vector<ll>& segmentTree,int l, int r, int& index, ll& newValue, int pos) {

    
    if (index >= l && index <= r) {
       


        if (l != r) {
            int mid = getMiddle(l, r);
            ll y1=update_values_util(segmentTree,l, mid, index, newValue, 2 * pos + 1);
            ll y2=update_values_util(segmentTree,mid + 1, r, index, newValue, 2 * pos + 2);

            segmentTree[pos]=max(y1,y2);
            

        }
        else
            segmentTree[pos]= newValue;

       
    }
    return segmentTree[pos];
    
}
void update_value(vector<ll>& segmentTree,int n, int index, ll NewValue) {

 
        update_values_util(segmentTree,0, n - 1, index, NewValue, 0);
    
}

void initSegmentTree() {
   
    int pow = round(log2(n));
    int size = (2 << (pow + 1)) - 1;
    SegmentTree1 = vector<ll>(size, -1e18);
    SegmentTree2 = vector<ll>(size, -1);
    
}
int main()
{
	cin >> n;
    initSegmentTree();
    beauty = vector<int>(n);
    heights= vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> beauty[i];
    }
    vector<pair<ll, int>> dp(n, { -1e18,0 });
    for(int i=0;i<n;i++){
      
        if (i == 0) {
            dp[i] = { beauty[i],heights[i] };
            update_value(SegmentTree2, n, dp[i].second, i);
        }
        else {
            if (heights[i] >= heights[i - 1])
                dp[i] = dp[i - 1];
            else {
                dp[i] = { beauty[i] + (i > 1 ? dp[i - 2].first : 0),heights[i] };
            }

            if (dp[i].first < dp[i - 1].first + beauty[i]) {
                dp[i].first = dp[i - 1].first + beauty[i];
                dp[i].second = heights[i];
            }
            update_value(SegmentTree2, n, heights[i], i);
            int currBeauty = beauty[i];
            int l = 0;
            int currHeight = heights[i] - 1;
            int index = getMaxUtil(SegmentTree2, 0, n - 1, l, currHeight, 0);
            if (index >= 0) {
                if (dp[i].first < dp[index].first) {
                    dp[i] = dp[index];

                }
            }
            else {
                if(dp[i].first< currBeauty)
                    dp[i] = { currBeauty ,currHeight +1};
            }
            l = index + 1;
            int r = i - 1;
                if (l <= r) {
            ll add = getMaxUtil(SegmentTree1, 0, n - 1, l, r, 0);
            if (dp[i].first < add + currBeauty) {
                dp[i].first = add + currBeauty;
                dp[i].second = currHeight;

            }
        }
           
        }
        update_value(SegmentTree1, n, i, dp[i].first);
        
        
    }
    cout << dp[n - 1].first << endl;
	
	return 0;
	
}