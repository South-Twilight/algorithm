#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
#define Pair pair<LL, int> 
#define mk(x, y) make_pair(x, y)
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int n, m, s;
int be[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
LL dis[maxn];
priority_queue<Pair, vector<Pair >, greater<Pair > >q;

inline void add_edge(int x, int y, int z){
	to[++e] = y, ne[e] = be[x], be[x] = e, w[e] = z;;
}

void Dijkstra(){
	For(i, 1, n) dis[i] = -1;
	dis[s] = 0;
	q.push(mk(dis[s], s));
	while(!q.empty()){
		Pair res = q.top();
		q.pop();
		LL d = res.first;
		int u = res.second;
		if(d > dis[u]) continue;
		for(int i = be[u]; i; i = ne[i]){
			int v = to[i];
			if(dis[v] == -1 || dis[v] > d + w[i]){
				dis[v] = d + w[i];
				q.push(mk(dis[v], v));
			}
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
	cin >> n >> m >> s;
	int x, y, z;
	For(i, 1, m) cin >> x >> y >> z, add_edge(x, y, z);
	Dijkstra();
	For(i, 1, n) printf("%lld ", dis[i]);
	return 0;
}
