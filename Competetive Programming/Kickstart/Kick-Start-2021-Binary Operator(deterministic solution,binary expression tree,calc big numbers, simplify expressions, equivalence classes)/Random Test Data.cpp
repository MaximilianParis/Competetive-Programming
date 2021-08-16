// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
long long rand(long long a, long long b) {
    return a + rand() % (b - a + 1);
}

string generateExpression(int cnt) {
    int op = rand(0, 2);
    if (cnt > 1) {
        cnt--;
       
         if (op == 1)
            return "(" + generateExpression(cnt/rand(2,5)) + "+" + generateExpression(cnt / rand(2, 5)) + ")";
        else if (op == 2)
            return "(" + generateExpression(cnt / rand(2, 5)) + "*" + generateExpression(cnt / rand(2, 5)) + ")";
        else {
            return "(" + generateExpression(cnt / rand(2, 5)) + "#" + generateExpression(cnt / rand(2, 5)) + ")";
        }
    }
    else  return to_string(rand(0,2));

 }
int main(int argc, char* argv[]) {

   srand(atoi(argv[1])); // atoi(s) converts an array of chars to int
   ll n;

   n =rand(2,100);
  cout << n << endl;
  for (int i = 0; i < n; i++){
      int cnt = rand(20, 50);
      string a = generateExpression(cnt);
      cout << a << endl;
  }
  

  
       
 
   


    puts("");
}
