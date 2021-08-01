#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
vector<ll> st;

vector<ll> arr;

int minVal(int x, int y)

{

    return (x < y) ? x : y;

}

int getMid(int s, int e)

{

    return s + (e - s) / 2;

}

int RMQUtil( int ss, int se, int qs, int qe, int index)

{

    if (qs <= ss && qe >= se)

        return st[index];



    if (se < qs || ss > qe)

        return INT_MAX;



    int mid = getMid(ss, se);

    return minVal(RMQUtil( ss, mid, qs, qe, 2 * index + 1), RMQUtil( mid + 1, se, qs, qe, 2 * index + 2));

}

int RMQ( int n, int qs, int qe)

{

    if (qs < 0 || qe > n - 1 || qs > qe)

    {

        cout << "Invalid Input";

        return -1;

    }

    return RMQUtil( 0, n - 1, qs, qe, 0);

}

int constructSTUtil( int ss, int se, int si)

{

    if (ss == se)

    {

        st[si] = arr[ss];

        return arr[ss];

    }

    int mid = getMid(ss, se);

    st[si] = minVal(constructSTUtil( ss, mid, si * 2 + 1), constructSTUtil( mid + 1, se, si * 2 + 2));

    return st[si];

}

void constructST( int n)

{

    int x = (int)(ceil(log2(n)));

    int max_size = (int)pow(2, x+1) - 1;

    st = vector<ll> (max_size);

    constructSTUtil( 0, n - 1, 0);

  

}



int main()

{
   
     arr = { 1, 3, 2, 7, 9, 11 };

     int n = int(arr.size());

    constructST( n);

    int qs = 1;

    int qe = 5;

    cout << "Minimum of values in range["<<qs<<" to "<<qe<<"] is ="<< RMQ( n, qs, qe)<<endl;

}