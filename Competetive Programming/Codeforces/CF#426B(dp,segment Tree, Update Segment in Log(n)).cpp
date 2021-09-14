
#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Author: Max Paris
//Problem Link: https://codeforces.com/blog/entry/53567
//O(k*n*log(n))
int n, k;
vector<int>arr;
vector<vector<int>> dp2;
ll ans;
ll value;
int index = 0;
vector<int> lazyUpdate;
vector<int> SegmentTree;

int cnt = 1;
int getMiddle(int l, int r) {

    return l + (r - l) / 2;

}

int getMaxUtil(int begin, int end, int& l, int& r, int pos)
{
    if (lazyUpdate[pos] != 0) {

        SegmentTree[pos] += lazyUpdate[pos];
        if (begin != end) {
            lazyUpdate[pos * 2 + 1] += lazyUpdate[pos];
            lazyUpdate[pos * 2 + 2] += lazyUpdate[pos];

        }
        lazyUpdate[pos] = 0;
    }
    if (l <= begin && r >= end) {
        

        return SegmentTree[pos];
    }
    if (end < l || begin > r)return -1;

    int mid = getMiddle(begin, end);
    return max(getMaxUtil(begin, mid, l, r, 2 * pos + 1),
        getMaxUtil(mid + 1, end, l, r, 2 * pos + 2));

}
void update_values_util(int l, int r, int& l1,int& r1, int& diff, int pos) {

    if (lazyUpdate[pos] != 0) {
       
        SegmentTree[pos] += lazyUpdate[pos];
        if (l != r) {
            lazyUpdate[pos * 2 + 1] += lazyUpdate[pos];
            lazyUpdate[pos * 2 + 2] += lazyUpdate[pos];
           
        }
        lazyUpdate[pos] = 0;
    }
    if (r < l1 || l > r1)return;
    if (l1 <= l && r <= r1) {
       


        if (l != r) {
            

            SegmentTree[pos]+= diff;
            lazyUpdate[pos * 2 + 1] += diff;
            lazyUpdate[pos * 2 + 2] += diff;

        }
        else
            SegmentTree[pos]+= diff;

        return;
    }
    int mid = getMiddle(l,r);
    update_values_util( l, mid, l1, r1, diff,2*pos+1);
    update_values_util(mid + 1, r, l1, r1, diff, 2 * pos + 2);
        SegmentTree[pos] = max(SegmentTree[2 * pos + 1], SegmentTree[2 * pos + 2]);
    
}
void update_value(int n, int l1,int r1, int add) {

 
        update_values_util(0, n - 1, l1,r1, add, 0);
    
}
int constructSTUtil(int ss, int se, int pos)
{
    if (ss == se)
    {
       
            SegmentTree[pos] = dp2[cnt-1][index];
            index++;
        
        lazyUpdate[pos] = 0;
       
    }
    else {

        int mid = getMiddle(ss, se);

        int y1 = constructSTUtil(ss, mid, pos * 2 + 1);
        int y2 = constructSTUtil(mid + 1, se, pos * 2 + 2);
        SegmentTree[pos] = max(y1, y2);
        lazyUpdate[pos] = 0;
    }
    return SegmentTree[pos];

}
void initSegementTree() {
   
    int pow = round(log2(n));
    int size = (2 << (pow + 1)) - 1;
    SegmentTree = vector<int>(size, 0);
    lazyUpdate= vector<int>(size, 0);
    
}
int main()
{
	cin >> n>>k;
   
    arr = vector<int>(n);
    vector<int> LastOcurrence(n,-1);
    dp2 = vector<vector<int>>(k,vector<int>(n));
   
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (LastOcurrence[arr[i] - 1]==-1)
            dp2[0][i]++, LastOcurrence[arr[i] - 1]=i;
        if (i > 0)
            dp2[0][i] += dp2[0][i - 1];
        LastOcurrence[arr[i] - 1] = max(i, LastOcurrence[arr[i] - 1]);
    }
   
    if (k == 1)
        cout << dp2[0][n - 1] << endl;
    else {
        initSegementTree();
        k--;
       
        int sum = 0;
        vector<int> Indexing(n, -1);
        while (k--) {
            
            index = 0;
            constructSTUtil(0, n - 1, 0);
            
            for (int i = 0; i < n; i++) {
               
              
               
                if (i >= cnt) {
                    if (Indexing[arr[i] - 1] < i) {

                        update_value(n, max(cnt-1,Indexing[arr[i] - 1]), i-1, 1);

                    }


                    int l = cnt-1;
                    int r = i-1;
                    dp2[cnt][i] = getMaxUtil(0, n - 1, l, r, 0);
                    
                }
                

                
                if (LastOcurrence[arr[i] - 1] == i)
                    Indexing[arr[i] - 1] = -1;
                else
                    Indexing[arr[i] - 1] = i;
                   
                }
                
            
            
            cnt++;
        }
        cout << dp2[cnt-1][n - 1] << endl;
    }

	

	
	
	return 0;
	
}
