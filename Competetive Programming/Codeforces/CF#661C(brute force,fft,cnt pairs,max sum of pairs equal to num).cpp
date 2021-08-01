       #include <bits/stdc++.h>
     
    using namespace std;
   
   
   
   int main(){
       int t;
       cin>>t;
       while(t--){
           
           int n,x,y,minb,mina,cnt;
        int ans=0;
           
           cin>>n;
           
        vector<   int> sum (n+1);
                
        
           for(int i=0;i<n;i++){
     
               cin>>x;
       
               sum[x]++;
              
           }

          for(int s=2;s<n*2+1;s++){
              cnt=0;
              for(int i=1;i<(s+1)/2;i++){
                  if(s-i>n)continue;
                  cnt+=min(sum[i],sum[s-i]);
              }
              if(s%2==0) cnt+=sum[s/2]/2;
              ans=max(cnt,ans);
          }
cout<<ans<<endl;
      
       }
       
       
       
       
   }