#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
using namespace std;
//Author:Max Paris
//Problem Link: https://codeforces.com/problemset/problem/981/E
//O(q*n+q*log(q))
int n, m, q;
vector<tuple<int, int, int>> arr;
vector<tuple<int, int, int>> values;


int main()
{
    cin >> n >> q;
    
    arr = vector<tuple<int, int, int>>(q);
    values = vector<tuple<int,int,int>>(n, { -1,-1,-1 });
  
    for (int i = 0; i < q; i++) 
        cin >> get<0>(arr[i]) >> get<1>(arr[i]) >> get<2>(arr[i]);
   
    

    sort(arr.begin(), arr.end());
    int ans = 0;
   
    for (int i = 0; i < q; i++) {
        if (i > 0) {
           
            for (int k = n-2; k>=0; k--) {
                if (get<0>(values[k])!=-1 &&get<1>(arr[i]) >= get<0>(values[k]) && get<1>(arr[i]) <= get<1>(values[k])&&i!= get<2>(values[k])) {
                    int val = get<2>(arr[i]) + k;
                    if (val < n) {
                        if (get<0>(values[val]) == -1) {
                            int x1, x2;
                            x1 = max(get<0>(values[k]), get<0>(arr[i]));
                            x2 = min(get<1>(arr[i]), get<1>(values[k]));
                           
                                ans++;
                           
                            values[val] = { x1,x2,i };
                          
                        }
                        else {
                            int x1, x2;
                            x1 = max(get<0>(values[k]), get<0>(arr[i]));
                            x2 = min(get<1>(arr[i]), get<1>(values[k]));
                            if(x2> get<1>(values[val]))
                                values[val] = { x1,x2,i };
                        }
                    }
                }
                else if (get<0>(values[k]) != -1  && get<0>(arr[i]) <= get<1>(values[k]) && get<1>(arr[i]) >= get<1>(values[k]) && i != get<2>(values[k])) {
                    int val = get<2>(arr[i])+ k;
                    if (val < n) {
                        
                        if (get<0>(values[val]) == -1) {
                            int x1, x2;
                            x1 = max(get<0>(values[k]), get<0>(arr[i]));
                            x2 = min(get<1>(arr[i]), get<1>(values[k]));
                          
                                ans++;
                           
                            values[val] = { x1,x2,i };

                        }
                        else {
                            int x1, x2;
                            x1 = max(get<0>(values[k]), get<0>(arr[i]));
                            x2 = min(get<1>(arr[i]), get<1>(values[k]));
                            if (x2 > get<1>(values[val]))
                                values[val] = { x1,x2,i };
                        }
                        
                    }
                }
            }

        }

       

       
        int val = get<2>(arr[i])-1;
        if (get<1>(values[val]) == -1)
            ans++;

        if (get<1>(arr[i]) > get<1>(values[val]))
            values[val] = { get<0>(arr[i]) ,get<1>(arr[i]),i };
          
            
          
           
          
        
       
    }
    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        if (get<1>(values[i])!=-1)
            cout << i + 1 << " ";
    }

    
    return 0;

}