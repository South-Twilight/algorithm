#include<bits/stdc++.h>
#define For(aa,bb,cc) for(int aa=(bb);aa<=(int)(cc);++aa)
#define Rand T*(rand()*2-RAND_MAX)//[-T*RM,T*RM)
using namespace std;
typedef long double LD;
const int maxn=110;
const double eps=1e-14,D=0.97;
int n;
double best,ans;//best ans,now ans
struct Point{
	double x,y,z;

	Point(){ x=y=z=0; }
}p[maxn];

LD calc(LD xx,LD yy,LD zz){//Min dis(p0,p[i])
	LD res=0;
	For(i,1,n)
		res=max(res,sqrt((xx-p[i].x)*(xx-p[i].x)+
				(yy-p[i].y)*(yy-p[i].y)+(zz-p[i].z)*(zz-p[i].z)));
	return res;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	scanf("%d",&n);
	Point ap,p0,p1;
	For(i,1,n){
		scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z);
		ap.x+=p[i].x,ap.y+=p[i].y,ap.z+=p[i].z;
	}
	ap.x/=n,ap.y/=n,ap.z/=n;
	best=ans=calc(ap.x,ap.y,ap.z);
	srand(time(NULL));
	int tim=100;
	while(tim--){
		ans=best,p0=ap;
		for(LD T=1e5;T>eps;T*=D){
			p1.x=p0.x+Rand;
			p1.y=p0.y+Rand;
			p1.z=p0.z+Rand;
			LD res=calc(p1.x,p1.y,p1.z);
			if(best>res) best=res,ap=p1;
			if(ans>res || exp((ans-res)/T)>(LD)rand()/RAND_MAX) ans=res,p0=p1;
		}
	}
	printf("%.8lf\n",best);
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}
