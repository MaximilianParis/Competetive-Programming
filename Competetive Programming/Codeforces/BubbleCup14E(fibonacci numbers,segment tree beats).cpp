#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long ld;
int n, q;
const int Mod = 1e9 + 7;
const int Mod1 = 2.5e5;
vector<int> A1;
vector<int> A2;
const int normal[2][2] = { {0,1}, {1,1} };
const int inv[2][2] = { {-1,1}, {1,0} };
const int normal1[2][2] = { {192827593, 608672132},{ 608672132 ,801499725 } };
const int inv1[2][2] = { {801499725, -608672132},{ -608672132 ,192827593 } };
int matrix[Mod1][2][2];
int matrix_inverse[Mod1][2][2];
int matrix1[Mod1][2][2];
int matrix_inverse1[Mod1][2][2];
pair<int, int> operator+(const std::pair<int, int>& a, const  std::pair<int, int>& b)
{
    return make_pair((a.first + b.first * 1l) % Mod, (a.second + b.second * 1l) % Mod);
}

struct TopDownSegmentTreeBeats {
    // limit for array size
    int n;
    int N;
    int cnt = 1;

    vector<vector<vector<ll>>> beat;

    vector<vector<pair<int, int>>> fibValues;

    //Lazy Update
    vector<vector<ll>> lazyUpdate;


    // default Values
    ll defaultValue;
    vector<bool> Updates;

    //construct segment tree with specific default value and merge function
    TopDownSegmentTreeBeats(int n, ll defaultValue) {
        this->n = n;
        int pow = ceil(log2(n));
        this->N = (2 << (pow)) - 1;

        this->defaultValue = defaultValue;



        beat = vector<vector<vector<ll>>>(N, vector<vector< ll>>(2, vector<ll>(4)));

        lazyUpdate = vector<vector<ll>>(N, vector<ll>(2, defaultValue));
        fibValues = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(9));
      
