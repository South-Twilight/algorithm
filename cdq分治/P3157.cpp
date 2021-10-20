#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int n, m;
struct node{
	int v, p, t;

	node(){ v = p = t = 0; }
}a[maxn];
int pos[maxn];
LL f[maxn];

struct Bit{
	const int N = 1e5;
	int t[maxn << 1];
	
	inline int lowbit(int x){ return x & -x; }

	void update(int x, int y){
		while(x <= n){
			t[x] += y;
			 x += lowbit(x);
		}
	}

	LL query(int x){
		LL res = 0;
		while(x){
			res += t[x];
			x -= lowbit(x);
		}
		return res;
	}
}T;

void solve(int l, int r){
	if(l == r) return ;
	int mid = (l + r) >> 1, p, q;
	solve(l, mid);
	solve(mid + 1, r);

	sort(a + l, a + mid + 1, [&](node i, node j){ return i.p > j.p; });
	sort(a + mid + 1, a + r + 1, [&](node i, node j){ return i.p > j.p; });
	p = l, q = mid;
	while(p <= mid){
		while(q < r && a[q + 1].p > a[p].p){
			++q;
			T.update(a[q].v, 1);
		}
		f[a[p].t] += T.query(a[p].v);
		++p;
	}
	while(q > mid) T.update(a[q].v, -1), --q;

	sort(a + l, a + mid + 1, [&](node i, node j){ return i.p < j.p; });
	sort(a + mid + 1, a + r + 1, [&](node i, node j){ return i.p < j.p; });
	p = l, q = mid;
	while(p <= mid){
		while(q < r && a[q + 1].p < a[p].p){
			++q;
			T.update(a[q].v, 1);
		}
		f[a[p].t] += q - mid - T.query(a[p].v);
		++p;
	}
	while(q > mid) T.update(a[q].v, -1), --q;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	For(i, 1, n){
		cin >> a[i].v, a[i].p = i;
		pos[a[i].v] = i;
	}
	For(i, 1, m){
		int x;
		cin >> x;
		a[pos[x]].t = i;
	}
	For(i, 1, n) if(!a[i].t) a[i].t = m + 1;
	sort(a + 1, a + 1 + n, [&](node i, node j){ return i.t < j.t; });
	solve(1, n);
	for(int i = m; i; --i) f[i] += f[i + 1];
	For(i, 1, m) cout<< f[i] << endl;
	return 0;
}
