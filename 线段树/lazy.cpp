#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const LL mod = 1e9 + 7;
const int maxn = 1e5 + 10;
int n, m;
LL sum[maxn << 4][3], tag[maxn << 4][3], mul[maxn << 4], ch[maxn << 4];

#define lr (node<<1)
#define rr (node<<1|1)
#define mid ((l+r)>>1)

void create(int node,int l,int r){
	mul[node] = 1;
	if(l == r) return ;
	create(lr, l, mid);
	create(rr, mid + 1, r);
}

inline void push_down(int node,int l,int r){
	if(mul[node] != 1){
		sum[lr][0] = sum[lr][0] * mul[node] % mod;
		sum[lr][1] = sum[lr][1] * mul[node] % mod;
		sum[lr][2] = sum[lr][2] * mul[node] % mod;
		
		sum[rr][0] = sum[rr][0] * mul[node] % mod;
		sum[rr][1] = sum[rr][1] * mul[node] % mod;
		sum[rr][2] = sum[rr][2] * mul[node] % mod;
		
		tag[node][0] = tag[node][0] * mul[node] % mod;
		tag[node][1] = tag[node][1] * mul[node] % mod;
		tag[node][2] = tag[node][2] * mul[node] % mod;
		
		mul[lr] = mul[lr] * mul[node] % mod;
		mul[rr] = mul[rr] * mul[node] % mod;
		mul[node] = 1;
	}	
	if(tag[node]){
		sum[lr][0] = (sum[lr][0] + 1ll * (mid - l + 1) * tag[node][0] % mod) % mod;
		sum[lr][1] = (sum[lr][1] + 1ll * (mid - l + 1) * tag[node][1] % mod) % mod;
		sum[lr][2] = (sum[lr][2] + 1ll * (mid - l + 1) * tag[node][2] % mod) % mod;
		
		sum[rr][0] = (sum[rr][0] + 1ll * (r - mid) * tag[node][0] % mod) % mod;
		sum[rr][1] = (sum[rr][1] + 1ll * (r - mid) * tag[node][1] % mod) % mod;
		sum[rr][2] = (sum[rr][2] + 1ll * (r - mid) * tag[node][2] % mod) % mod;
			
		tag[lr][0] = (tag[node][0] + tag[lr][0]) % mod;
		tag[lr][1] = (tag[node][1] + tag[lr][1]) % mod;
		tag[lr][2] = (tag[node][2] + tag[lr][2]) % mod;
		
		tag[rr][0] = (tag[node][0] + tag[rr][0]) % mod;
		tag[rr][1] = (tag[node][1] + tag[rr][1]) % mod;
		tag[rr][2] = (tag[node][2] + tag[rr][2]) % mod;
		
		tag[node][0] = tag[node][1] = tag[node][2] = 0;
	}
}

inline void push_up(int node){
	sum[node][0] = (sum[lr][0] + sum[rr][0]) % mod;
	sum[node][1] = (sum[lr][1] + sum[rr][1]) % mod;
	sum[node][2] = (sum[lr][2] + sum[rr][2]) % mod;
}

void add(int node,int l,int r,int L,int R,int* a){
	push_down(node, l, r);
	if(L == l && r == R){
		sum[node][0] += 1ll * (r - l + 1) * a[0] % mod;
		sum[node][1] += 1ll * (r - l + 1) * a[1] % mod;
		sum[node][2] += 1ll * (r - l + 1) * a[2] % mod;
		
		sum[node][0] %= mod;
		sum[node][1] %= mod;
		sum[node][2] %= mod;
		
		tag[node][0] = (tag[node][0] + a[0]) % mod;
		tag[node][1] = (tag[node][1] + a[1]) % mod;
		tag[node][2] = (tag[node][2] + a[2]) % mod;
		return ;
	}
	if(R <= mid) add(lr, l, mid, L, R, a);
	else if(L > mid) add(rr, mid + 1, r, L, R, a);
	else{
		add(lr, l, mid, L, mid, a);
		add(rr, mid + 1, r, mid + 1, R, a);
	}
	push_up(node);
}

void Mul(int node,int l,int r,int L,int R,int k){
	push_down(node, l, r);
	if(L == l && r == R){
		sum[node][0] = sum[node][0] * k % mod;
		sum[node][1] = sum[node][1] * k % mod;
		sum[node][2] = sum[node][2] * k % mod;
		
		mul[node] = mul[node] * k %mod;
		return ;
	}
	if(R <= mid) Mul(lr, l, mid, L, R, k);
	else if(L > mid) Mul(rr, mid + 1, r, L, R, k);
	else{
		Mul(lr, l, mid, L, mid, k);
		Mul(rr, mid + 1, r, mid + 1, R, k);
	}
	push_up(node);
}

LL query_x(int node,int l,int r,int L,int R){
	push_down(node, l, r);
	if(L == l && r == R) return sum[node][0];
	LL res = 0;
	if(R <= mid) res = query_x(lr, l, mid, L, R);
	else if(L > mid) res = query_x(rr, mid + 1, r, L, R);
	else{
		res += query_x(lr, l, mid, L, mid);
		res += query_x(rr, mid + 1, r, mid + 1, R);
	}
	push_up(node);
	return res % mod;
}

LL query_y(int node,int l,int r,int L,int R){
	push_down(node, l, r);
	if(L == l && r == R) return sum[node][1];
	LL res = 0;
	if(R <= mid) res = query_y(lr, l, mid, L, R);
	else if(L > mid) res = query_y(rr, mid + 1, r, L, R);
	else{
		res += query_y(lr, l, mid, L, mid);
		res += query_y(rr, mid + 1, r, mid + 1, R);
	}
	push_up(node);
	return res % mod;
}

LL query_z(int node,int l,int r,int L,int R){
	push_down(node, l, r);
	if(L == l && r == R) return sum[node][2];
	LL res = 0;
	if(R <= mid) res = query_z(lr, l, mid, L, R);
	else if(L > mid) res = query_z(rr, mid + 1, r, L, R);
	else{
		res += query_z(lr, l, mid, L, mid);
		res += query_z(rr, mid + 1, r, mid + 1, R);
	}
	push_up(node);
	return res % mod;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif	
	scanf("%d%d", &n, &m);
	create(1, 1, n);
	int a[3];
	int tp, l, r, k;
	For(i, 1, m){
		scanf("%d%d%d", &tp, &l ,&r);
		if(tp == 1){
			scanf("%d%d%d", &a[0], &a[1], &a[2]);
			add(1, 1, n, l, r, a);
		//	For(j, 1, n) printf("add %d %lld\n",j,query_y(1, 1, n, j,j));
		}
		else if(tp == 2){
			scanf("%d", &k);
			Mul(1, 1, n, l, r, k);
			//For(j, 1, n) printf("mul %d %lld\n",j, query_y(1, 1, n, j,j));
		}
		else if(tp == 3){
		}
		else{
			LL x = query_x(1, 1, n, l, r);
			LL y = query_y(1, 1, n, l, r);
			LL z = query_z(1, 1, n, l, r);
			//For(j, 1, n) printf("%d %lld\n", j, query_y(1, 1, n, j,j));
			printf("%lld\n", (x * x %mod + y * y %mod + z * z % mod) % mod);
		}
	}
	return 0;
}