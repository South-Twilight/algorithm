#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
using namespace std;
const int maxn = 2e6 + 10;
int n;
char s[maxn * 10];
int tr[maxn][26], fail[maxn], pos[maxn], tot;
int deg[maxn], f[maxn];
vector<int> G[maxn];

void insert(string st, int id){
	int u = 0;
	For(i, 0, st.length() - 1){
		int j = st[i] - 'a';
		if(!tr[u][j]) tr[u][j] = ++tot;
		u = tr[u][j];
	}
	pos[id] = u;
}

void get_fail(){
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
		}
	}
}

void Topo(){
	queue<int> q;
	For(i, 1, tot) if(!deg[i]) q.push(i);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		For(i, 0, G[u].size() - 1){
			int v = G[u][i];
			f[v] += f[u];
			--deg[v];
			if(!deg[v]) q.push(v);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	cin >> n;
	string t;
	For(i, 1, n) cin >> t, insert(t, i);
	get_fail();
	//For(i, 1, tot) cout<<i<<" "<<fail[i]<<endl;
	cin >> (s + 1);
	int len = strlen(s + 1);
	int u = 0;
	For(i, 1, len){
		u = tr[u][s[i] - 'a'];
		++f[u];
	}
	For(i, 1, tot){
		if(fail[i]) G[i].push_back(fail[i]), ++deg[fail[i]];
		//cout<<fail[i]<<" "<<i<<endl;
	}
	Topo();
	For(i, 1, n) printf("%d\n", f[pos[i]]);
	return 0;
}
