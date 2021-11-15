#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long ld;
int n, m, q, k, t;
string s;
vector<int> a, b, answer;
//Author:Max Paris
//Problem Link:http://codeforces.com/contest/1601/problem/C
//O((m+n)*log(m))

vector<ll>nums;
vector<tuple<int, int>> CountZeroAndOnes(2e6);
ll ans = 0;
vector<vector<int>> BitValues1(2e6);
vector<vector<int>> BitValues2(2e6);


ll InversionsAtBit(vector<int>& values, int& bit, int& pos);
void dp(vector<int>& values) {
    int maxbit = 30;
    
    
   

    int count = 0;
    for (int bit = maxbit; bit >= 0; bit--) {

        if (bit == maxbit) {

            int c = 0;
            int bitValues = InversionsAtBit(values, bit, c);

            ans += bitValues;
            int value = 1 << bit;
            int size = count;
            for (int j = 0; j <= size; j++) {

                int cntZero = get<0>(CountZeroAndOnes[j]);
                int cntOne = get<1>(CountZeroAndOnes[j]);

                if (cntZero > 0 && cntOne > 0) {
                    BitValues2[count++].resize(cntZero);
                    BitValues2[count++].resize(cntOne);
                    int i = 0, k = 0;
                    for (auto it : values) {

                        if ((it & value) == value)
                            BitValues2[count - 1][i++] = it;
                        else
                            BitValues2[count - 2][k++] = it;

                    }
                }
                else if (cntOne > 0) {
                    BitValues2[count++].resize(cntOne);
                    int i = 0;
                    for (auto it : values) {

                        BitValues2[count - 1][i++] = it;


                    }
                }
                else if (cntZero > 0) {
                    BitValues2[count++].resize(cntZero);
                    int i = 0;
                    for (auto it : values) {

                        BitValues2[count - 1][i++] = it;


                    }
                }




            }
            swap(BitValues1, BitValues2);

        }
        else {


            int cnt = 0;
            for (int j = 0; j < count; j++) {

                ans += InversionsAtBit(BitValues1[j], bit, j);


            }



            if (bit > 0) {
                int value = 1 << bit;
                int size = count;
                for (int j = 0; j < size; j++) {

                    int cntZero = get<0>(CountZeroAndOnes[j]);
                    int cntOne = get<1>(CountZeroAndOnes[j]);
                    if (cntZero > 0 && cntOne > 0) {
                        BitValues2[cnt++].resize(cntZero);
                        BitValues2[cnt++].resize(cntOne);
                        int i = 0, k = 0;
                        for (auto it : BitValues1[j]) {

                            if ((it & value) == value)
                                BitValues2[cnt - 1][i++] = it;
                            else
                                BitValues2[cnt - 2][k++] = it;

                        }
                    }
                    else if (cntOne > 0) {
                        BitValues2[cnt++].resize(cntOne);
                        int i = 0;
                        for (auto it : BitValues1[j]) {

                            BitValues2[cnt - 1][i++] = it;


                        }
                    }
                    else if (cntZero > 0) {
                        BitValues2[cnt++].resize(cntZero);
                        int i = 0;
                        for (auto it : BitValues1[j]) {

                            BitValues2[cnt - 1][i++] = it;


                        }
                    }




                }
                swap(BitValues1, BitValues2);

            }


            count = cnt;
        }

    }
}



ll InversionsAtBit(vector<int>& values, int& bit, int& pos) {

    int cntZero = 0;
    int cntOne = 0;
    int value1 = int(int(1) << int(bit));
    ll inv1 = 0;
    for (auto it : values) {

        if ((it & value1) == value1)
            cntOne++;
        else
            inv1 += cntOne, cntZero++;


    }
    get<0>(CountZeroAndOnes[pos]) = cntZero;
    get<1>(CountZeroAndOnes[pos]) = cntOne;



    return inv1;
}
void recur(int l1, int r1, int l2, int r2) {

    if (l2 != r2) {
        int cost = 0;
        int mid = l2 + (r2 - l2) / 2;

        for (int i = l1; i < r1; i++) {
            if (a[i] > b[mid])
                cost++;
        }

        int curr_cost = cost;
        int pMid = r1;

        for (int i = r1 - 1; i >= l1; i--) {
            if (a[i] < b[mid])
                curr_cost++;
            else if (a[i] > b[mid])
                curr_cost--;

            if (curr_cost < cost) {
                cost = curr_cost;
                pMid = i;
            }
        }
        int j = mid;
        int rem = j + 1;
        while (j >= 0 && b[mid] == b[j])
            answer[pMid + j] = b[mid], j--;

        int x1 = j + 1;
        j = rem;

        while (j < m && b[mid] == b[j])
            answer[pMid + j] = b[mid], j++;

        int x2 = j;

        recur(l1, pMid, l2, x1);
        recur(pMid, r1, x2, r2);

    }




}


int main()
{

    scanf("%d", &t);
   
    while (t--) {
        scanf("%d%d", &n, &m);

        a = vector<int>(n);
        b = vector<int>(m);
        answer = vector<int>(m + n);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);

        for (int i = 0; i < m; i++)
            scanf("%d", &b[i]);

        sort(b.begin(), b.end());
        recur(0, n, 0, m);


        int i = 0;
        for (auto& it : answer) {
            if (it == 0)
                it = a[i++];
        }

        n += m;
        dp(answer);
        printf("%lld\n", ans);
        ans = 0;
    }

}