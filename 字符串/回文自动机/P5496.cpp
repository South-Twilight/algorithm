#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
#define Forr(aa, bb, cc) for(int aa = (bb); aa >= (int)(cc); --aa)
using namespace std;
const int maxn = 5e5 + 10;
char s[maxn];

struct PAM{
	int maxlen[maxn], trans[maxn][26], fail[maxn];
	int num[maxn], Size[maxn], L[maxn];
	int tot, lst;
	//num[u]：以u代表的回文串结尾的回文后缀的个数
	//Size[u]：u代表的回文串的数量，进行从叶子到根的累加后就是整个串出现的次数（每次都只加了最长的）
	//L[pos]：以pos结尾的回文串长度

	void init(){
		maxlen[0] = 0; maxlen[1] = -1;
		fail[0] = 1; fail[1] = 0;
		tot = 1; lst = 0;
		memset(trans[0], 0, sizeof trans[0]);
		memset(trans[1], 0, sizeof trans[1]);
	}

	int newnode(int len){
		int now = ++tot;
		memset(trans[now], 0, sizeof trans[now]);
		maxlen[now] = len;
		return tot;
	}

	void extend(int c, int pos){
		int u = lst;
		while(s[pos - maxlen[u] - 1] != s[pos]) u = fail[u];//find self
		if(!trans[u][c]){
			int now = newnode(maxlen[u] + 2);
			int v = fail[u];
			while(s[pos - maxlen[v] - 1] != s[pos]) v = fail[v];//find second self
			fail[now] = trans[v][c];
			trans[u][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		lst = trans[u][c];
		L[pos] = maxlen[lst];
		++Size[lst];
	}

	void calc(){
		Forr(i, tot, 0) Size[fail[i]] += Size[i];
	}

	int query(){
		return num[lst];
	}

}pam;

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	pam.init();
	cin >> (s + 1);
	int len = strlen(s + 1), pre;
	For(i, 1, len){
		int c = s[i] - 'a';
		if(i > 1) c = (c + pre) % 26;
		s[i] = c + 'a';
		pam.extend(c , i);
		printf("%d ", pre = pam.query());
	}
	return 0;
}
