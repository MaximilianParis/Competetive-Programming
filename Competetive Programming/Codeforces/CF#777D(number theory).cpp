#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris
//O(sqrt(d))
//Problem Link: https://codeforces.com/contest/1647/problem/D
typedef long long ll;
int n, d, t, x;
bool isPrime(int a) {
    int size = sqrt(a);
    for (int i = 2; i <= size; i++) {
        if (a % i == 0)
            return false;
    }

    return true;
}


int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &x, &d);
        ll dPotenz = 1;
        int cnt = 0;
        int count = 0;
        int index = 0;
        for (ll potenz = d, i = 1,k=0; potenz <= x; potenz *= potenz, i *= 2, count++,k++) {
            if (x % potenz == 0) {
                dPotenz = potenz;
                cnt = i;
                index = k;
            }
        }
        vector<int> rem(count);
        count = 0;
        for (ll potenz = d; potenz <= x; potenz *= potenz, count++)
            rem[count] = potenz;
        int temp = x / dPotenz;
        count= index -1;
        if (count >= 0) {
            for (ll potenz = rem[count], i = cnt / 2;; i /= 2, potenz = rem[count]) {
                if (temp % potenz == 0) {
                    temp /= potenz;
                    dPotenz *= potenz;
                    cnt += i;
                }
                if (count == 0)
                    break;
                else count--;
            }
        }
        if (cnt == 1)
            printf("\n NO");
        else if(cnt==2){
            int div = x / dPotenz;
            if(isPrime(div)||div==1)
                printf("\n NO");
            else 
                printf("\n YES");
        }
        else if(cnt==3){
            int div = x / dPotenz;
            if(!(isPrime(div) || div == 1))
                printf("\n YES");
            else if(isPrime(d))
                printf("\n NO");
            else {
                if(div==1)
                    printf("\n YES");
                else {
                    bool ans = false;
                    int size = sqrt(d);
                    for (int i = 2; i <= size; i++) {
                        if (d % i == 0) {
                            if ((i * div) % d != 0|| ((d/i) * div) % d != 0) {
                                ans = true;
                                break;
                            }
                        }
                           
                    }

                    if(ans)
                        printf("\n YES");
                    else 
                        printf("\n NO");
                }
            }
                
        }
        else {
            int div = x / dPotenz;
            if ((isPrime(div)||div==1) && isPrime(d))
                printf("\n NO");
            else
                printf("\n YES");
        }
    }
}