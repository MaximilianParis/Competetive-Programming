#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


int main()
{
   long long n, a, m, tc, x, cnt, y, u, b,teamsize,sum,prefix,ans;
 
    cin >> tc;
    while (tc--)
    {
        cnt=0;
        cin>>n>>m;
        vector <pair<int,int>> s;
        vector <int> v;
   long long  pre[m];
        for(int i=0;i<m;i++){
            cin>>a>>b;
           s.push_back({a,b});
     v.push_back(a);
           
        }
     
      sort(v.begin(),v.end());
      for(int i=m-1;i>=0;i--){
          if(i==m-1)pre[i]=v[i];
          else
          pre[i]=v[i]+pre[i+1];
      }
        x=n;
        prefix=0;
        u=0;
        if(n<=m){
         for(int i=m-1;;i--){
            u+=v[i];
          
            x--;
            if(x==0)break;
        }}
         x=n;
        ans=0;
        
                for (long long i = 0; i < m; i++)
        {
            x=n;
            sum = 0;
            int sc=s[i].second;
            long long pos= upper_bound(v.begin(),v.end(),sc)-v.begin();
       //    for(int r=0;r<m;r++){
       //        if(v[r]>=sc)pos=r+1;
       //        else break;
       //    }
         
       int c=m-pos;
            
           if(pos!=m)
            sum = pre[pos];
               
 
            if (s[i].first <= s[i].second)	{
                sum += s[i].first;
                c++;
            }
          if( c>= n)
            	ans = max(ans , pre[m - n]);
           else
            	ans = max(ans, sum + (n-c) * s[i].second);
        }
        
        
        
       
            
            cout<<max(u,ans)<<endl;
            
        }
        
        
        
        
    }


    
        
         
     
     



