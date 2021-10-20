#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const double pi = acos(-1);
const int maxn = 2e5 + 10;
int n, n1, n2;
int rev[maxn << 1];

struct Complex{
	double x, y;

	Complex operator +(Complex tmp){
		return (Complex){x + tmp.x, y + tmp.y}; 
	}

	Complex operator -(Complex tmp){
		return (Complex){x - tmp.x, y - tmp.y};
	}

	Complex operator *(Complex tmp){
		return (Complex){x * tmp.x - y * tmp.y, x * tmp.y + y * tmp.x};
	}
}a[maxn], b[maxn];

void init_rev(){
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
				y[i + j] = y0 + y1;
				y[i + j + (k >> 1)] = y0 - y1;
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	char s1[maxn], s2[maxn];
	while(scanf("%s%s", s1, s2) != EOF){
		int l = 0, r = 0;
		if(s1[0] == '-') l = 1;
		if(s2[0] == '-') r = 1;
		n1 = strlen(s1) - 1 - l;
		n2 = strlen(s2) - 1 - r;
		n = 1;
		while(n <= (n1 + n2)) n <<= 1;
		For(i, 0, n) a[i].x = a[i].y = b[i].x = b[i].y = 0; 
		For(i, 0, n1) a[n1 - i].x = s1[i + l] - '0';
		For(i, 0, n2) b[n2 - i].x = s2[i + r] - '0';
		init_rev();
		FFT(a, 1);
		FFT(b, 1);
		For(i, 0, n - 1) a[i] = a[i] * b[i];
		FFT(a, -1);
		int ans[maxn << 1], pre = 0;
		For(i, 0, n1 + n2){
			int x = (int)(a[i].x / n + 0.5) + pre;
			pre = x / 10;
			x %= 10;
			ans[n1 + n2 - i] = x;
		}
		if(l ^ r) putchar('-');
		if(pre) printf("%d", pre);
		For(i, 0, n1 + n2) printf("%d", ans[i]);
		puts("");
	}
}//数据有前导零，没有判断
