#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const LL mod = 998244353;
const int maxn = 2e5 + 10;
LL ans[maxn][3];

inline LL fadd(LL x, LL y){
	return x + y >= mod ? x + y - mod : x + y;
}

inline LL fdel(LL x, LL y){
	return x - y < 0 ? x - y + mod : x - y;
}

void FWT_and(LL f[], LL n, LL tp){ //A[0] + A[1], A[1]
	for(int o = 2, k = 1; o <= n; o <<= 1, k <<= 1){
		for(int i = 0; i < n; i += o) 
			for(int j = 0; j < k; ++j){
				f[i + j] += tp * f[i + j + k];

				f[i + j] %= mod;
				f[i + j] = fdel(f[i + j], 0);
			}
	}
}

void FWT_or(LL f[], LL n, LL tp){ //A[0], A[0] + A[1]
	for(int o = 2, k = 1; o <= n; o <<= 1, k <<= 1){
		for(int i = 0; i < n; i += o) 
			for(int j = 0; j < k; ++j){
				f[i + j + k] += tp * f[i + j] % mod;

				f[i + j + k] %= mod;
				f[i + j + k] = fdel(f[i + j + k], 0);
			}
	}
}

void FWT_xor(LL f[], LL n, LL tp){ // A[0] + A[1], A[0] - A[1]
	for(int o = 2, k = 1; o <= n; o <<= 1, k <<= 1){
		for(int i = 0; i < n; i += o) 
			for(int j = 0; j < k; ++j){
				f[i + j] += f[i + j + k];
				f[i + j + k] = f[i + j] - f[i + j + k] - f[i + j + k];
				f[i + j] *= tp;
				f[i + j + k] *= tp;

				f[i + j] %= mod;
				f[i + j] = fdel(f[i + j], 0);
				f[i + j + k] %= mod;
				f[i + j + k] = fdel(f[i + j + k], 0);
			}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	LL a[maxn], b[maxn], c[maxn], d[maxn];
	cin >> n;
	n = 1 << n;
	For(i, 0, n - 1) cin >> a[i];
	For(i, 0, n - 1) cin >> b[i];
	memcpy(c, a, n * sizeof (LL));
	memcpy(d, b, n * sizeof (LL));
	FWT_or(c, n, 1);
	FWT_or(d, n, 1);
	For(i, 0, n - 1) c[i] = c[i] * d[i] % mod;
	FWT_or(c, n, mod - 1); // -1
	For(i, 0, n - 1) cout << c[i] << " ";
	cout << endl;

	memcpy(c, a, n * sizeof (LL));
	memcpy(d, b, n * sizeof (LL));
	FWT_and(c, n, 1);
	FWT_and(d, n, 1);
	For(i, 0, n - 1) c[i] = c[i] * d[i] % mod;
	FWT_and(c, n, mod - 1); // -1
	For(i, 0, n - 1) cout << c[i] << " ";
	cout << endl;

	memcpy(c, a, n * sizeof (LL));
	memcpy(d, b, n * sizeof (LL));
	FWT_xor(c, n, 1);
	FWT_xor(d, n, 1);
	For(i, 0, n - 1) c[i] = c[i] * d[i] % mod;
	FWT_xor(c, n, (mod + 1) >> 1); // 1/2
	For(i, 0, n - 1) cout << c[i] << " ";
	cout << endl;

	return 0;
}
