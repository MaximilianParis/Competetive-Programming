#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, q,t,k;
//Problem Link:https://codeforces.com/contest/747/problem/D
//O(n*log(n))
int main(){
    scanf("%d%d", &n, &k);

    vector<int> temperatures(n);
    int cntGaps = 0;
    int cntColdDays=0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &temperatures[i]);
        if (temperatures[i] < 0)
            cntColdDays++;
      
    }
    if (k >= cntColdDays) {
        for (int i = 0; i < n - 1; i++) {
            if (temperatures[i] < 0 && temperatures[i + 1] >= 0)
                cntGaps++, i++;
        }
        if (cntGaps > 0) {
            vector<int> gaps(cntGaps);
            cntGaps = 0;
            bool bad = false;
            for (int i = 0; i < n - 1; i++) {
                if (temperatures[i] < 0 && temperatures[i + 1] >= 0) {
                    int cnt = 0;

                    while (i + 1 < n && temperatures[i + 1] >= 0)
                        cnt++, i++;
                    if (i + 1 == n)
                        bad = true;
                    gaps[cntGaps] = cnt;
                    cntGaps++;
                }
            }

            sort(gaps.begin(), gaps.end()- bad);
            int rest = k - cntColdDays;
            for (int i = 0; i < cntGaps; i++) {
                if (rest < gaps[i]) {
                    if (bad == true) {
                        if (rest < gaps[cntGaps - 1])
                            printf("%d\n", (cntGaps - i - 1) * 2 + 2);
                        else
                            printf("%d\n", (cntGaps - i - 1) * 2 + 1);
                    }
                    else {
                        printf("%d\n", (cntGaps - i) * 2 + 1);
                    }
                    break;
                }
                else if (i == cntGaps - 1 && rest >= gaps[i])
                    printf("1\n");

                rest -= gaps[i];
            }
        }else if(cntColdDays==0)
               printf("0\n");
        else 
            printf("1\n");
    }
    else {
        printf("-1\n");
    }
       
    
}