#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const int maxn = 4e5 + 10, N = 3e4;
const double pi = cos(-1);
int n, n1, n2, n3;
int num1[maxn], num2[maxn];
LL rev[maxn];
struct Complex{
	double x, y;

	Complex(){ x = y = 0; }
	Complex(double xx, double yy){ x = xx, y = yy; }

	Complex operator +(Complex res){
		return (Complex){x + res.x, y + res.y};
	}

	Complex operator -(Complex res){
		return (Complex){x - res.x, y - res.y};
	}

	Complex operator *(Complex res){
		return (Complex){x * res.x - res.y * y, x * res.y + y * res.x};
	}
}a[maxn], b[maxn];

void init(){
	For(i, 0, n - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
}

void FFT(Complex *y, int tp){
	For(i, 0, n - 1) if(i < rev[i]) swap(y[i], y[rev[i]]);
	for(int k = 2; k <= n; k <<= 1){
		Complex wn = (Complex){cos(2 * pi / k), sin(2 * pi / k) * tp};
		for(int i = 0; i < n; i += k){
			Complex x = (Complex){1, 0};
			for(int j = 0; j < (k >> 1); ++j, x = x * wn){
				Complex y0 = y[i + j], y1 = x * y[i + j + (k >> 1)];
				y[i + j] = y0 + y1, y[i + j + (k >> 1)] = y0 - y1;
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int x, l1 = 0, l2 = 0;
	n = 1;
	scanf("%d", &n1);
	For(i, 1, n1){
		scanf("%d", &x), ++a[x + N].x, l1 = max(l1, x + N);
	}
	scanf("%d", &n2);
	For(i, 1, n2){
		scanf("%d", &x), ++num1[(x + N) << 1];
	}
	scanf("%d", &n3);
	For(i, 1, n3){
		scanf("%d", &x), ++b[x + N].x, l2 = max(l2, x + N);
	}
	while(n <= l1 + l2) n <<= 1;
	init();
	FFT(a, 1);
	FFT(b, 1);
	For(i, 0, n - 1) a[i] = a[i] * b[i];
	FFT(a, -1);
	For(i, 0, n - 1){
		num2[i] = (LL)(a[i].x / n + 0.5);
		if(a[i].x != 0) cout<<i<<" "<<a[i].x<<endl;
	}
	LL ans = 0;
	For(i, 0, n - 1) ans += 1ll * num1[i] * num2[i];
	printf("%lld\n", ans);
	return 0;
}
