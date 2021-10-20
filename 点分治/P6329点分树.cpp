#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int maxn = 2e5 + 10;
const int inf = 0x3f3f3f3f;
typedef long long LL;
int n, m, rt, Min;
int be[maxn], ne[maxn << 1], to[maxn << 1], e;
int val[maxn];
int Size[maxn], Maxdep[maxn], tot;
int lg[maxn], st[maxn][20], dep[maxn], dfn[maxn], pos[maxn], cnt;
vector<int> t[maxn], tf[maxn];
int fa[maxn];
bool vis[maxn];

inline void add_edge(int x, int y){
	to[++e] = y, ne[e] = be[x], be[x] = e;
	to[++e] = x, ne[e] = be[y], be[y] = e;
}

void get_root(int u, int f){
	Size[u] = 1;
	int res = 0;
	for(int i = be[u]; i; i = ne[i]){
		int v = to[i];
		if(v == f || vis[v]) continue;
		get_root(v, u);
		Size[u] += Size[v];
		res = max(res, Size[v]);
	}
	if(res < tot - Size[u]) res = tot - Size[u];
	if(res < Min) Min = res, rt = u;
}

void get_st(){
	For(i, 1, cnt) lg[i] = 31 - __builtin_clz(i);
	For(j, 1, 17) For(i, 1, cnt){
		if(i + (1 << j) <= cnt){
			int x= st[i][j - 1], y = st[i + (1 << (j - 1))][j - 1];
			st[i][j] = dep[x] > dep[y] ? y : x;
		}
	}
}

void dfs(int u, int f){
	dep[u] = dep[f] + 1;
	st[++cnt][0] = u;
	dfn[u] = cnt;
	for(int i = be[u]; i; i = ne[i]){
		int v = to[i];
		if(v == f) continue;
		dfs(v, u);
		st[++cnt][0] = u;
	}
}

int DFS(int u, int f, int d){
	int dis = d;
	Size[u] = 1;
	for(int i = be[u]; i; i = ne[i]){
		int v = to[i];
		if(v == f || vis[v]) continue;
		dis = max(dis, DFS(v, u, d + 1));
		Size[u] += Size[v];
	}
	return dis;
}

void build(int u, int f){
	Maxdep[u] = DFS(u, 0, 1);
	vis[u] = 1;
	fa[u] = f;
	t[u].resize(Maxdep[u] + 1);
	for(int i = be[u]; i; i = ne[i]){
		int v = to[i];
		if(vis[v]) continue;
		rt = 0, Min = inf;
		tot = Size[v];
		get_root(v, u);
		tf[rt].resize(Maxdep[u] + 1);
		build(rt, u);
	}
}

int get_lca(int x, int y){
	if(dfn[x] > dfn[y]) swap(x, y);
	int d = lg[dfn[y] - dfn[x] + 1];
	int u = st[dfn[x]][d], v = st[dfn[y] - (1 << d) + 1][d];
	if(dep[u] > dep[v]) return v;
	return u;
}

int get_dis(int x, int y){
	return dep[x] + dep[y] - 2 * dep[get_lca(x, y)];
}

inline int lowbit(int x){
	return x & (-x);
}

void update(int x, int y, int z){
	while(y <= Maxdep[x]) t[x][y] += z, y += lowbit(y);
}

void update1(int x, int y, int z){
	while(y <= Maxdep[fa[x]]) tf[x][y] += z, y += lowbit(y);
}

int query(int x, int y){
	int res = 0;
	y = min(y, Maxdep[x]);
	while(y) res += t[x][y], y -= lowbit(y);
	return res;
}

int query1(int x, int y){
	int res = 0;
	y = min(y, Maxdep[fa[x]]);
	while(y) res += tf[x][y], y -= lowbit(y);
	return res;
}

void modify(int x, int y){
	update(x, 1, y);
	for(int i = x; fa[i]; i = fa[i]){
		update(fa[i], get_dis(x, fa[i]) + 1, y);
		update1(i, get_dis(x, fa[i]) + 1, y);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	For(i, 1, n) cin >> val[i];
	For(i, 1, n - 1){
		int x, y;
		cin >> x >> y;
		add_edge(x, y);
	}
	dfs(1, 0);
	get_st();
	tot = n; Min = inf;
	get_root(1, 0);
	get_root(rt, 0);
	build(rt, 0);
	For(i, 1, n) modify(i, val[i]);
	int ans = 0;
	while(m--){
		int tp, x, y;
		cin >> tp >> x >> y;
		x ^= ans, y ^= ans;
		if(tp){
			modify(x, y - val[x]);
			val[x] = y;
		}
		else{
			ans = query(x, y + 1);
			for(int i = x; fa[i]; i = fa[i]){
				int d = get_dis(fa[i], x);
				if(d <= y)
					ans += query(fa[i], y - d + 1) - query1(i, y - d + 1);
			}
			cout << ans << endl;
		}
	}
	return 0;
}
