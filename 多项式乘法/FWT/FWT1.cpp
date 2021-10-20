#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 2e3 + 10;
int n, m, inv2;
int val[maxn], ans[maxn];
int be[maxn], ne[maxn << 1], to[maxn << 1], e;
int dp[maxn][maxn], f[maxn];

inline void add_edge(int x, int y){
	to[++e] = y, ne[e] = be[x], be[x] = e;
	to[++e] = x, ne[e] = be[y], be[y] = e;
}

int qpow(int x, int y){
	int res = 1;
	while(y){
		if(y & 1) res = 1ll * res * x %mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return res;
}

void FWT(int *a, int n, int tp){
	for(int i = 2; i <= n; i <<= 1){
		for(int p = i >> 1, j = 0; j < n; j += i){
			for(int k = j; k < j + p; ++k){//half
				int x = a[k], y = a[k + p];
				a[k] = (x + y) % mod;
				a[k + p] = (x - y + mod) % mod;
				if(tp == - 1){
					a[k] = 1ll * a[k] * inv2 % mod;
					a[k + p] = 1ll * a[k + p] * inv2 % mod;
				}
			}
		}
	}
}

void solve(int *a, int *b, int n){
	FWT(a, n, 1);//FWT 
	FWT(b, n, 1);
	For(i, 0, n - 1) a[i] = 1ll * a[i] * b[i] % mod;
	FWT(a, n, -1);
}

void dfs(int u, int fa){
	dp[u][val[u]] = 1;
	for(int i = be[u]; i; i = ne[i]){
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		For(j, 0, m - 1) f[j] = dp[u][j];
		solve(f, dp[v], m);
		For(j, 0, m - 1) dp[u][j] = (dp[u][j] + f[j]) % mod;
	}
	For(i, 0, m - 1) ans[i] = (ans[i] + dp[u][i]) %mod;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int _, x, y;
	scanf("%d", &_);
	inv2 = qpow(2, mod - 2);
	while(_--){
		memset(dp, 0, sizeof dp);
		memset(ans, 0, sizeof ans);
		memset(be, 0, sizeof be);
		e = 0;
		scanf("%d%d", &n, &m);
		For(i, 1, n) scanf("%d", &val[i]);
		For(i, 1, n - 1) scanf("%d%d", &x, &y), add_edge(x, y);
		dfs(1, 0);
		For(i, 0, m - 1) printf("%d%c", ans[i], i == m - 1 ? '\n' : ' ');
	}
	return 0;
}
