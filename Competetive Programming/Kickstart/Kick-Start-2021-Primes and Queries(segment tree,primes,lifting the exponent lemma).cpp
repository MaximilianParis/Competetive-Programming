#include <bits/stdc++.h>


using namespace std;
typedef long long ll;
//Author: Maximilian Paris
// Problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/00000000004361e3/000000000082bcf4#problem
vector<  long long> sum1;
vector<  long long> sum3;
vector<pair< long long, int>>sum2;
vector<pair<ll, bool>> arr;
long long  value1;
long long value2;
int s, l, r;
ll p;
int cnt;
vector<ll> mods;

ll V(ll val, ll prime) {
    if (log(val) / log(prime)<1)
        return 0;
    int end = round(log(val) / log(prime));
    int begin = 0;
    int y = 0;
    int add = 0;
    while (begin <= end) {
        int middle = begin + ((end - begin) / 2);
        if (val % (ll)pow(prime, middle-add) == 0) {
            val /= (ll)pow(prime, middle-add);
            y = max(y, middle);
            begin = middle + 1;
            add = middle;
        }
        else
            end = middle - 1;
    }
    return y;
}


int getMid(int s, int e) { return s + (e - s) / 2; }

void getSumUtil(int ss, int se, int qs, int qe, int si)
{

    if (qs <= ss && qe >= se) {
        value1 += sum1[si] ;
        value2 += sum2[si].first;
        if (p == 2&& sum2[si].first>0) {
            value2+= (s%2==0)?sum3[si]:0;
        }
        if (sum2[si].first != 0)
            cnt+= sum2[si].second;
        return;
    }
    if (se < qs || ss > qe)return;

    int mid = getMid(ss, se);
    getSumUtil(ss, mid, qs, qe, 2 * si + 1);
    getSumUtil(mid + 1, se, qs, qe, 2 * si + 2);
    return;
}


void updateValueUtil(int ss, int se, int i, ll diff1,ll diff2,ll diff3,int add, int si)
{

    if (i < ss || i > se)
        return;


    sum1[si] = sum1[si] + diff1;
    if (p == 2) {
        sum3[si] = sum3[si] + diff3;
    }
    sum2[si].first = sum2[si].first + diff2;
    sum2[si].second += add;
    if (se != ss)
    {
        int mid = getMid(ss, se);
        updateValueUtil(ss, mid, i, diff1,diff2, diff3,add, 2 * si + 1);
        updateValueUtil(mid + 1, se, i, diff1,diff2, diff3,add, 2 * si + 2);
    }
}


void updateValue(int n, int i, ll new_val)
{

    int val= arr[i].first;
    bool check = arr[i].second;
    int mod = new_val % p;
    if (mod == 0) {
        arr[i] = { V(new_val, p) ,true };


    }
    else {
        arr[i] = { V(new_val - mod, p),false };


    }
    int add = 0;
    ll diff1=0, diff2=0;
    if (check == true && arr[i].second == true) {
        diff1 = arr[i].first - val;
        diff2 = 0;
    }
    else if (check == false && arr[i].second == false) {
        diff1 =0;
        diff2 = arr[i].first - val;
        if (arr[i].first == 0 && val != 0)
            add = -1;

        else if (arr[i].first != 0 && val == 0)
            add = 1;
    }
    else if (check == true && arr[i].second == false) {
        diff1 = -val;
        diff2 = arr[i].first;
        if(arr[i].first>0)
        add = 1;
    }
    else {
        diff1 = arr[i].first;
        diff2 = -val;
        if(val>0)
        add = -1;
    }
    ll diff3 = 0;
    if (p == 2) {
        ll last = mods[i];
        if (new_val % 2 != 0)
            mods[i] = V(new_val + new_val % 2, p) - 1;
        else
            mods[i] = 0;
        diff3 = mods[i] - last;
    }
    updateValueUtil(0, n - 1, i, diff1,diff2,diff3,add, 0);
}




void constructSTUtil(int ss, int se, int si)
{
    if (ss == se)
    {
       
        sum1[si] =  (arr[ss].second)? arr[ss].first:0;
        if (p == 2) {
            sum3[si] = mods[ss];
        }
        sum2[si].first = (!arr[ss].second) ? arr[ss].first : 0;
        sum2[si].second = (!arr[ss].second&& arr[ss].first>0) ? 1 : 0;
    }
    else {

        int mid = getMid(ss, se);

        constructSTUtil(ss, mid, si * 2 + 1);
        constructSTUtil(mid + 1, se, si * 2 + 2);

        sum1[si] = sum1[si * 2 + 1] + sum1[si * 2 + 2];
        sum2[si].first = sum2[si * 2 + 1].first + sum2[si * 2 + 2].first;
        sum2[si].second = sum2[si * 2 + 1].second + sum2[si * 2 + 2].second;
        if (p == 2) {
            sum3[si] = sum3[si * 2 + 1] + sum3[si * 2 + 2];
        }
    }

}


void constructST(int n)
{
    int x = (int)(ceil(log2(n)));
    int max_size = 2 * (int)pow(2, x) - 1;
    sum1 = vector<long long>(max_size);
    sum2 = vector<pair< long long, int>>(max_size);
    if (p == 2) {
        sum3 = vector<long long>(max_size);
    }
    constructSTUtil(0, n - 1, 0);

}





int main() {
   int t;
  cin >> t;
   for (int tc = 1; tc <= t; tc++) {
        int n, q;
        
        cin >> n >> q >> p;
        vector<ll> input(n);
      
        arr= vector<pair<ll,bool>>(n);
       
        for (int i = 0; i < n; i++)
            cin >> input[i];
       
        if (p == 2) {
            mods = vector<ll>(n);
            for (int j = 0; j <= n - 1; j++) {

              if(input[j]%2!=0)
                mods[j] = V(input[j] + input[j]%2, p)-1;


              
            }
        }
            for (int j = 0; j <= n - 1; j++) {

                int mod = input[j] % p;
                if (mod == 0) {
                    arr[j] = { V(input[j], p) ,true };


                }
                else {
                    arr[j] = { V(input[j] - mod, p) ,false };


                }
            }
        
        
     constructST(n);
        vector<ll> ans(q);
        int cnt_type2 = 0;
        for (int i = 0; i < q; i++) {
            int type;
            cin >> type;
            if (type == 1) {
               
                int pos;
                ll val;
                cin >> pos >> val;
                pos--;
            
                updateValue(n, pos, val);
                input[pos] = val;
            }
            else {
                cnt = 0;
                cin >> s >> l >> r;
               
                ll sum = 0;
               
                   
                value1 = 0;
                value2 = 0;
                getSumUtil(0, n - 1, l - 1, r-1, 0);
                               
                             
                ans[cnt_type2] = (value1)*s+value2+ ((s % p == 0) ? V(s, p) : 0)*cnt;
            
                cnt_type2++;
                
            }
           
        }
        cout << "Case #" << tc << ": ";
        for (int j = 0; j < cnt_type2; j++)
            cout << ans[j] << " ";
        cout << endl;
  }
   
   
    return 0;
}