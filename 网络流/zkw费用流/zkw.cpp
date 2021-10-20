#include<cstdio>
#include<cstring>
#include<iostream>
#define For(aa,bb,cc) for(int aa=(bb);aa<=(int)(cc);++aa)
using namespace std;
const int maxn=5e3+10,maxm=5e5+10,inf=0x3f3f3f3f;
int n,m,s,t,allcost,allflow;
int be[maxn],ne[maxm],to[maxm],flow[maxm],cost[maxm],cur[maxn],e;
int dis[maxn],vis[maxn];

template<class T>
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
	if(node==t) return allcost+=-dis[s]*f,allflow+=f,f;
	int sum=0;
	for(int &i=cur[node];i;i=ne[i]){
		int u=to[i];
		if(!vis[u] && flow[i] && dis[u]==dis[node]+cost[i]){
			int tmp=dfs(u,min(flow[i],f));
			if(tmp){
				flow[i]-=tmp;
				flow[i^1]+=tmp;
				f-=tmp;
				sum+=tmp;
			}
			if(!f) return sum;
		}
	}
	return sum;
}

bool update(){
	if(vis[t]) return 1;
	int tmp=inf;
	For(k,1,n){
		if(vis[k]){
			for(int i=be[k];i;i=ne[i]){
				int u=to[i];
				if(flow[i] && !vis[u])
					tmp=min(tmp,dis[k]-dis[u]+cost[i]);
			}
		}
	}
	if(tmp==inf) return 0;
	For(i,1,n) 
		if(vis[i]) 
			dis[i]-=tmp;
	return 1;
}

void minflow(){
	allcost=allflow=0;
	do{
		memset(vis,0,sizeof vis);
		memcpy(cur,be,sizeof be);
		dfs(s,inf);
	}while(update());
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
#endif
	int x,y,z,l;e=1;
	read(n),read(m),read(s),read(t);
	For(i,1,m){
		read(x),read(y),read(z),read(l);
		add_edge(x,y,z,l);
	}
	minflow();
	printf("%d %d\n",allflow,allcost);
	return 0;
}
