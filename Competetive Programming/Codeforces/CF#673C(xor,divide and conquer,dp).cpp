#include<bits/stdc++.h>
#include<unordered_map>
//Author: Max Paris
//Problem Link: https://codeforces.com/problemset/problem/1416/C
//O(n) solution
using namespace std;
typedef long long ll;
int n, m, d;
vector<int>nums;

ll ans=0;
int x=0;
pair<ll, ll> InversionsAtBit(vector<int>& values, int bit, int value);
void dp(vector<int>& values) {
    vector<vector<int>> BitValues1(n);
    vector<vector<int>> BitValues2(n);
    vector<vector<int>>& BitValues= BitValues1;
    vector<vector<int>>& BitValues3 = BitValues2;
    
    int maxbit = 29;
    int count = 0;
    for (int bit = maxbit; bit >= 0; bit--) {
       
        if (bit == maxbit) {
            
            
            pair<ll, ll> bitValues=InversionsAtBit(values, bit, 0);
            if (bitValues.first <= bitValues.second) {
                ans += bitValues.first;
                int value = 1 << bit;
                int size = count;
                for (int j = 0; j <= size; j++) {

                    int cntZero = 0;
                    int cntOne = 0;
                    for (auto it : values) {
                        it ^= x;
                        if ((it & value) == value)
                            cntOne++, it ^= x;
                        else
                            cntZero++, it ^= x;

                    }
                    if (cntZero > 0 && cntOne > 0) {
                        BitValues2[count++] = vector<int>(cntZero);
                        BitValues2[count++] = vector<int>(cntOne);
                        int i = 0, k = 0;
                        for (auto it : values) {
                            it ^= x;
                            if ((it & value) == value)
                                BitValues2[count - 1][i++] = it ^= x;
                            else
                                BitValues2[count - 2][k++] = it ^= x;

                        }
                    }
                    else if (cntOne > 0) {
                        BitValues2[count++] = vector<int>(cntOne);
                        int i = 0;
                        for (auto it : values) {

                            BitValues2[count - 1][i++] = it;


                        }
                    }
                    else if (cntZero > 0) {
                        BitValues2[count++] = vector<int>(cntZero);
                        int i = 0;
                        for (auto it : values) {

                            BitValues2[count - 1][i++] = it;


                        }
                    }




                }
                swap(BitValues, BitValues3);
            }
            else {
                ans += bitValues.second;
                x = 1 << bit;
                int value = 1 << bit;
                int size = count;
                for (int j = 0; j <= size; j++) {

                    int cntZero = 0;
                    int cntOne = 0;
                    for (auto it : values) {
                        it ^= x;
                        if ((it & value) == value)
                            cntOne++, it ^= x;
                        else
                            cntZero++, it ^= x;

                    }
                    if (cntZero > 0 && cntOne > 0) {
                        BitValues2[count++] = vector<int>(cntZero);
                        BitValues2[count++] = vector<int>(cntOne);
                        int i = 0, k = 0;
                        for (auto it : values) {
                            it ^= x;
                            if ((it & value) == value)
                                BitValues2[count - 1][i++] = it ^= x;
                            else
                                BitValues2[count - 2][k++] = it ^= x;

                        }
                    }
                    else if (cntOne > 0) {
                        BitValues2[count++] = vector<int>(cntOne);
                        int i = 0;
                        for (auto it : values) {

                            BitValues2[count - 1][i++] = it;


                        }
                    }
                    else if (cntZero > 0) {
                        BitValues2[count++] = vector<int>(cntZero);
                        int i = 0;
                        for (auto it : values) {

                            BitValues2[count - 1][i++] = it;


                        }
                    }




                }
                swap(BitValues, BitValues3);
               
               
            }
        }
        else {
            ll sumBitOne = 0;
            ll sumBitZero = 0;
       
            int cnt = 0;
            for (int j = 0; j < count; j++) {
               
                pair<ll, ll> bitValues1 = InversionsAtBit(BitValues[j], bit, x);
               
                sumBitZero += bitValues1.first;
                    sumBitOne += bitValues1.second;
            }
                
                if (sumBitZero <= sumBitOne) {
                    ans += sumBitZero;
                    if (bit > 0) {
                        int value = 1 << bit;
                        int size = count;
                        for (int j = 0; j < size; j++) {
                            
                            int cntZero = 0;
                            int cntOne = 0;
                            for (auto it : BitValues[j]) {
                                it ^= x;
                                if ((it & value) == value)
                                    cntOne++,it ^= x;
                                else
                                    cntZero++, it ^= x;

                            }
                            if (cntZero > 0&& cntOne > 0) {
                                BitValues2[cnt++] = vector<int>(cntZero);
                                BitValues2[cnt++] = vector<int>(cntOne);
                                int i = 0, k = 0;
                                for (auto it : BitValues[j]) {
                                    it ^= x;
                                    if ((it & value) == value)
                                        BitValues2[cnt -1][i++] = it ^= x;
                                    else
                                        BitValues2[cnt - 2][k++] = it ^= x;

                                }
                            }
                            else if (cntOne > 0) {
                                BitValues2[cnt++] = vector<int>(cntOne);
                                int i = 0;
                                for (auto it : BitValues[j]) {
                                   
                                   BitValues2[cnt - 1][i++] = it;
                                   

                                }
                            }
                            else if (cntZero > 0) {
                                BitValues2[cnt++] = vector<int>(cntZero);
                                int i = 0;
                                for (auto it : BitValues[j]) {

                                    BitValues2[cnt - 1][i++] = it;


                                }
                            }

                          
                           

                        }
                        swap(BitValues, BitValues3);

                    }
                }
                else {
                    ans += sumBitOne;
                    x += 1 << bit;
                    if (bit > 0) {
                        int value = 1 << bit;
                        int size = count;
                        for (int j = 0; j < size; j++) {

                            int cntZero = 0;
                            int cntOne = 0;
                            for (auto it : BitValues[j]) {
                                it ^= x;
                                if ((it & value) == value)
                                    cntOne++, it ^= x;
                                else
                                    cntZero++, it ^= x;

                            }
                            if (cntZero > 0 && cntOne > 0) {
                                BitValues2[cnt++] = vector<int>(cntZero);
                                BitValues2[cnt++] = vector<int>(cntOne);
                                int i = 0, k = 0;
                                for (auto it : BitValues[j]) {
                                    it ^= x;
                                    if ((it & value) == value)
                                        BitValues2[cnt - 1][i++] = it ^= x;
                                    else
                                        BitValues2[cnt - 2][k++] = it ^= x;

                                }
                            }
                            else if (cntOne > 0) {
                                BitValues2[cnt++] = vector<int>(cntOne);
                                int i = 0;
                                for (auto it : BitValues[j]) {

                                    BitValues2[cnt - 1][i++] = it;


                                }
                            }
                            else if (cntZero > 0) {
                                BitValues2[cnt++] = vector<int>(cntZero);
                                int i = 0;
                                for (auto it : BitValues[j]) {

                                    BitValues2[cnt - 1][i++] = it;


                                }
                            }




                        }
                        swap(BitValues, BitValues3);

                    }
            }
            count = cnt;
        }

    }
}



pair<ll,ll> InversionsAtBit(vector<int>& values,int bit,int value) {
 
    ll cntZero = 0;
    ll cntOne = 0;
    int value1 = 1 << bit;
    ll inv1 = 0;
    for (auto it : values) {
        it ^= value;
        if ((it & value1) == value1)
            cntOne++;
        else
            inv1+= cntOne;
        it ^= value;
       
    }
   
    
    value += (1 << bit);
   
    cntZero = 0;
    cntOne = 0;
    ll inv2 = 0;
    for (auto it : values) {
        it ^= value;
        if ((it & value1) == value1)
            cntOne++;
        else
            inv2 += cntOne;
        it ^= value;
    }
   
    return { inv1,inv2 };
}
int main() {

    cin >> n;
   
    
    
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        
    }
    dp(nums);

    cout << ans << " " << x;
}