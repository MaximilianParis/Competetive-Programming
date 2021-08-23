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


int main(int argc, char* argv[]) {

   srand(atoi(argv[1])); // atoi(s) converts an array of chars to int

   int n = rand(1, 4);
   cout << n << endl;
   vector<vector<int>> arr(n, vector<int>(n));
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) {
           arr[i][j] = rand(-1, 1);
           cout << arr[i][j] <<" ";
       }
       cout << endl;
   }
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) {
           if (arr[i][j] == -1)
               cout << rand(1, 1000) << " ";
           else
               cout << "0 ";
       }
       cout << endl;
   }
   
   for (int j = 0; j < n; j++) {
       cout << rand(1, 1000) << " ";
   }
   cout << endl;
   for (int j = 0; j < n; j++) {
       cout << rand(1, 1000) << " ";
   }
   cout << endl;


    puts("");
}
