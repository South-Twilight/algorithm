#include<queue>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mem(a,b) memset(a,b,sizeof(a))
#define  For(i,a,b) for(int i=a,i##E=b;i<=i##E;++i)
#define rFor(i,a,b) for(int i=a,i##E=b;i>=i##E;--i)
using namespace std;
typedef long long LL;
const int N=5010;
const int M=100010;
const int inf=0x3f3f3f3f;
template<typename T>inline T chkmax(T A,T B){return A>B?A:B;}
template<typename T>inline T chkmin(T A,T B){return A<B?A:B;}
template<typename T>inline void read(T &x)
{
    x=0;int _f(0);char ch=getchar();
    while(!isdigit(ch))_f|=(ch=='-'),ch=getchar();
    while( isdigit(ch))x=x*10+ch-'0',ch=getchar();
    x=_f?-x:x;
}
inline void file()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
}
int n,m,s,t;
int bgn[N],nxt[M],to[M],c[M],w[M],E=1;
inline void add_edge(int u,int v,int f,int ew){nxt[++E]=bgn[u],bgn[u]=E,to[E]=v,c[E]=f,w[E]=ew;}
struct Netflow
{
    int cur[N],dis[N],vis[N],q[N],n,S,T;
    inline void init(int s,int t,int cnt){S=s,T=t,n=cnt+1;}
    inline bool bfs()
    {
        memset(vis,0,n*sizeof(int));
        memset(dis,inf,n*sizeof(int));
        deque<int>q;q.push_back(S);
        vis[S]=1;dis[S]=0;
        while(!q.empty())
        {
            int u=q.front();q.pop_front();vis[u]=0;
            for(int v,i=bgn[u];i;i=nxt[i])
                if(c[i]&&dis[v=to[i]]>dis[u]+w[i])
                {
                    dis[v]=dis[u]+w[i];
                    if(!vis[v])
                    {
                        vis[v]=1;
                        if(q.empty()||dis[v]<dis[q.front()])
                             q.push_front(v);
                        else q.push_back(v);
                    }
                }
        }
        return dis[T]!=inf;
    }
    int dfs(int u,int flow)
    {
        if(u==T)return flow;
        int ret=flow;vis[u]=1;
        for(int v,&i=cur[u];i;i=nxt[i])
        if(c[i]&&!vis[v=to[i]]&&dis[v]==dis[u]+w[i])
        {
            int f=dfs(v,chkmin(c[i],ret));
            c[i]-=f,c[i^1]+=f,ret-=f;
            if(!ret)return flow;
        }vis[u]=0;
        return flow-ret;
    }
    inline void Maxflow()
    {
        int ans1=0,ans2=0;
        while(bfs())
        {
            memset(vis,0,n*sizeof(int));
            memcpy(cur,bgn,n*sizeof(int));
            int x=dfs(S,inf);
            ans1+=x,ans2+=x*dis[T];
        }
        printf("%d %d\n",ans1,ans2);
    }
}ZKW;
int main()
{
    file();
    int u,v,x,y;
    read(n),read(m),read(s),read(t);
    For(i,1,m)
    {
        read(u),read(v),read(x),read(y);
        add_edge(u,v,x,y),add_edge(v,u,0,-y);
    }
    ZKW.init(s,t,n);
    ZKW.Maxflow();
    return 0;
}
