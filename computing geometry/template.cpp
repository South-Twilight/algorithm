#include <bits/stdc++.h>
#define For(aa, bb, cc) for(int aa = (bb); aa <= (int)(cc); ++aa)
#define Forr(aa, bb, cc) for(int aa = (bb); aa >= (int)(cc); --aa)
using namespace std;
const double eps = 1e-9;
const int maxn = 1e5 + 10;
const int inf = 0x3f3f3f3f;

int fcmp(double x) { //check +, -, 0
	if(fabs(x) < eps) return 0;
	return x > 0 ? 1 : - 1;
}

//2-dimension
struct Vector2 { 
	double x, y;
	
	Vector2(): x(0), y(0) {}
	Vector2(double p0, double p1): x(p0), y(p1) {}

	Vector2 operator +(Vector2 p0) { return (Vector2) { p0.x + x, p0.y + y }; }
	Vector2 operator -(Vector2 p0) { return (Vector2) { x - p0.x, y - p0.y }; }
	Vector2 operator *(double p0) { return (Vector2) { p0 * x, p0 * y }; }
	Vector2 operator /(double p0) { return (Vector2) { x / p0, y / p0 }; }
	double operator *(Vector2 p0) { return x * p0.y - p0.x * y; } //cross
	bool operator ==(Vector2 p0) { return x == p0.x && y == p0.y; }
	double len(){ return sqrt(x * x + y * y); }
	//a cross b > 0 => a -> b outside paper
};

//3-dimension
struct Vector3 { 
	double x, y, z;

	Vector3(): x(0), y(0), z(0) {}
	Vector3(double p0, double p1, double zz): x(p0), y(p1), z(zz) {}
	Vector3 operator +(Vector3 p0) { return (Vector3) { p0.x + x, p0.y + y, p0.z + z }; }
	Vector3 operator -(Vector3 p0) { return (Vector3) { x - p0.x, y - p0.y, z - p0.z }; }
	Vector3 operator *(double p0) { return (Vector3) { p0 * x, p0 * y, p0 * z }; }
	Vector3 operator /(double p0) { return (Vector3) { x / p0, y / p0, z / p0 }; }
	Vector3 operator *(Vector3 p0) { //cross
		double x0 = y * p0.z - z * p0.y;
		double y0 = z * p0.x - x * p0.z;
		double z0 = x * p0.y - y * p0.x;
		return (Vector3) { x0, y0, z0 };
	} 
	double len(){ return sqrt(x * x + y * y + z * z); }
};

// p1_p0_p2
double get_sita(Vector2 p0, Vector2 p1, Vector2 p2) {
	double a = (p1 - p0).len();
	double b = (p2 - p0).len();
	double c = (p2 - p1).len();
	return acos((a * a + b * b - c * c) / (2 * a * b));
}

//p0 * p1
double dot(Vector2 p0, Vector2 p1) { 
	return p0.x * p1.x + p0.y * p1.y;
}

//p0 * p1
double dot(Vector3 p0, Vector3 p1) { 
	return p0.x * p1.x + p0.y * p1.y + p0.z * p1.z;
}

//oo->p0 cross oo->p1
double cross(Vector2 oo, Vector2 p0, Vector2 p1) { 
	return (p0 - oo) * (p1 - oo);
}

//oo->p0 cross oo->p1
Vector3 cross(Vector3 oo, Vector3 p0, Vector3 p1) { 
	return (p0 - oo) * (p1 - oo);
}

// |p0, p1|
double get_dis(Vector2 p0, Vector2 p1) { 
	return sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
}

// |p0, p1|
double get_dis(Vector3 p0, Vector3 p1) { 
	return sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y) + (p0.z - p1.z) * (p0.z - p1.z));
}

struct line {
	Vector2 ps, dir;

	line() {}
	line(Vector2 p0, Vector2 p1) {
		ps = p0;
		dir = p1 - p0;
		dir = dir / dir.len();
	}
};

// 点关于直线的投影
Vector2 proj(line l, Vector2 p) {
	double len = dot(l.dir, p - l.ps);
	return l.ps + l.dir * len;
}

