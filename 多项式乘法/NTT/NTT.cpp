#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const int maxn = 4e6 + 10;
const LL mod = 998244353, g = 3, invg = 332748118;
int n, m;
LL a[maxn], b[maxn];
int rev[maxn];

LL qpow(LL x, LL y){
	LL res = 1;
	while(y){
		if(y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

void Init(int len) {
	for(int i = 1; i < len; ++i) {
		rev[i] = rev[i >> 1] >> 1;
		if(i & 1) rev[i] |= len >> 1;
	}
}

void NTT(LL a[], int len, int tp){
	For(i, 0, len - 1) if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int h = 2; h <= len; h <<= 1){
		LL gn = qpow(tp == 1 ? g : invg, (mod - 1) / (LL)h);
		for(int j = 0; j < len; j += h){
			LL gk = 1;
			for(int k = j; k < j + h / 2; ++k){
				LL e = a[k], o = gk * a[k + h / 2] %  mod;
				a[k] = (e + o) % mod, a[k + h / 2] = ((e - o) % mod + mod) % mod;
				gk = gk * gn % mod;
			}
		}
	}
	if(tp == -1){
		LL inv = qpow(len, mod - 2);
		For(i, 0, len - 1) a[i] = a[i] * inv % mod;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	For(i, 0, n) cin >> a[i];
	For(i, 0, m) cin >> b[i];
	int n0 = 1;
	while(n0 <= n + m) n0 <<= 1;
	Init(n0);
	NTT(a, n0, 1);
	NTT(b, n0, 1);
	For(i, 0, n0) a[i] = a[i] * b[i];
	NTT(a, n0, -1);
	For(i, 0, n + m) cout << a[i] << " ";
	cout << endl;
	return 0;
}
