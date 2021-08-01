// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
long long rand(long long a, long long b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {

   srand(atoi(argv[1])); // atoi(s) converts an array of chars to int
   //free space to generate test data with the above rand function
}