// 点关于直线的反射
Vector2 reflec(line l, Vector2 p) {
	Vector2 p0 = proj(l, p);
	return p + (p0 - p) * 2;
}

// 直线顺逆时针旋转
line line_rotate(line l1, double sita) {
	line l2 = l1;
	l2.dir.x = l1.dir.x * cos(sita) - l1.dir.y * sin(sita);
	l2.dir.y = l1.dir.x * sin(sita) + l1.dir.y * cos(sita);
	return l2;
}

#define COUNTER_CLOCK 1
#define CLOCK 2
#define ON_LINE_BACK 3
#define ON_LINE_FRONT 4
#define ON_SEGMENT 5

// 点与线段的关系
int point_segment(Vector2 p0, Vector2 p1, Vector2 p) {
	double res = (p1 - p0) * (p - p0);
	if(res > 0) return COUNTER_CLOCK;
	else if(res < 0) return CLOCK;
	else { 
		if(dot(p - p0, p1 - p0) < 0) return ON_LINE_BACK; //BACK
		else {
			if(dot(p1 - p0, p - p1) > 0) return ON_LINE_FRONT;
			else return ON_SEGMENT;
		}
	}
}

#define line_orthogonal 1
#define line_parallel 2
#define line_other 0

// 两条直线的位置
int two_line(line s1, line s2) {
	if(dot(s1.dir, s2.dir) == 0) return line_orthogonal;
	if(s1.dir * s2.dir == 0) return line_parallel;
	return line_other; 
}

#define seg_not_intersect 0
#define seg_is_intersect 0

// 线段是否相交
bool two_seg_intersect(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3) { 
	if(max(p0.x, p1.x) < min(p2.x, p3.x) ||
	   max(p0.y, p1.y) < min(p2.y, p3.y) ||
	   min(p0.x, p1.x) > max(p2.x, p3.x) ||
	   min(p0.y, p1.y) > max(p2.y, p3.y)) { //fast_repel
		return seg_not_intersect;
	}
	if(((p0 - p3) * (p2 - p3)) * ((p1 - p3) * (p2 - p3)) > 0 ||
	   ((p2 - p1) * (p0 - p1)) * ((p3 - p1) * (p0 - p1)) > 0) { //kua_li 
		return seg_not_intersect;
	}
	return seg_is_intersect;
}

// 两条线段交点
Vector2 two_line_crosspoint(line s1, line s2) {
	if(s1.ps == s2.ps) return s1.ps;
	Vector2 u = s2.ps - s1.ps;
	double t = (u * s2.dir) / (s1.dir * s2.dir);
	return s1.ps + s1.dir * t;
}

// 点到线段的距离
double seg_point_dis(Vector2 p0, Vector2 p1, Vector2 p2) { //seg p0p1
	if(dot(p1 - p0, p2 - p0) <= 0) return (p2 - p0).len();
	if(dot(p0 - p1, p2 - p1) <= 0) return (p2 - p1).len();
	return fabs((p1 - p0) * (p2 - p0)) / (p1 - p0).len();
}

// 两个线段的距离
double two_seg_dis(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3) {
	if(two_seg_intersect(p0, p1, p2, p3)) return 0;
	double d1 = seg_point_dis(p0, p1, p2);
	double d2 = seg_point_dis(p0, p1, p3); 
	double d3 = seg_point_dis(p2, p3, p0); 
	double d4 = seg_point_dis(p2, p3, p1); 
	return min(min(d1, d2), min(d3, d4));
}

// 多边形
struct Polygon {
	int tot;
	vector<Vector2> p; //index begin with 0
	
	Polygon() { tot = 0; }
	Polygon(int n): tot(n) {}

	double get_girth() {
		double ans = 0;
		for(int i = 0; i < tot; ++i) ans += (p[i] - p[(i + 1) % tot]).len();
		return ans;
	}
	
	void ins(Vector2 p0) { 
		p.push_back(p0), ++tot;
	}
	
