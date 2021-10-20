#include<bits/stdc++.h>
#define For(aa,bb,cc) for(int aa=(bb);aa<=(int)(cc);++aa)
using namespace std;
typedef long long LL;
const int maxn=3e3+10;
const LL mod=998244353;
LL x[maxn],y[maxn],w[maxn];

LL qpow(LL a,int b){
	LL res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	int n,cnt=0;
	scanf("%d",&n);
	while(n--){
		int tp,X;
		scanf("%d",&tp);
		if(tp==1){
			++cnt;
			scanf("%lld%lld",&x[cnt],&y[cnt]);
			For(i,1,cnt-1) w[i]=w[i]*qpow(x[i]-x[cnt],mod-2)%mod;
			w[cnt]=y[cnt];
			For(i,1,cnt-1) w[cnt]=w[cnt]*qpow(x[cnt]-x[i],mod-2)%mod;
		}
		else{
			scanf("%d",&X);
			bool flag=0;
			For(i,1,cnt){
				if(X==x[i]){
					flag=1;
					printf("%lld\n",y[i]);
					break;
				}
			}
			if(flag) continue;
			LL ans=1;
			For(i,1,cnt) ans=ans*(X-x[i])%mod;
			LL sum=0;
			For(i,1,cnt) sum=(sum+w[i]*qpow(X-x[i],mod-2)%mod)%mod;
			printf("%lld\n",(ans*sum%mod+mod)%mod);
		}
	}
	return 0;
}
