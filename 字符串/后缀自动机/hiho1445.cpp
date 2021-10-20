#include<cstdio>
#include<iostream>
#include<cstring>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
#define Forr(aa, bb, cc) for(int aa = (bb); aa >= (int)(cc); --aa)
#define Cpy(aa, bb) memcpy(aa, bb, sizeof bb)
using namespace std;
const int maxn = 1e6 + 10;
int len;
char s[maxn];
int val[maxn << 1];
int num[maxn << 1], id[maxn << 1], cnt[maxn << 1], ans[maxn];

//sam

int maxlen[maxn << 1];
int trans[maxn << 1][26];
int link[maxn << 1];
int lst, tot;

void init(){
	lst = tot = 1;
}

void extend(int c){
	int now = ++tot, p;
	val[now] = 1;
	maxlen[now] = maxlen[lst] + 1;
	for(p = lst; p && !trans[p][c]; p = link[p]) trans[p][c] = now;
	if(!p) link[now] = 1;
	else{
		int q = trans[p][c];
		if(maxlen[q] == maxlen[p] + 1) link[now] = q;
		else{
			int sp = ++tot;
			maxlen[sp] = maxlen[p] + 1;
			Cpy(trans[sp], trans[q]);
			link[sp] = link[q];
			for(; p && trans[p][c] == q; p = link[p]) trans[p][c] = sp;
			link[q] = link[now] = sp;
		}
	}
	lst = now;
}

void topsort(){
	For(i, 1, tot) ++num[maxlen[i]];
	For(i, 1, len) num[i] += num[i - 1];
	For(i, 1, tot) id[num[maxlen[i]]--] = i;
	Forr(i, tot, 1) val[link[id[i]]] += val[id[i]];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	init();
	cin >> (s + 1);
	len = strlen(s + 1);
	For(i, 1, len) extend(s[i] - 'a');
	topsort();
	For(i, 1, tot) ans[maxlen[i]] = max(ans[maxlen[i]], val[i]);
	Forr(i, len - 1, 1) ans[i] = max(ans[i], ans[i + 1]);
	For(i, 1, len) printf("%d\n", ans[i]);
	return 0;
}
