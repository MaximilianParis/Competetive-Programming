#include<bits/stdc++.h>
using namespace std;

#define PI 3.141592654
typedef complex<double> base;  // stl complex class


void fft(vector<base>& a, bool& invert) {
	int n = (int)a.size();

	if (n == 1) return;
	int half = n / 2;
	vector<base> y0(half), y1(half);   // y0 and y1

	for (int i = 0, j = 0; i < n; i += 2, ++j) {        // initialisation of the vectors
		y0[j] = a[i];
		y1[j] = a[i + 1];
	}

	fft(y0, invert);
	fft(y1, invert);

	double ang = 2 * PI / n * (invert ? -1 : 1);   // setting angle acc. to invert or non invert
	base w(1), wn(cos(ang), sin(ang));   // setting wn for use and initialising w to 1
	
	for (int k = 0; k < half; ++k) {

		a[k] = y0[k] + w * y1[k];                  // y(k)
		a[k + half] = y0[k] - w * y1[k];         // y(k+n/2)

		 // if we are doing inverse fft, we have to divide by n at each step
		if (invert)
			a[k] /= 2, a[k + half] /= 2;

		w *= wn;            // changing wn (from 1 to i, -1, -i etc) depending on the choice of w
	}
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& res)
{
	vector<base> fx(a.begin(), a.end()), fy(b.begin(), b.end()), hx;

	size_t n = max(1<<int(ceil(log2(a.size()))), 1<<int(ceil(log2(b.size()))))*2;

	//while (n < max(a.size(), b.size())) n <<= 1;  // finding power of 2, i.e size of hx 
	//n <<= 1;

	fx.resize(n), fy.resize(n), hx.resize(n);

	// finding fft of fx and gx and then multiplying each term of both to obtain
	// fft of hx
	bool invert = false;
	fft(fx, invert), fft(fy, invert);

	for (size_t i = 0; i < n; ++i)
		hx[i] = fx[i] * fy[i];

	invert = true;
	fft(hx, invert);  // inverse fft of hx
	res.resize(n);

	// storing the result coeficients
	for (size_t i = 0; i < n; ++i)
		res[i] = int(hx[i].real() + 0.5);

}


int main() {

	
	int n, m;
	cin >> n;
	vector<int> fx(n);
	for (int i = 0; i < n; i++)
		cin >> fx[i];

	cin >> m;
	vector<int> gx(m);

	for (int i = 0; i < m; i++)
		cin >> gx[i];

      vector<int> res;

	multiply(fx, gx, res);

	for (int i = 0; i < res.size(); i++)
		cout << res[i] << " ";           
	cout << endl;


	return 0;
}
