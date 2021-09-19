#include<bits/stdc++.h>
#include<unordered_map>
typedef long long ll;
typedef long double ld;
using namespace std;
//Author:Max Paris
//O(max(n,d)*log(n))
int t, n, m, q, d, k;
vector<tuple<int, int, int>> arr;



int main()
{
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> d >> n >> k;
       
        arr = vector<tuple<int, int, int>>(n);
        for (int i = 0; i < n; i++) {
            int x1, x2, x3;
            cin >> x1 >> x2 >> x3;
            arr[i] = {x2-1,x3-1,x1};
        }
       
        sort(arr.begin(), arr.end());
        multiset <int, greater <int> > values;
        multiset <pair<int,int>> rightBorder;
        ll sum = 0;
        ll ans = 0;
        int index = 0;
        auto KthElement = values.begin();
        for (int i = get<0>(arr[0]); i < d&&index<n; i++) {
            for (auto it = rightBorder.begin(); it != rightBorder.end();) {
                if (it->first < i) {
                    auto to =values.find(it->second);
                    if (*KthElement <= *to&& KthElement!=to) {
                        sum -= *to;
                        
                        values.erase(to);
                        if (values.size() >= k && k > 1)
                            KthElement++, sum += *KthElement;
                        else if (values.size() >= k && k == 1)
                            KthElement = values.begin(), sum += *KthElement;
                        
                    }
                    else if (KthElement == to) {
                        sum -= *to;
                        KthElement--;
                        values.erase(to);
                        if (values.size() >= k&&k>1)
                            KthElement++,sum+= *KthElement;
                        else if(values.size() >= k && k == 1)
                        KthElement=values.begin(), sum += *KthElement;
                    }
                    else values.erase(to);
                    
                    rightBorder.erase(it);
                    it = rightBorder.begin();
                    
                }
                else break;


            }




            while (index < n && i == get<0>(arr[index])) {
               
              
                
                if (values.size() < k) {
                    values.insert(get<2>(arr[index]));
                    rightBorder.insert({ get<1>(arr[index]),get<2>(arr[index]) });
                    sum += get<2>(arr[index]);
                    if (values.size() == 1)
                        KthElement = values.begin();
                    else if(get<2>(arr[index]) <= *KthElement)KthElement++;

                }
                else {
                    if (get<2>(arr[index]) > *KthElement) {
                        sum += -*KthElement + get<2>(arr[index]);
                    }
                    values.insert(get<2>(arr[index]));
                    rightBorder.insert({ get<1>(arr[index]),get<2>(arr[index]) });
                    if (get<2>(arr[index]) > *KthElement)
                        KthElement--;
                }
                index++;

           }
            
            ans = max(ans, sum);
        }
        
       
        cout << "Case #" << tc << ": " << ans<< endl;

    }

    return 0;

}