#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int maxn = 5e4 + 10;
int n, m;
int a[maxn], b[maxn], cnt, tot;
int ans[maxn];

struct node{
	int l, r, k, tp, id;
}q[maxn << 1], q1[maxn << 1], q2[maxn << 1];
/*
   tp = 0: query(l, r, k) ans[id]
   tp = 1: val = l, pos = r, += k

*/
struct ques{
	int x, y, z, tp;
}qs[maxn];

struct Bit{
	int t[maxn << 1];

	inline int lowbit(int x){ return x & -x; }

	inline int query(int x){
		int res = 0;
		for(; x; x -= lowbit(x)) res += t[x];
		return res;
	}

	inline void update(int x, int y){
		for(; x <= n; x += lowbit(x)) t[x] += y;
	}
}T;

int ask(int x){
	return partition_point(b + 1, b + 1 + cnt, [&](int y){ return y < x; }) - b;
}

void solve(int l, int r, int ql, int qr){
	if(ql > qr || l > r) return ;
	if(l == r){
		For(i, ql, qr) ans[q[i].id] = b[l];
		return ;
	}
	int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
	For(i, ql, qr){
		if(q[i].tp == 0){
			int num = T.query(q[i].r) - T.query(q[i].l - 1);
			if(q[i].k <= num) q1[++cnt1] = q[i];
			else q[i].k -= num, q2[++cnt2] = q[i];
		}
		else{
			if(q[i].l <= mid) T.update(q[i].r, q[i].k), q1[++cnt1] = q[i];
			else q2[++cnt2] = q[i];
		}
	}
	For(i, 1, cnt1) if(q1[i].tp) T.update(q1[i].r, -q1[i].k);
	For(i, 1, cnt1) q[ql + i - 1] = q1[i];
	For(i, 1, cnt2) q[ql + cnt1 + i - 1] = q2[i];
	solve(l, mid, ql, ql + cnt1 - 1);
	solve(mid + 1, r, ql + cnt1, qr);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int _;
	cin >> _;
	while(_--){
		cnt = tot = 0;
		cin >> n >> m;
		For(i, 1, n){
			cin >> a[i];
			b[++cnt] = a[i];
		}
		For(i, 1, m){
			char s[2];
			int x, y, z;
			cin >> s;
			if(s[0] == 'C'){
				cin >> x >> y, qs[i] = ques{x, y, 0, 1};
				b[++cnt] = y;
			}
			else{
				cin >> x >> y >> z, qs[i] = ques{x, y, z, 2};
			}
		}
		sort(b + 1, b + 1 + cnt);
		cnt = unique(b + 1, b + 1 + cnt) - b - 1;
		For(i, 1, n) q[++tot] = node{ask(a[i]), i, 1, 1, 0};
		int id = 0;
		For(i, 1, m){
			int x, y, z;
			if(qs[i].tp == 1){
				x = qs[i].x, y = qs[i].y;
				q[++tot] = node{ask(a[x]), x, -1, 1, 0};
				q[++tot] = node{ask(y), x, 1, 1, 0};
			}
			else{
				x = qs[i].x, y = qs[i].y, z = qs[i].z;
				q[++tot] = node{x, y, z, 0, ++id};
			}
		}
		solve(1, cnt, 1, tot);
		For(i, 1, id) cout << ans[i] << endl;
	}
	return 0;
}
