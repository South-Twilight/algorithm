#include<cstdio>
#include<cstring>
#include<iostream>
#define For(aa,bb,cc) for(int aa=(bb);aa<=(int)(cc);++aa)
using namespace std;
const int maxn=1e3+10,maxm=3e4+10,inf=0x3f3f3f3f;
int n,m,s,t,ans;
int be[maxn],ne[maxm<<1],to[maxm<<1],flow[maxm<<1],cost[maxm<<1],e;
int cur[maxn],dis[maxn],vis[maxn];

template<typename T>
void read(T &x){
	x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
}

inline void add_edge(int x,int y,int f,int c){
	to[++e]=y,ne[e]=be[x],be[x]=e,flow[e]=f,cost[e]=c;
	to[++e]=x,ne[e]=be[y],be[y]=e,flow[e]=0,cost[e]=-c;
}

int dfs(int node,int f){
	vis[node]=1;
	if(node==t) return ans+=-dis[s]*f,f;
	for(int &i=cur[node];i;i=ne[i]){
		int u=to[i];
		if(!vis[u] && flow[i] && dis[u]==dis[node]+cost[i]){
			int tmp=dfs(u,min(f,flow[i]));
			if(tmp){
				flow[i]-=tmp;
				flow[i^1]+=tmp;
				return tmp;
			}
		}
	}
	return 0;
}

bool update(){
	if(vis[t]) return 1;
	int tmp=inf;
	For(k,1,n+3){
		if(vis[k]){
			for(int i=be[k];i;i=ne[i]){
				int u=to[i];
				if(flow[i] && !vis[u])
					tmp=min(tmp,dis[k]+cost[i]-dis[u]);
			}
		}
	}
	if(tmp==inf) return 0;
	For(i,1,n+3)
		if(vis[i]) 
			dis[i]-=tmp;
	return 1;
}

void minflow(){
	do{
		memset(vis,0,sizeof vis);
		memcpy(cur,be,sizeof be);
		dfs(s,inf);
	}while(update());
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	int x,y,z;e=1;
	read(n),read(m);
	s=n+2,t=n+3;
	add_edge(s,1,inf,0);add_edge(n+1,t,inf,0);
	For(i,1,n) read(x),add_edge(i,i+1,inf-x,0);
	For(i,1,m){
		read(x),read(y),read(z);
		add_edge(x,y+1,inf,z);
	}
	minflow();
	printf("%d\n",ans);
	return 0;
}
