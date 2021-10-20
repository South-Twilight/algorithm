#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int maxn = 1e6 + 10;
int n;
int tr[maxn][26], fail[maxn], tot;
int pos[maxn], cnt[maxn];

void insert(char *s, int id){
	int len = strlen(s + 1), u = 0;
	For(i, 1, len){
		int j = s[i] - 'a';
		if(!tr[u][j]) tr[u][j] = ++tot;
		u = tr[u][j];
	}
	pos[u] = id;
}

void getfail(){
	queue<int> q;
	For(i, 0, 25) if(tr[0][i]) q.push(tr[0][i]), fail[tr[0][i]] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		For(i, 0, 25){
			if(tr[u][i]){
				fail[tr[u][i]] = tr[fail[u]][i];
				q.push(tr[u][i]);
			}
			else tr[u][i] = tr[fail[u]][i];
			//这里采用了构建trie图得到fail的方式，真正用trie树得到fail，就需要这里不能赋值，用循环不断往回跳，直到存在儿子或者为根节点
		}
	}
}

void Clear(){
	For(i, 0, tot){
		For(j, 0, 25) tr[i][j] = 0;
		fail[i] = pos[i] = 0;
	}
	For(i, 1, n) cnt[i]= 0;
	tot = 0;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	while(~scanf("%d", &n) && n){
		char s[maxn], t[160][100];
		For(i, 1, n){
			scanf("%s", t[i] + 1);
			insert(t[i], i);
		}
		getfail();
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		int u = 0;
		For(i, 1, len){
			u = tr[u][s[i] - 'a'];
			for(int j = u; j; j = fail[j]) ++cnt[pos[j]];
		}
		int Max = 0;
		For(i, 1, n) if(cnt[i] > Max) Max = cnt[i];
		printf("%d\n", Max);
		For(i, 1, n) if(cnt[i] == Max) printf("%s\n", t[i] + 1);
		Clear();
	}
	return 0;
}