	double area() {
		double ans = 0;
		for(int i = 0; i < tot; ++i)
			ans += p[i] * p[(i + 1) % tot];
		ans *= 0.5;
		return fabs(ans);
	}
};

// 求凸包
Polygon get_convex_polygon(Polygon g) { //Andrew
	int cp[maxn], top = 0, n = g.tot;
	bool used[maxn]; //in_cp
	for(int i = 0; i < n; ++i) used[i] = 0;
	sort(g.p.begin(), g.p.end(), [&](Vector2 p0, Vector2 p1)
			{ return p0.x == p1.x ? p0.y < p1.y : p0.x < p1.x; });
	cp[++top] = 0;
	for(int i = 1; i < n; ++i) {
		while(top > 1 && cross(g.p[cp[top - 1]], g.p[cp[top]], g.p[i]) < 0) {
			used[cp[top--]] = 0;
		}
		used[cp[++top] = i] = 1;
	}
	int limcnt = top; //limited cnt
	for(int i = n - 2; i >= 0; --i) {
		if(used[i]) continue;
		while(top > limcnt && cross(g.p[cp[top - 1]], g.p[cp[top]], g.p[i]) < 0) {
			used[cp[top--]] = 0;
		}
		used[cp[++top] = i] = 1;
	}
	--top; //add 1 twice
	Polygon tb(top);
	for(int i = 1; i <= top; ++i) tb.p.push_back(g.p[cp[i]]);
	return tb;
}

// 检查是否为凸包
bool check_convex_polygon(Polygon g) {
	int ans = 1;
	int n = g.tot;
	int ori = fcmp(cross(g.p[0], g.p[1], g.p[2]));
	for(int i = 0; i < n; ++i) {
		int fx = fcmp(cross(g.p[i], g.p[(i + 1) % n], g.p[(i + 2) % n]));
		if(fabs(ori) < eps) ori = fx; // except on_line
		ans &= (ori == fx || fabs(fx) < eps);
	}
	return ans;
}

#define Polygon_contain_point 2
#define Point_on_polygon 1
#define Polygon_not_contain_point 0

// 多边形是否包含点
int polygon_point_contain(Polygon g, Vector2 p) {
	int n = g.tot;
	int cross_cnt = 0;
	for(int i = 0; i <  n; ++i) {
		Vector2 p0 = g.p[i], p1 = g.p[(i + 1) % n];
		if(point_segment(p0, p1, p) == ON_SEGMENT) return Point_on_polygon;
		if(p0.y > p1.y) swap(p0, p1);
		if(p0.y <= p.y && p1.y > p.y && (p0 - p) * (p1 - p) > 0) {
			cross_cnt ^= 1;
		}
		//only calc up_seg
	}
	return cross_cnt ? Polygon_contain_point : Polygon_not_contain_point;
}

// 求凸包直径
double get_convex_diameter(Polygon g) { 
	int id = 1, n = g.tot;
	while(id + 1 < n && get_dis(g.p[0], g.p[id + 1]) > get_dis(g.p[0], g.p[id])) ++id;
	double ans = get_dis(g.p[0], g.p[id]);
	for(int i = 1; i < n; ++i) {
		if(id == i) id = (id + 1) % n;
		while(get_dis(g.p[i], g.p[(id + 1) % n]) > get_dis(g.p[i], g.p[id])) {
			id = (id + 1) % n;
		}
		ans = max(ans, get_dis(g.p[i], g.p[id]));
	}
	return ans;
}

// 将凸包切割成两个，求左边部分的面积
Polygon Cut_convex_polygon(Polygon g, Vector2 p0, Vector2 p1) { 
	Polygon ans;
	line l1(p0, p1);
	for(int i = 0; i < g.tot; ++i) { 
		Vector2 pp0 = g.p[i], pp1 = g.p[(i + 1 == g.tot) ? 0 : i + 1];
		line l2(pp0, pp1);
		int tp1 = point_segment(p0, p1, pp0);
		int tp2 = point_segment(p0, p1, pp1);
		if(tp1 != CLOCK) ans.ins(pp0);
		if(tp1 * tp2 == CLOCK * COUNTER_CLOCK) { 
			ans.ins(two_line_crosspoint(l1, l2)); 
		}
	}
	return ans;
}

