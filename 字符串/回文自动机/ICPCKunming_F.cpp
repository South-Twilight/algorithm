/*
支持修改的PAM
*/
#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int maxn = 1e6 + 10;
typedef long long LL;
const LL mod = 1e9 + 7;
int n, m;
char s[maxn];
int tot, lst;
int trans[maxn][26], fail[maxn], fa[maxn][26], len[maxn];
int de[maxn];
LL sum[maxn], val[maxn], mul[maxn], ans;
//val[i]：以该点结尾的回文子串的贡献

void init(){
	For(i, 0, tot){
		fail[i] = 0;
		memset(trans[i], 0, sizeof trans[i]);
		memset(fa[i], -1, sizeof fa[i]);
	}
	tot = 0;
	fail[0] = fail[1] = 1;
	sum[0] = sum[1] = 0;
	tot = lst = 1;
	len[0] = 0;
	len[1] = -1;
}

int newnode(int L){
	++tot;
	len[tot] = L;
	return tot;
}

int get_pos(int u, int c, int pos){
	int v = u;
	while(s[pos - len[v] - 1] != s[pos]){
		if(fa[v][c] != -1) v = fa[v][c];
		else v = fail[v];
	}
	for(int i = u; i != v; i = fail[i]){
		if(fa[i][c] == -1) fa[i][c] = v;
		else break;
	}
	return v;
}

void extend(int c, int pos){
	int u = lst;
	u = get_pos(u, c, pos);
	if(!trans[u][c]){
		int v = newnode(len[u] + 2), p = fail[u];
		p = get_pos(p, c, pos);
		fail[v] = trans[p][c];
		trans[u][c] = v;
		if(len[v] <= n) sum[v] = 1ll * mul[n - len[v]] * (n - len[v] + 1) % mod;
		else sum[v] = 0;
		sum[v] = (sum[v] + sum[fail[v]]) % mod;
	}
	lst = trans[u][c];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int _;
	cin >> _;
	memset(fa, -1, sizeof fa);
	mul[0] = 1;
	For(i, 1, 1e6) mul[i] = mul[i - 1] * 26 % mod;
	while(_--){
		init();
		cin >> n >> m;
		cin >> (s + 1);
		int L = strlen(s + 1);
		ans = 0;
		For(i, 1, L){
			extend(s[i] - 'a', i);
			de[i] = lst;
			val[i] = sum[lst];
			ans = (ans + val[i]) % mod;
		}
		printf("%lld\n", ans);
		while(m--){
			int x;
			char t[3];
			cin >> x;
			if(x == 1){
				cin >> (t + 1);
				s[++L] = t[1];
				extend(s[L] - 'a', L);
				de[L] = lst;
				val[L] = sum[lst];
				ans = (ans + val[L]) % mod;
				printf("%lld\n", ans);
			}
			else{
				ans = (ans - val[L] + mod) % mod;
				lst = de[--L];
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
