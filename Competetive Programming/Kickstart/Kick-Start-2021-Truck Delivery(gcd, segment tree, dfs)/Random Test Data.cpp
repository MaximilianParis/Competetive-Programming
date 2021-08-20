// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, q,cnt,newIndex;
vector<string> out;
set<int> loadlimits;
long long rand(long long a, long long b) {
    return a + rand() % (b - a + 1);
}

void generateTree(int parent,bool kid) {
    if (kid) {
        int l = rand(1, 1e5);
        while(loadlimits.count(l)!=0)
            l = rand(1, 1e5);
        loadlimits.insert(l);
        ll a = rand(1, 1e18);
        out.push_back(to_string(++newIndex)+ " " + to_string(parent) + " " + to_string(l) + " " + to_string(a) );
    }

    if (cnt < n) {
       
        int kids = rand((kid)?0:1,min(4, n-cnt));
        cnt += kids;
        int index = newIndex;
       while(kids--)
        generateTree(index, true);
   }

 }
int main(int argc, char* argv[]) {

   srand(atoi(argv[1])); // atoi(s) converts an array of chars to int
 
   int t = 20;
   cout << t << endl;
   while (t--) {
       cnt = 1;
       newIndex = 1;
       n = 1000;
       q = 1000;
       out.clear();
loadlimits.clear();

       generateTree(-1, false);
       cout << newIndex << " " << q << endl;
       for (auto it : out)
           cout << it << endl;
       for (int i = 0; i < q; i++) {
           int w = rand(1, 1e5);
           int c = rand(1, newIndex);
           cout << c << " " << w << endl;
       }

   }
  
       
 
   


    puts("");
}
