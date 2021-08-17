
 
 
#include <bits/stdc++.h> 
using namespace std;

vector<  long long> sum1;
vector< long long>sum2;
vector<long long> arr;
long long  value1;
long long value2;

int getMid(int s, int e) { return s + (e - s) / 2; }

void getSumUtil(int ss, int se, int qs, int qe, int si)
{
    
    if (qs <= ss && qe >= se) {
        value1 += sum1[si]*1ll;
        value2 += sum2[si]*1ll;
        return ;
    }
    if (se < qs || ss > qe)return ;

    int mid = getMid(ss, se);
    getSumUtil(ss, mid, qs, qe, 2 * si + 1);
        getSumUtil(mid + 1, se, qs, qe, 2 * si + 2);
    return;
}


void updateValueUtil(int ss, int se, int i, int diff, int si)
{
    
    if (i < ss || i > se)
        return;

  
    sum1[si] = sum1[si] + pow((-1), i) * diff*1ll;
    sum2[si] = sum2[si] + pow((-1), i) * diff * (i + 1*1ll)*1ll;
    if (se != ss)
    {
        int mid = getMid(ss, se);
        updateValueUtil(ss, mid, i, diff, 2 * si + 1);
        updateValueUtil(mid + 1, se, i, diff, 2 * si + 2);
    }
}


void updateValue(int n, int i, int new_val)
{

     
    int diff = new_val - arr[i];

    
    arr[i] = new_val;

  
    updateValueUtil(0, n - 1, i, diff, 0);
}




void constructSTUtil(int ss, int se, int si)
{
    if (ss == se)
    {
        sum1[si] = pow((-1), ss) * arr[ss*1ll];
        sum2[si] = pow((-1), ss) *1ll* arr[ss]*1ll * (ss + 1*1ll)*1ll;

    }
    else {

        int mid = getMid(ss, se);

        constructSTUtil(ss, mid, si * 2 + 1);
        constructSTUtil(mid + 1, se, si * 2 + 2);

        sum1[si] = sum1[si * 2 + 1] + sum1[si * 2 + 2];
        sum2[si] = sum2[si * 2 + 1] + sum2[si * 2 + 2];

    }

}


void constructST(int n)
{
    int x = (int)(ceil(log2(n)));
    int max_size = 2 * (int)pow(2, x) - 1;
    sum1 = vector<long long>(max_size);
    sum2 = vector<long long>(max_size);
  
    constructSTUtil(0, n - 1, 0);

}

int main()
{
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, q;
        cin >> n >> q;
        arr = vector<long long>(n);
       
        for (int i = 0; i < n; i++)cin >> arr[i];



   
        constructST(n);
        long long ans = 0;
       
        while (q--) {
            string type;
            cin >> type;
            if (type == "U") {
                int x, v; cin >> x >> v; x--;
                updateValue(n, x, v);
               
            }
            else {
                int l, r;
                cin >> l >> r; 
                value1 = 0;
                value2 = 0;
                getSumUtil(0, n - 1, l-1, r-1, 0);
                ans += pow((-1), l-1)*1ll * (value2*1ll - (l-1)*value1*1ll);
              
              
            }
        }
        cout << "Case #" << tc << ": " << ans  << endl; sum1.clear(); sum2.clear(); arr.clear();
       
      }
    return 0;
}
