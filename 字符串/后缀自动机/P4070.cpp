#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int n;
int a[maxn];

struct SAM{

	struct node{
		map<int, node *> ch;
		node *nex;
		int maxlen;

		node(int len = 0) : nex(NULL), maxlen(len) {}
	} *st, *lst;

	void init(){ 
		st = lst = new node;
	}

	node *extend(int c){
		node *u = new node(lst->maxlen + 1), *v = lst;
		for(; v && !(v->ch[c]); v = v->nex) v->ch[c] = u;
		if(!v) u->nex = st;
		else if(v->ch[c]->maxlen == v->maxlen + 1) u->nex = v->ch[c];
		else{
			node *p = v->ch[c], *pp = new node(v->maxlen + 1);
			pp->ch = p->ch;;
			pp->nex = p->nex;
			p->nex = u->nex = pp;
			for(; v && v->ch[c] == p; v = v->nex) v->ch[c] = pp;
		}
		lst = u;
		return u;
	}
}sam;

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r",stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	LL ans = 0;
	sam.init();
	For(i, 1, n){
		cin >> a[i];
		SAM::node *u = sam.extend(a[i]);
		ans += u->maxlen - u->nex->maxlen;
		printf("%lld\n", ans);
	}
	return 0;
}