// 平面最近点对
struct Closest_point_pair {
	int tot;
	Vector2 p[maxn], st[maxn];

	Closest_point_pair() { tot = 0; }

	void ins(Vector2 p0) { p[++tot] = p0; }

	bool cmp_x(Vector2 p0, Vector2 p1) {
		return p0.x == p1.x ? p0.y < p1.y : p0.x < p1.x;
	}

	double rec(int l, int r) {
		if(r - l <= 3) {
			double mind = inf;
			for(int i = l; i <= r; ++i) {
				for(int j = i + 1; j <= r; ++j) {
					mind = min(mind, get_dis(p[i], p[j]));
				}
			}
			sort(p + l, p + r + 1, [&](Vector2 p0, Vector2 p1) { return p0.y < p1.y; });
			return mind;
		}
		int mid = (l + r) >> 1; 
		double midx = p[mid].x;
		double mind = min(rec(l, mid), rec(mid + 1, r));
		// merge with y
		int top = 0, L = l, R = mid + 1;
		while(L <= mid && R <= r) {
			if(p[L].y < p[R].y) st[++top] = p[L++];
			else st[++top] = p[R++];
		}
		while(L <= mid) st[++top] = p[L++];
		while(R <= r) st[++top] = p[R++];
		for(int i = 1; i <= top; ++i) p[i + l - 1] = st[i];

		top = 0;
		for(int i = l; i <= r; ++i) { 
			if(fabs(p[i].x - midx) > mind) continue;
			for(int j = top; j && fabs(p[i].y - st[j].y) < mind; --j) {
				mind = min(mind, get_dis(p[i], st[j]));
			}
			st[++top] = p[i];
		}
		return mind;
	}


	double get_ans() { 
		sort(p + 1, p + 1 + tot, [&](Vector2 p0, Vector2 p1)
				{ return p0.x == p1.x ? p0.y < p1.y : p0.x < p1.x; });
		double d = rec(1, tot);
		return d;
	}
};

#define CircleNotCross 4
#define Circumscribed 3
#define Intersect 2
#define Inscribed 1
#define Included 0

struct Circle {
	double r;
	Vector2 cr;

	Circle() { r = 0; }
	Circle(double rr, double px, double py): r(rr), cr(Vector2{px, py}) {}
	Circle(double rr, Vector2 p0): r(rr), cr(p0) {}
};

// 圆与圆的位置关系
int CirclePos(Circle c1, Circle c2) {
	if(c1.r < c2.r) swap(c1, c2);
	double d = get_dis(c1.cr, c2.cr);
	if(d > c1.r + c2.r) return CircleNotCross;
	if(fcmp(d - c1.r - c2.r) == 0) return Circumscribed;
	if(c1.r - c2.r < d && d < c1.r + c2.r) return Intersect;
	if(fcmp(d - c1.r + c2.r) == 0) return Inscribed;
	return Included;
}

Circle IncircleOfTriangle(Vector2 p1, Vector2 p2, Vector2 p3) {
	if(point_segment(p1, p2, p3) == CLOCK) swap(p2, p3);
	line l1(p1, p2);
	line l2(p2, p3);
	double sita1 = get_sita(p1, p2, p3);
	double sita2 = get_sita(p2, p1, p3);
	l1 = line_rotate(l1, sita1 / 2);
	l2 = line_rotate(l2, sita2 / 2);
	Vector2 cr = two_line_crosspoint(l1, l2);
	double r = seg_point_dis(p1, p2, cr);
	return Circle{r, cr};
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	Vector2 p1, p2, p3;
	cin >> p1.x >> p1.y;
	cin >> p2.x >> p2.y;
	cin >> p3.x >> p3.y;
	Circle c0 = IncircleOfTriangle(p1, p2, p3);
	printf("%.8lf %.8lf %.8lf\n", c0.cr.x, c0.cr.y, c0.r);
	return 0;
}

