#include<queue>
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

bool spfa(){
	int k,u;
	memset(vis,0,sizeof vis);
	memset(dis,inf,sizeof dis);
	deque<int>q;
	dis[t]=0;
	q.push_back(t);
	while(!q.empty()){
		k=q.front();q.pop_front();vis[k]=0;
		for(int i=be[k];i;i=ne[i]){
			u=to[i];
			if(flow[i^1] && dis[u]>dis[k]-cost[i]){
				dis[u]=dis[k]-cost[i];
				if(!vis[u]){
					vis[u]=1;
					if(!q.empty() && dis[u]<dis[q.front()]) q.push_front(u);
					else q.push_back(u);
				}
			}
		}
	}
	return dis[s]<inf;
}
 
int dfs(int node,int f){
	vis[node]=1;
	if(node==t) return allcost+=-dis[s]*f,allflow+=f,f;
	if(!f) return 0;
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

void minflow(){
	allcost=allflow=0;
	while(spfa()){
		memset(vis,0,sizeof vis);
		memcpy(cur,be,sizeof be);
		dfs(s,inf);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
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