        fib();
        build(0, n - 1, 0);
    }

    pair<int, int> mult(long index, pair<int, int> x1 = { 0,1 }) {
        pair<int, int> ans;
        if (index > 0) {

            index--;
            if (index < Mod1) {
                ans.first = ((1ll * x1.first * matrix[index][0][0]) % Mod + (1ll * x1.second * matrix[index][1][0]) % Mod) % Mod;
                ans.second = ((1ll * x1.first * matrix[index][0][1]) % Mod + (1ll * x1.second * matrix[index][1][1]) % Mod) % Mod;
            }
            else {
                int curr[2][2] = { {0,0},{0,0} };
                int rest = (index + 1) % Mod1;
                int div = (index + 1) / Mod1;
                div--;
                rest--;
                if (rest == -1) {
                    curr[0][0] = matrix1[div][0][0];
                    curr[0][1] = matrix1[div][0][1];
                    curr[1][0] = matrix1[div][1][0];
                    curr[1][1] = matrix1[div][1][1];
                }
                else {
                    for (int j = 0; j < 2; j++) {
                        for (int k = 0; k < 2; k++) {
                            for (int l = 0; l < 2; l++) {

                                curr[j][k] = (curr[j][k] + 1ll * matrix[rest][j][l] * matrix1[div][l][k]) % Mod;


                            }
                        }
                    }
                }
                ans.first = ((1ll * x1.first * curr[0][0]) % Mod + (1ll * x1.second * curr[1][0]) % Mod) % Mod;
                ans.second = ((1ll * x1.first * curr[0][1]) % Mod + (1ll * x1.second * curr[1][1]) % Mod) % Mod;
            }

        }
        else if (index < 0) {
            index *= -1;
            index--;
            if (index < Mod1) {
                ans.first = ((1ll * x1.first * matrix_inverse[index][0][0]) % Mod + (1ll * x1.second * matrix_inverse[index][1][0]) % Mod) % Mod;
                while (ans.first < 0)
                    ans.first += Mod;
                ans.second = ((1ll * x1.first * matrix_inverse[index][0][1]) % Mod + (1ll * x1.second * matrix_inverse[index][1][1]) % Mod) % Mod;
                while (ans.second < 0)
                    ans.second += Mod;
            }
            else {
                int curr[2][2] = { {0,0},{0,0} };
                int rest = (index + 1) % Mod1;
                int div = (index + 1) / Mod1;
                div--;
                rest--;
                if (rest == -1) {
                    curr[0][0] = matrix_inverse1[div][0][0];
                    curr[0][1] = matrix_inverse1[div][0][1];
                    curr[1][0] = matrix_inverse1[div][1][0];
                    curr[1][1] = matrix_inverse1[div][1][1];
                }
                else {
                    for (int j = 0; j < 2 && rest >= 0; j++) {
                        for (int k = 0; k < 2; k++) {
                            for (int l = 0; l < 2; l++) {

                                curr[j][k] = (curr[j][k] + 1ll * matrix_inverse[rest][j][l] * matrix_inverse1[div][l][k]) % Mod;


                            }
                        }
                    }
                }
                ans.first = ((1ll * x1.first * curr[0][0]) % Mod + (1ll * x1.second * curr[1][0]) % Mod) % Mod;
                ans.second = ((1ll * x1.first * curr[0][1]) % Mod + (1ll * x1.second * curr[1][1]) % Mod) % Mod;
                while (ans.first < 0)
                    ans.first += Mod;
                while (ans.second < 0)
                    ans.second += Mod;
            }
        }
        else ans = x1;

        return ans;

    }


    void fib() {
        matrix[0][0][0] = 0;
        matrix[0][0][1] = 1;
        matrix[0][1][0] = 1;
        matrix[0][1][1] = 1;
        matrix_inverse[0][0][0] = -1;
        matrix_inverse[0][0][1] = 1;
        matrix_inverse[0][1][0] = 1;
        matrix_inverse[0][1][1] = 0;
        for (int i = 1; i < Mod1; i++) {
            matrix[i][0][0] = 0;
            matrix[i][0][1] = 0;
            matrix[i][1][0] = 0;
            matrix[i][1][1] = 0;
            matrix_inverse[i][0][0] = 0;
            matrix_inverse[i][0][1] = 0;
            matrix_inverse[i][1][0] = 0;
            matrix_inverse[i][1][1] = 0;
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int l = 0; l < 2; l++) {

                        matrix[i][j][k] = (1ll * matrix[i][j][k] + matrix[i - 1][j][l] * normal[l][k]) % Mod;
                        matrix_inverse[i][j][k] = (1ll * matrix_inverse[i][j][k] + matrix_inverse[i - 1][j][l] * inv[l][k]) % Mod;

                    }
                }
            }
        }
        int index = Mod1 - 1;

        matrix1[0][0][0] = matrix[index][0][0];
        matrix1[0][0][1] = matrix[index][0][1];
        matrix1[0][1][0] = matrix[index][1][0];
        matrix1[0][1][1] = matrix[index][1][1];
        matrix_inverse1[0][0][0] = matrix_inverse[index][0][0];
        matrix_inverse1[0][0][1] = matrix_inverse[index][0][1];
        matrix_inverse1[0][1][0] = matrix_inverse[index][1][0];
        matrix_inverse1[0][1][1] = matrix_inverse[index][1][1];
        for (int i = 1; i < Mod1; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int l = 0; l < 2; l++) {

                        matrix1[i][j][k] = (matrix1[i][j][k] + 1ll * matrix1[i - 1][j][l] * normal1[l][k]) % Mod;
                        matrix_inverse1[i][j][k] = (matrix_inverse1[i][j][k] + 1ll * matrix_inverse1[i - 1][j][l] * inv1[l][k]) % Mod;

                    }
                }
            }
        }


    }

    int getMiddle(int l, int r) {

        return l + (r - l) / 2;

    }
    void merge(int& pos) {



        int childindex1 = 2 * pos + 1;
        int childindex2 = childindex1 + 1;
        beat[pos][0][0] = max(beat[childindex1][0][0], beat[childindex2][0][0]);

        long x1 = min(beat[childindex1][0][0], beat[childindex2][0][0]);
        long x2 = max(beat[childindex1][0][1], beat[childindex2][0][1]);

        beat[pos][0][1] = max(x1, x2);


        beat[pos][1][0] = max(beat[childindex1][1][0], beat[childindex2][1][0]);

        x1 = min(beat[childindex1][1][0], beat[childindex2][1][0]);
        x2 = max(beat[childindex1][1][1], beat[childindex2][1][1]);

        beat[pos][1][1] = max(x1, x2);


        beat[pos][0][2] = min(beat[childindex1][0][2], beat[childindex2][0][2]);

        x1 = max(beat[childindex1][0][2], beat[childindex2][0][2]);
        x2 = min(beat[childindex1][0][3], beat[childindex2][0][3]);


        beat[pos][0][3] = min(x1, x2);


        beat[pos][1][2] = min(beat[childindex1][1][2], beat[childindex2][1][2]);

        x1 = max(beat[childindex1][1][2], beat[childindex2][1][2]);
        x2 = min(beat[childindex1][1][3], beat[childindex2][1][3]);


        beat[pos][1][3] = min(x1, x2);
        int childindex = childindex1;
        int curr = 0;
        int n1 = 0;
        int n2 = 0;
        fill(fibValues[pos].begin(), fibValues[pos].end(), make_pair(0, 0));
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][0][0] == beat[childindex][0][n1] && beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][0] = fibValues[pos][0] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][1] = fibValues[pos][1] + fibValues[childindex][curr];
            else if (beat[pos][0][0] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][2] = fibValues[pos][2] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];
            else if (beat[pos][0][0] == beat[childindex][0][n1])
                fibValues[pos][4] = fibValues[pos][4] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];
            else if (beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][6] = fibValues[pos][6] + fibValues[childindex][curr];
            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][0][0] == beat[childindex][0][n1] && beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][0] = fibValues[pos][0] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][1] = fibValues[pos][1] + fibValues[childindex][curr];
            else if (beat[pos][0][0] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][2] = fibValues[pos][2] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];
            else if (beat[pos][0][0] == beat[childindex][0][n1])
                fibValues[pos][4] = fibValues[pos][4] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];
            else if (beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][6] = fibValues[pos][6] + fibValues[childindex][curr];
            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        n1 = 2;

        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][1] = fibValues[pos][1] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];
            else if (beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][6] = fibValues[pos][6] + fibValues[childindex][curr];

            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][1] = fibValues[pos][1] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];
            else if (beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][6] = fibValues[pos][6] + fibValues[childindex][curr];

            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        n1 = 0;
        n2 = 2;
        if (fibValues[childindex][curr].second != 0) {

            if (beat[pos][0][0] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][2] = fibValues[pos][2] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];
            else if (beat[pos][0][0] == beat[childindex][0][n1])
                fibValues[pos][4] = fibValues[pos][4] + fibValues[childindex][curr];

            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {

            if (beat[pos][0][0] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][2] = fibValues[pos][2] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];
            else if (beat[pos][0][0] == beat[childindex][0][n1])
                fibValues[pos][4] = fibValues[pos][4] + fibValues[childindex][curr];

            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        n1 = 2;
        if (fibValues[childindex][curr].second != 0) {

            if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];

            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];

            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {

            if (beat[pos][0][2] == beat[childindex][0][n1] && beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][3] = fibValues[pos][3] + fibValues[childindex][curr];

            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];

            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        n1 = 0;
        if (fibValues[childindex][curr].second != 0) {

            if (beat[pos][0][0] == beat[childindex][0][n1])
                fibValues[pos][4] = fibValues[pos][4] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];

            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {

            if (beat[pos][0][0] == beat[childindex][0][n1])
                fibValues[pos][4] = fibValues[pos][4] + fibValues[childindex][curr];
            else if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];

            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        n1 = 2;

        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];

            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][0][2] == beat[childindex][0][n1])
                fibValues[pos][5] = fibValues[pos][5] + fibValues[childindex][curr];

            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        n2 = 0;
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][6] = fibValues[pos][6] + fibValues[childindex][curr];
            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][1][0] == beat[childindex][1][n2])
                fibValues[pos][6] = fibValues[pos][6] + fibValues[childindex][curr];
            else if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        n2 = 2;
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex++;
        if (fibValues[childindex][curr].second != 0) {
            if (beat[pos][1][2] == beat[childindex][1][n2])
                fibValues[pos][7] = fibValues[pos][7] + fibValues[childindex][curr];
            else
                fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        }
        childindex--;
        curr++;
        if (fibValues[childindex][curr].second != 0)
            fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];
        childindex++;
        if (fibValues[childindex][curr].second != 0)
            fibValues[pos][8] = fibValues[pos][8] + fibValues[childindex][curr];

    }
    void build(int l, int r, int pos)
    {
        //if we are at leaf
        if (l == r)
        {

            
            beat[pos][0][0] = { A1[l] };
            beat[pos][0][1] = { -defaultValue };
            beat[pos][1][0] = { A2[l] };
            beat[pos][1][1] = { -defaultValue };
            beat[pos][0][2] = { A1[l] };
            beat[pos][0][3] = { defaultValue };
            beat[pos][1][2] = { A2[l] };
            beat[pos][1][3] = { defaultValue };
            fibValues[pos][0] = mult(A1[l] + A2[l]);




        }
        //not at leaf then merge childs
        else {

            int mid = getMiddle(l, r);
            build(l, mid, pos * 2 + 1);
            build(mid + 1, r, pos * 2 + 2);

            merge(pos);

        }

    }
    void updateMax(int& pos, bool& i, bool& leaf, ll& val) {





        if (beat[pos][i][0] > val) {
            int diff = val - beat[pos][i][0];
            beat[pos][i][0] = val;
            if (fibValues[pos][0].second != 0)
                fibValues[pos][0] = mult(diff, fibValues[pos][0]);
            if (!i) {
                if (fibValues[pos][2].second != 0)
                    fibValues[pos][2] = mult(diff, fibValues[pos][2]);
                if (fibValues[pos][4].second != 0)
                    fibValues[pos][4] = mult(diff, fibValues[pos][4]);
            }
            else {
                if (fibValues[pos][1].second != 0)
                    fibValues[pos][1] = mult(diff, fibValues[pos][1]);
                if (fibValues[pos][6].second != 0)
                    fibValues[pos][6] = mult(diff, fibValues[pos][6]);
            }
            if (beat[pos][i][2] > val)
                beat[pos][i][2] = val;

            if (beat[pos][i][3] > val && beat[pos][i][3] != defaultValue)
                beat[pos][i][3] = val;
            if (beat[pos][i][1] > val && beat[pos][i][1] != -defaultValue)
                beat[pos][i][1] = val;

           

        }


      






    }
    void updateMin(int& pos, bool& i, bool& leaf, ll& val) {
        if (beat[pos][i][2] < val) {
            int diff = val - beat[pos][i][2];
            beat[pos][i][2] = val;
            if (!leaf) {
                if (fibValues[pos][3].second != 0)
                    fibValues[pos][3] = mult(diff, fibValues[pos][3]);
                if (!i) {
                    if (fibValues[pos][1].second != 0)
                        fibValues[pos][1] = mult(diff, fibValues[pos][1]);
                    if (fibValues[pos][5].second != 0)
                        fibValues[pos][5] = mult(diff, fibValues[pos][5]);
                }
                else {
                    if (fibValues[pos][2].second != 0)
                        fibValues[pos][2] = mult(diff, fibValues[pos][2]);
                    if (fibValues[pos][7].second != 0)
                        fibValues[pos][7] = mult(diff, fibValues[pos][7]);
                }





            }
            else  fibValues[pos][0] = mult(diff, fibValues[pos][0]);

            if (beat[pos][i][0] < val)
                beat[pos][i][0] = val;
            if (beat[pos][i][1] < val && beat[pos][i][1] != -defaultValue)
                beat[pos][i][1] = val;
            if (beat[pos][i][3] < val && beat[pos][i][3] != defaultValue)
                beat[pos][i][3] = val;

           
        }



      
    }
    void updateAdd(int& pos, bool& i, bool& leaf) {

        beat[pos][i][0] = beat[pos][i][0] + lazyUpdate[pos][i];
        if (beat[pos][i][1] != -defaultValue)
            beat[pos][i][1] = beat[pos][i][1] + lazyUpdate[pos][i];
        beat[pos][i][2] = beat[pos][i][2] + lazyUpdate[pos][i];
        if (beat[pos][i][3] != defaultValue)
            beat[pos][i][3] = beat[pos][i][3] + lazyUpdate[pos][i];
        for (int k = 0; k < 9; k++) {
            if (fibValues[pos][k].second != 0)
                fibValues[pos][k] = mult(lazyUpdate[pos][i], fibValues[pos][k]);
        }

        if (!leaf) {
            int next = 2 * pos + 1;
            int next1 = next + 1;
            if (lazyUpdate[next][i] == defaultValue)
                lazyUpdate[next][i] = 0;
            lazyUpdate[next][i] = lazyUpdate[pos][i] + lazyUpdate[next][i];
            if (lazyUpdate[next1][i] == defaultValue)
                lazyUpdate[next1][i] = 0;
            lazyUpdate[next1][i] = lazyUpdate[pos][i] + lazyUpdate[next1][i];
        }

        lazyUpdate[pos][i] = defaultValue;
        
    }






    bool firstCondition(bool& i, int& type, ll& x, int& pos) {
        if (type == 0)
            return beat[pos][i][0] <= x;
        else if (type == 1)
            return beat[pos][i][2] >= x;
        else
            return false;
    }

    bool secondCondition(bool& i, int& type, ll& x, int& pos) {
        if (type == 0)
            return beat[pos][i][1] < x;
        else if (type == 1)
            return beat[pos][i][3] > x;
        else
            return true;
    }
    // function to perfom update
    void update_Range(int l, int r, int& l1, int& r1, bool& i, int& type, ll& x, int pos, int last = -1) {



        //out of range
        if (r < l1 || l > r1 || firstCondition(i, type, x, pos))return;
        //continue updating
        bool leaf = l == r;
        //in range
        if (l1 <= l && r <= r1 && secondCondition(i, type, x, pos)) {

            if (type == 0)
                updateMax(pos, i, leaf, x);
            else if (type == 1)
                updateMin(pos, i, leaf, x);
            else
                lazyUpdate[pos][i] = x, updateAdd(pos, i, leaf);



            return;
        }

        leaf = false;
        int mid = getMiddle(l, r);
        bool a = false;

        if (l != r) {
            int next = 2 * pos + 1;
            int next1 = next + 1;
            leaf = l == mid;
           
                if (lazyUpdate[next][a] != defaultValue)
                    updateAdd(next, a, leaf);
                updateMax(next, a, leaf, beat[pos][a][0]);
                updateMin(next, a, leaf, beat[pos][a][2]);

                a = true;

                if (lazyUpdate[next][a] != defaultValue)
                    updateAdd(next, a, leaf);
                updateMax(next, a, leaf, beat[pos][a][0]);
                updateMin(next, a, leaf, beat[pos][a][2]);
           

            leaf = mid + 1 == r;
            a = false;
            
                if (lazyUpdate[next1][a] != defaultValue)
                    updateAdd(next1, a, leaf);
                updateMax(next1, a, leaf, beat[pos][a][0]);
                updateMin(next1, a, leaf, beat[pos][a][2]);

                a = true;

                if (lazyUpdate[next1][a] != defaultValue)
                    updateAdd(next1, a, leaf);
                updateMax(next1, a, leaf, beat[pos][a][0]);
                updateMin(next1, a, leaf, beat[pos][a][2]);
           



        }
        // merge childs

        update_Range(l, mid, l1, r1, i, type, x, 2 * pos + 1);
        update_Range(mid + 1, r, l1, r1, i, type, x, 2 * pos + 2);

        merge(pos);

    }

    void update_Range(int l1, int r1, bool& a, int& type, ll x) {
        return update_Range(0, n - 1, l1, r1, a, type, x, 0);
    }

    // function to get merge values on interval [l, r]
    pair<int, int> query(int begin, int end, int& l, int& r, int pos)
    {
        //out of range
        if (end < l || begin > r)return { 0,0 };



        //in range
        if (l <= begin && r >= end) {
            pair<int, int> ans = fibValues[pos][0];
            for (int i = 1; i < 9; i++) {
                if (fibValues[pos][i].second != 0)
                    ans = ans + fibValues[pos][i];
            }
            return ans;
        }
        bool leaf = false;
        int mid = getMiddle(begin, end);
        bool a = false;
       
        if (begin != end) {
            int next = 2 * pos + 1;
            int next1 = next + 1;
            leaf = begin == mid;
            if (!(mid < l || begin > r)) {
                if (lazyUpdate[next][a] != defaultValue)
                    updateAdd(next, a, leaf);
                updateMax(next, a, leaf, beat[pos][a][0]);
                updateMin(next, a, leaf, beat[pos][a][2]);

                a = true;
                if (lazyUpdate[next][a] != defaultValue)
                    updateAdd(next, a, leaf);
                updateMax(next, a, leaf, beat[pos][a][0]);
                updateMin(next, a, leaf, beat[pos][a][2]);
            }
            if (!(end < l || mid+1 > r)) {
                leaf = mid + 1 == end;
                a = false;
                if (lazyUpdate[next1][a] != defaultValue)
                    updateAdd(next1, a, leaf);
                updateMax(next1, a, leaf, beat[pos][a][0]);
                updateMin(next1, a, leaf, beat[pos][a][2]);

                a = true;
                if (lazyUpdate[next1][a] != defaultValue)
                    updateAdd(next1, a, leaf);
                updateMax(next1, a, leaf, beat[pos][a][0]);
                updateMin(next1, a, leaf, beat[pos][a][2]);
            }



        }

        // merge childs

        pair<int, int> x1 = query(begin, mid, l, r, 2 * pos + 1);
        pair<int, int> x2 = query(mid + 1, end, l, r, 2 * pos + 2);
       

        return x1 + x2;
    }

    pair<int, int> query(int l, int r) {
        return query(0, n - 1, l, r, 0);
    }

};

int main()
{

    scanf("%d%d", &n, &q);

    A1 = vector<int>(n);
    A2 = vector<int>(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A1[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &A2[i]);
    ll border = ll(1e11);
    TopDownSegmentTreeBeats tree(n, border);

    while (q--) {
        int x2, x3, x4, x5;
        int x1;
        scanf("%d", &x2);
        if (x2 == 4) {
            scanf("%d%d", &x2, &x3);
            x2--, x3--;
            int ans = tree.query(x2, x3).first;
            printf("%d\n", ans);
            
        }
        else {
            scanf("%d%d%d%d", &x1, &x3, &x4, &x5);

            if (x2 != 3 || x5 != 0) {
                x2--, x3--, x4--;
                bool arr = x1 == 2;
                tree.update_Range(x3, x4, arr, x2, ll(x5));
            }
        }
    }
}
