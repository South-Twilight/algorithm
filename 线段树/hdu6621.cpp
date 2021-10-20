#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int maxn = 1e5 + 10;
int n, m, Max;
int a[maxn];
int rt[maxn], tot;
struct tree{
	int cnt;
	int lr, rr;
}tr[maxn * 80];

void update(int &now, int pre, int l, int r, int pos){
	now = ++tot;
	tr[now] = tr[pre];
	++tr[now].cnt;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) update(tr[now].lr, tr[pre].lr, l, mid, pos);
	else update(tr[now].rr, tr[pre].rr, mid + 1, r, pos);
}

int query(int now, int pre, int l, int r, int L, int R){
	if(L <= l && r <= R) return tr[now].cnt - tr[pre].cnt;
	int mid = (l + r) >> 1;
	int sum = 0;
	if(L <= mid) sum += query(tr[now].lr, tr[pre].lr, l, mid, L, R);
	if(R > mid) sum += query(tr[now].rr, tr[pre].rr, mid + 1, r, L, R);
	return sum;
}

bool check(int l, int r, int p, int k, int dis){
	int L = max(1, p - dis), R = min(Max, p + dis);
	int cnt = query(rt[r], rt[l - 1], 1, Max, L, R);
	//cout << dis << " "  << cnt << endl;
	if(cnt >= k) return 1;
	else return 0;
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
	while(_--){
		cin >> n >> m;
		Max = tot = 0;
		For(i, 1, n){
			cin >> a[i];
			Max = max(Max, a[i]);
			rt[i] = 0;
		}
		For(i, 1, n) update(rt[i], rt[i - 1], 1, Max, a[i]);
		int ans = 0;
		For(i, 1, m){
			int l, r, p, k;
			cin >> l >> r >> p >> k;
			l ^= ans; r ^= ans; p ^= ans; k ^= ans;
			int L = 0, R = Max;
			while(L < R){
				int mid = (L + R) >> 1;
				if(check(l, r, p, k, mid)) R = mid;
				else L = mid + 1;
			}
			ans = R;
			cout << R << endl;
		}
	}
	return 0;
}
