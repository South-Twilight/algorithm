#include<bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
#define Forr(aa, bb, cc) for(int aa = (bb); aa >= (int)(cc); --aa)
using namespace std;
const int maxn = 2e5 + 10;
int n;

struct Vector2{
	double x, y;
	
	Vector2(): x(0), y(0){}
	Vector2(double xx, double yy): x(xx), y(yy){}

	Vector2 operator +(Vector2 xx){ return (Vector2){xx.x + x, xx.y + y}; }
	Vector2 operator -(Vector2 xx){ return (Vector2){x - xx.x, y - xx.y}; }
	double operator *(Vector2 xx){ return x * xx.y - xx.x * y; }
};

double cross(Vector2 oo, Vector2 xx, Vector2 yy){
	return (xx - oo) * (yy - oo);
}

double get_dis(Vector2 xx, Vector2 yy){
	return sqrt((xx.x - yy.x) * (xx.x - yy.x) + (xx.y - yy.y) * (xx.y - yy.y));
}

Vector2 a[maxn];
int st[maxn], top;
bool used[maxn];

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	For(i, 1, n) cin >> a[i].x >> a[i].y;
	sort(a + 1, a + 1 + n, [&](Vector2 xx, Vector2 yy)
			{ return xx.x == yy.x ? xx.y < yy.y : xx.x < yy.x; });
	st[++top] = 1;
	For(i, 2, n){
		while(top > 1 && cross(a[st[top - 1]], a[st[top]], a[i]) > 0)
			used[st[top--]] = 0;
		used[st[++top] = i] = 1;
	}
	int tmpcnt = top;
	Forr(i, n - 1, 1){
		if(!used[i]){
			while(top > tmpcnt && cross(a[st[top - 1]], a[st[top]], a[i]) > 0)
				used[st[top--]] = 0;
			used[st[++top] = i] = 1;
		}
	}
	//add 1 twice
	double ans = 0;
	For(i, 1, top - 1) ans += get_dis(a[st[i]], a[st[i + 1]]);
	printf("%.2lf\n", ans);
	return 0;
}
