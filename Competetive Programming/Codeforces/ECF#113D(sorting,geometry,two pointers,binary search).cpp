#include<bits/stdc++.h>

//Author: Max Paris
//Problem Link: http://codeforces.com/contest/1569/problem/D
//O(t*(p*log(p)+m+n))

using namespace std;
typedef long long ll;
typedef long double ld;
ll ans = 0;
int n,m,t,p;
int Indexes[(int)1e6 + 1];



   int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        ans = 0;
        cin >> n>>m>>p;
        vector<int> streetsVertical(n);
        for (int i = 0; i < n; i++)
            cin >> streetsVertical[i];
      
        vector<int> streetsHorizontal(m);
        for (int i = 0; i < m; i++)
            cin >> streetsHorizontal[i];
    
        vector<pair<int, int>> personsVertical(p);
        vector<pair<int, int>> personsHorizontal(p);
        int sizePersonsVertical = 0, sizePersonsHorizontal = 0;
        for (int i = 0; i < p; i++) {
            int x1, x2;
            cin >> x1 >> x2;
            bool isVertical = binary_search(streetsVertical.begin(), streetsVertical.end(), x1);
            bool isHorizontal = binary_search(streetsHorizontal.begin(), streetsHorizontal.end(), x2);
            if (isVertical&&!isHorizontal)
                personsVertical[sizePersonsVertical] = { x2,x1 }, sizePersonsVertical++;
            
            else if (isHorizontal&& !isVertical)
                personsHorizontal[sizePersonsHorizontal] = { x1,x2 }, sizePersonsHorizontal++;
        }
        sort(personsVertical.begin(), personsVertical.begin() + sizePersonsVertical);
        sort(personsHorizontal.begin(), personsHorizontal.begin() + sizePersonsHorizontal);
            
        int lastindex = 0;
        for (int row = 1, index = 0, cnt = 0; index < sizePersonsVertical&&row<m;) {
            if (streetsHorizontal[row] > personsVertical[index].first) {
                ans += cnt - Indexes[personsVertical[index].second];
                cnt++; Indexes[personsVertical[index].second]++;
                index++;
            }
            else {
                cnt = 0;
                row++;
                for (int i = lastindex; i < index; i++)
                    Indexes[personsVertical[i].second] = 0;
                lastindex = index;
            }
        }
        for (int i = lastindex; i < sizePersonsVertical; i++)
            Indexes[personsVertical[i].second] = 0;

        lastindex = 0;

        for (int column = 1, index = 0, cnt = 0; index < sizePersonsHorizontal && column < n;) {
            if (streetsVertical[column] > personsHorizontal[index].first) {
                ans += cnt - Indexes[personsHorizontal[index].second];
                cnt++; Indexes[personsHorizontal[index].second]++;
                index++;
            }
            else {
                cnt = 0;
                column++;
                for (int i = lastindex; i < index; i++)
                    Indexes[personsHorizontal[i].second] = 0;

                lastindex = index;
            }
        }

        for (int i = lastindex; i < sizePersonsHorizontal; i++)
            Indexes[personsHorizontal[i].second] = 0;
       
        cout << ans << endl;
    }
}