#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//O(q*log(n)
//Problem Link:https://codeforces.com/problemset/problem/1625/E1
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
    
    curr = vector<char>(n+max(0,cnt)+cnt1);
   
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
          
           sum[j - cnt1].first++;
           if (sum[j - cnt1].second > 1)
               sum[j - cnt1].first += sum[j - cnt1].second * (sum[j - cnt1].second - 1) / 2;
           if (p >= cnt1 && p < n + cnt1) {
               sum[p - cnt1].first += sum[j - cnt1].first;
              
           }
       }
       
    }
    else {
        if (parent[p] >= cnt1 && parent[p] < n + cnt1) {
            sum[parent[p] - cnt1].second++;
           
        }
        
         constructTree(parent[p], j + 1, false, depth - 1);
    }

    
}



int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", &s);
    constructRBS();
    depthInGraph = vector<int>(n,-1);
    visited=vector<bool> (curr.size());
    sum = vector<pair<ll,ll>>(n);
    parent= vector<int>(curr.size());
    for(int i=0;i<curr.size();i++)
    constructTree(-1,i);

    vector<vector<pair<int, ll>>> answers(maxdepth);
    vector<int> cnt(maxdepth);
    for (int i = 0; i < n; i++) {
        if (depthInGraph[i] != -1)
            cnt[depthInGraph[i]]++;
    }
    for (int i = 0; i < maxdepth; i++)
        answers[i] = vector<pair<int,ll>>(cnt[i]), cnt[i]=0;
    for (int i = 0; i < n; i++) {
        if (depthInGraph[i] != -1) {
            answers[depthInGraph[i]][cnt[depthInGraph[i]]].first = i;
            answers[depthInGraph[i]][cnt[depthInGraph[i]]].second = sum[i].first;
            if(cnt[depthInGraph[i]]>0)
            answers[depthInGraph[i]][cnt[depthInGraph[i]]].second += answers[depthInGraph[i]][cnt[depthInGraph[i]] - 1].second;
            
            cnt[depthInGraph[i]]++;
        }
    }
    while (q--) {
        int x1, x2, x3;
        scanf("%d%d%d", &x1, &x2, &x3);
        x2--, x3--;
        int index = depthInGraph[x2];
        int x4, x5;
        x4 = lower_bound(answers[index].begin(), answers[index].end(), make_pair(x2,1ll*0)) - answers[index].begin();
        x5 = lower_bound(answers[index].begin(), answers[index].end(), make_pair(x3, 1ll * 0)) - answers[index].begin()-1;
        ll diff = 1 + x5 - x4;
        ll ans = diff * (diff - 1) / 2 + answers[index][x5].second - ((x4==0)?0:answers[index][x4-1].second);
        printf("%lld\n", ans);

    }

    return 0;
}