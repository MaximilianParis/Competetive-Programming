#include<bits/stdc++.h>
#include<unordered_map>
//Author: Max Paris

//O(n*maxbit) solution
using namespace std;
typedef long long ll;
int n;
vector<ll>nums;
vector<tuple<int, int>> CountZeroAndOnes;
ll ans = 0;

ll InversionsAtBit(vector<ll>& values, int bit, int pos);
void dp(vector<ll>& values) {
    vector<vector<ll>> BitValues1(n);
    vector<vector<ll>> BitValues2(n);
    CountZeroAndOnes = vector<tuple<int, int>>(n);
    vector<vector<ll>>& BitValues = BitValues1;
    vector<vector<ll>>& BitValues3 = BitValues2;

    int maxbit = 62;

    int count = 0;
    for (int bit = maxbit; bit >= 0; bit--) {

        if (bit == maxbit) {


            ll bitValues = InversionsAtBit(values, bit, 0);

            ans += bitValues;
            int value = 1 << bit;
            int size = count;
            for (int j = 0; j <= size; j++) {

                int cntZero = get<0>(CountZeroAndOnes[j]);
                int cntOne = get<1>(CountZeroAndOnes[j]);

                if (cntZero > 0 && cntOne > 0) {
                    BitValues2[count++] = vector<ll>(cntZero);
                    BitValues2[count++] = vector<ll>(cntOne);
                    int i = 0, k = 0;
                    for (auto it : values) {

                        if ((it & value) == value)
                            BitValues2[count - 1][i++] = it;
                        else
                            BitValues2[count - 2][k++] = it;

                    }
                }
                else if (cntOne > 0) {
                    BitValues2[count++] = vector<ll>(cntOne);
                    int i = 0;
                    for (auto it : values) {

                        BitValues2[count - 1][i++] = it;


                    }
                }
                else if (cntZero > 0) {
                    BitValues2[count++] = vector<ll>(cntZero);
                    int i = 0;
                    for (auto it : values) {

                        BitValues2[count - 1][i++] = it;


                    }
                }




            }
            swap(BitValues, BitValues3);

        }
        else {


            int cnt = 0;
            for (int j = 0; j < count; j++) {

                ans += InversionsAtBit(BitValues[j], bit, j);


            }



            if (bit > 0) {
                int value = 1 << bit;
                int size = count;
                for (int j = 0; j < size; j++) {

                    int cntZero = get<0>(CountZeroAndOnes[j]);
                    int cntOne = get<1>(CountZeroAndOnes[j]);
                    if (cntZero > 0 && cntOne > 0) {
                        BitValues2[cnt++] = vector<ll>(cntZero);
                        BitValues2[cnt++] = vector<ll>(cntOne);
                        int i = 0, k = 0;
                        for (auto it : BitValues[j]) {

                            if ((it & value) == value)
                                BitValues2[cnt - 1][i++] = it;
                            else
                                BitValues2[cnt - 2][k++] = it;

                        }
                    }
                    else if (cntOne > 0) {
                        BitValues2[cnt++] = vector<ll>(cntOne);
                        int i = 0;
                        for (auto it : BitValues[j]) {

                            BitValues2[cnt - 1][i++] = it;


                        }
                    }
                    else if (cntZero > 0) {
                        BitValues2[cnt++] = vector<ll>(cntZero);
                        int i = 0;
                        for (auto it : BitValues[j]) {

                            BitValues2[cnt - 1][i++] = it;


                        }
                    }




                }
                swap(BitValues, BitValues3);

            }


            count = cnt;
        }

    }
}



ll InversionsAtBit(vector<ll>& values, int bit, int pos) {

    ll cntZero = 0;
    ll cntOne = 0;
    ll value1 = ll(ll(1) << ll(bit));
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
int main() {

    cin >> n;

    nums = vector<ll>(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];

    }
    dp(nums);

    cout << ans;
}
