#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, q,t;
//Problem Link:https://codeforces.com/problemset/problem/1721/D
//O(n*log(n)*log(max(a[i],b[i])))
void recurr(int mask, int bit, vector<int>& a, vector<int>& b) {
    if (bit == 0) {
        printf("%d\n", mask);
        return;
    }
    mask += bit;

    map<int, int> values;
    int rest = n;
    for (int i = 0; i < n; i++) {
        int val = a[i] & mask;
        values[val ^ mask]++;
    }
    
    for (int i = 0; i < n; i++) 
        if (values[b[i] & mask]-- > 0) 
            rest--;
          
    if (rest != 0) 
        mask -= bit;

    recurr(mask, bit / 2, a, b);
        
        
    
}

int main(){
    scanf("%d", &t);
    vector<int> a(1e5);
    vector<int> b(1e5);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);

        for (int i = 0; i < n; i++)
            scanf("%d", &b[i]);

        recurr(0,1<<30, a, b);
      
       
      

        
    }
    
}