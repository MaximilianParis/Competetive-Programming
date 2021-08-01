#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

const string check= "abacaba";




int count(int n,const string& s) {
    int cnt = 0;
    for (int i = 0; i <= (int)s.size(); ++i) {
        if (s.substr(i, check.size()) == check) {
            ++cnt;
        }
    }
 
    return cnt;
}
     
     
   
     
    string setString(string s,int n){
        for(int i=0;i<n;i++){
            if(s[i]=='?'){s[i]='z';}
        }
        return s;
    }
     
    int main() {
     
    	int t;
    	cin >> t;
    	while (t--) {
         
    		int n;
    		 string s;
    		cin >> n >> s;
            bool m=false;
      int b= count(n,s);
      if(b>1)cout<<"No"<<endl;
      else if(b==0){
          string w=s;
          int cnt=0;
          int st=0;
         
    for(int i=0;i<=n;i++){
        if(cnt<7){
        if(w[i]==check[cnt])cnt++;
        else if(w[i]=='?'){w[i]=check[cnt];cnt++;}
        else {st++; cnt=0;w=s;i=st;}
        }else if(1==count(n,w)){m=true; w=setString(w,n); cout<<"YES"<<endl<<w<<endl;break;}
        else {st++; cnt=0;w=s;i=st;}
        }
        if(m==false)cout<<"No"<<endl;
    }else {s=setString(s,n); cout<<"YES"<<endl<<s<<endl;}      
          
          
          
          
        
    		
    	}
    	
     
    }
     
     

