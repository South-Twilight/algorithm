// problem id: jisuanke 42586
#include <bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int n, k, tot;
int val[maxn];
vector<int> G[maxn];
int dep[maxn], Size[maxn], son[maxn], rt[maxn];
LL ans;
struct node {
	int lr, rr;
	LL sum;
}tr[maxn * 20];

void dfs1(int u, int d) {
	Size[u] = 1;
	dep[u] = d;
	son[u] = 0;
	for(auto v: G[u]) {
		dfs1(v, d + 1);
		Size[u] += Size[v];
		if(!son[u] || Size[v] > Size[son[u]]) son[u] = v;
	}
}

void update(int &u, int l, int r, int p, int v) {
	if(!u) u = ++tot;
	tr[u].sum += v;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(p <= mid) update(tr[u].lr, l, mid, p, v);
	else update(tr[u].rr, mid + 1, r, p, v);
}

int query(int u, int l, int r, int L, int R) {
	if(L <= l && r <= R) return tr[u].sum;
	int mid = (l + r) >> 1;
	int res = 0;
	if(L < mid) res += query(tr[u].lr, l, mid, L, R);
	if(R > mid) res += query(tr[u].rr, mid + 1, r, L, R);
	return res;
}

void add(int u, int cn) {
	update(rt[val[u]], 1, n, dep[u], cn);
	for(auto v: G[u]) add(v, cn);
}

void qry(int u, int d, int va) {
	int dd = 2 * d + k - dep[u];
	dd = min(dd, n);
	int vv = 2 * va - val[u];
	if(dd >= 1 && 0 <= vv && vv <= n) ans += query(rt[vv], 1, n, 1, dd);
	for(auto v: G[u]) qry(v, d, va);
}

void dfs2(int u) {
	for(auto v: G[u]) {
		if(v == son[u]) continue;
		dfs2(v);
		add(v, -1);
	}
	if(son[u]) dfs2(son[u]);
	for(auto v: G[u]) {
		if(v == son[u]) continue;
		qry(v, dep[u], val[u]);
		add(v, 1);
	}
	update(rt[val[u]], 1, n, dep[u], 1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	For(i, 1, n) scanf("%d", &val[i]);
	For(i, 2, n) {
		int x;
		scanf("%d", &x);
		G[x].push_back(i);
	}
	dfs1(1, 1);
	dfs2(1);
	printf("%lld\n", ans * 2ll);
	return 0;
}
