#include<bits/stdc++.h>
//Author: Max Paris
//Problem Link: http://codeforces.com/problemset/problem/372/B
//Ps: this got barely accepted because the timecomplexity O(q*n*n*m) isnt that good
using namespace std;
typedef long long ll;
vector<vector<ll>> rectangle;
vector<vector<char>> grid;
int n, m, q, r1, r2, c1, c2;
ll ans;
void dp(int& top, int& bottom, int column, bool& start, vector<int>& count) {
    if (start) {

        int cnt = 0;
        for (int i = top; i <= bottom; i++) {
            if (grid[i][column] == '0') {
                cnt++, count[i] = 1;

                ans += cnt;
            }
            else {

                cnt = 0, count[i] = 0;
            }
        }
        if (column + 1 <= c2) {
            start = false;
            return dp(top, bottom, column + 1, start, count);
        }
    }
    else {
       
    
        int cnt = 0;
        ll sum = 0;
    
        
        for (int i = top; i <= bottom; i++) {
            if (grid[i][column - 1] == '0' && grid[i][column] == '0') {
                
                
                cnt++;
               
                if (sum>0 && count[i] < count[i - 1] - 1) {
                    int value = count[i];
                    int value1 = count[i - 1] - 1;
                    for (int j = i-1; j >= top; j--) {
                        if (count[j]-1 <= value)
                            break;

                        else
                           value1=min(value1,count[j] - 1), sum += value-(value1);
                       
                    }
                }
                 sum += count[i];
                 count[i]++;

                ans += sum + cnt;


            }
            else if (grid[i][column] == '1') {
               
                sum = 0;
                count[i] = 0;
                cnt = 0;
              

            }
            else if (grid[i][column - 1] == '1' && grid[i][column] == '0') {
               
             
                sum = 0;
                cnt++;
                ans += cnt;
                count[i] = 1;
              
            }

        }
        if (column + 1 <= c2)
            return dp(top, bottom, column + 1, start, count);
    }

}





int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> q;


    grid = vector<vector<char>>(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            cin >> grid[i][j];
        }
    }

    vector<int> cnt(n);
    vector<ll> query(q);
    for (int i = 0; i < q; i++) {
        cin >> r1 >> c1 >> r2 >> c2;
        r1--, r2--, c1--, c2--;
        ans = 0;
        bool start = true;
        dp(r1, r2, c1, start, cnt);
        query[i] = ans;
    }
    for (int i = 0; i < q; i++)
        cout << query[i] << endl;

}