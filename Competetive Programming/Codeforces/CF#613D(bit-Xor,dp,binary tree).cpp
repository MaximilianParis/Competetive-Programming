#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: http://codeforces.com/problemset/problem/1285/D
using namespace std;
vector<int> numbers;
int n;
int dp(vector<int>& currentNumbers, int bit){
    if (bit < 0)return 0;
    else {
        int bitValue = 1 << bit;
        //seperate in to two groups with bit on and off
        vector<int> bitOn;
        vector<int> bitOff;
        for (auto& number : currentNumbers) {
            //check if number has bit
            if ((number & bitValue) == bitValue)
                bitOn.push_back(number);
            else
                bitOff.push_back(number);
        }
        //continue with non empty group
        if (bitOn.size() == 0) return dp(bitOff, bit - 1);
        if (bitOff.size() == 0) return dp(bitOn, bit - 1);
        //if both are not empty take min of childs and add bitvalue
        return min(dp(bitOff, bit - 1), dp(bitOn, bit - 1)) + bitValue;
    }
}






int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    numbers.resize(n);
    for (auto& number : numbers) cin >> number;
    //root at 30 that way childsum is smaller then the bit value of current node
    cout << dp(numbers, 30) << endl;
}