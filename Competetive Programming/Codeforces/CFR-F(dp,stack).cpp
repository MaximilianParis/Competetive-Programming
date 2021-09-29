

#include <bits/stdc++.h>
using namespace std;
//Author: Max Paris
//Problem Link: http://codeforces.com/problemset/problem/1428/F
//O(n)
typedef long long ll;
int n;
char s[int(5e5+1)];
vector<pair<int, int>> segments;


int main() {
    
    scanf("%d", &n);
    scanf("%s", &s);
  
    
   
    int cnt = 0;
    int l = -1;
    int r = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1'&&l==-1) {
            l = i;
            cnt++;
        }
        else if (s[i] == '0' && l != -1) {
            r = i - 1;
            l = -1;
            r = -1;
        }
        
    }
    segments = vector<pair<int, int>>(cnt);
    cnt = 0;
    l = -1;
    r = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1' && l == -1) {
            l = i;
           if(i==n-1)
               segments[cnt] = { l,l };
        }
        else if (s[i] == '0' && l != -1) {
            r = i - 1;
            segments[cnt] = { l,r };
            cnt++;
            l = -1;
            r = -1;
        }
        else if (s[i] == '1' && i == n - 1) {
            r = i;
            segments[cnt] = { l,r };
        }
    }
   
    ll ans = 0;
    
     l = 0;
    cnt = 0;
    ll sum = 0;
    ll curr = 0;
    int l1 = 0;
   
    stack<pair<int, int>> prevSegments;
    for (int i = 0; i < segments.size();i++) {

        if (i > 0) {
            curr = 0;

            for (int j = segments[i].first; j <= segments[i].second; j++) {

                curr++;

                r = prevSegments.top().second;
                while (!prevSegments.empty() && (prevSegments.top().first <= curr)) {

                    ll val = prevSegments.top().first;
                    prevSegments.pop();
                    if (!prevSegments.empty())
                        l = prevSegments.top().second;
                    else l = -1;
                    sum -=  (r - l) * val;
                   
                    if (!prevSegments.empty() && (prevSegments.top().first <= curr))
                        r = l;



                }

                prevSegments.push({ curr,segments[i - 1].second }), sum += 1ll * (segments[i - 1].second - l) * curr ;
               




                ans += sum;
               

            }
        }
        
        l = l1;
            curr = segments[i].second - segments[i].first + 1;
            ll sum1 = 0;
            for (int j = segments[i].first; j <= segments[i].second; j++) {
                if(prevSegments.empty()|| prevSegments.top().first>curr)
                prevSegments.push({ curr,j });
                else if (prevSegments.top().first == curr) {
                    prevSegments.pop();
                    prevSegments.push({ curr,j });
                }

                sum1 += 1ll*j - l + 1;
               
                ans += sum1;
               
                
                    curr--;
            }
            sum += sum1;
          
        l1 = segments[i].second + 1;
        int r1 = 0;
        if (i == segments.size() - 1)
            r1 = n;
        else r1 = segments[i+1].first;
        ans +=(r1 - l1) * sum ;
       
        l = l1;
        
    }


    printf("%lld", ans);

    return 0;
}
