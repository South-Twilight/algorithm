#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const int maxn = 50, N = 1e5;
LL num[maxn];
map<LL, int> P;

LL gcd(LL x, LL y){
	return y ? gcd(y, x % y) : x;
}

LL qmul(LL x, LL y, LL z){
	LL res = 0;
	while(y){
		if(y & 1) res = (res + x) % z;
		x = (x + x) % z;
		y >>= 1;
	}
	return res;
}

LL qpow(LL x, LL y, LL z){
	LL res = 1;
	while(y){
		if(y & 1) res = qmul(res, x, z);
		x = qmul(x, x, z);
		y >>= 1;
	}
	return res;
}

LL pollard_rho(LL x, int c){
	LL i = 1, y = rand() % (x - 1) + 1, z = y, k = 2;
	while(1){
		++i;
		y = (qmul(y, y, x) + c) % x;
		LL p = gcd((z - y + x) % x, x);
		if(p != 1 && p != x) return p;
		if(z == y) return x;
		if(i == k){
			z = y;
			k <<= 1;
		}
	}
}

bool miller_rabin(LL x){
	if(x == 2) return 1;
	int tot = 0;
	LL y = x - 1;
	while(!(y & 1)){
		++tot;
		y >>= 1;
	}
	For(i, 1, 20){
		LL z = rand() % (x - 2) + 2;
		num[0] = qpow(z, y, x);
		For(j, 1, tot){
			num[j] = qmul(num[j - 1], num[j - 1], x);
			if(num[j] == 1 && num[j - 1] != 1 && num[j - 1] != x - 1) return 0;
		}
		if(num[tot] != 1) return 0;
	}
	return 1;
}

void find(LL x, int c){
	if(x == 1) return ;
	if(miller_rabin(x)){
		if(!P.count(x)) P[x] = 1;
		else P[x] = P[x] + 1;
		return ;
	}
	LL p = x, k = c;
	while(p >= x) p = pollard_rho(p, c--);
	find(p, k);
	find(x / p, k);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	LL n;
	scanf("%lld", &n);
	LL sum = 1;
	P.clear();
	memset(num, 0, sizeof num);
	find(n, 120);
	map<LL, int>::iterator it;
	for(it = P.begin(); it != P.end(); ++it){
		pair<LL, int> tmp = *it;
		LL x = tmp.first, y = tmp.second;
		For(j, 1, y) n /= x;
		sum *= (y + 1);
	}
	printf("%lld\n", sum);
	return 0;
}
