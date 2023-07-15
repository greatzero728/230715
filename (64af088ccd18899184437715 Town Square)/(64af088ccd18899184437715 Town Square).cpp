#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

using DO = long double;

const DO eps = 1e-4;

struct point {
	DO x, y;
	point(DO x = 0, DO y = 0) : x(x), y(y) {}
	point operator + (point a) {return point(x + a.x, y + a.y);}
	point operator - (point a) {return point(x - a.x, y - a.y);}
	point operator * (DO a) {return point(x * a, y * a);}
	point operator / (DO a) {return point(x / a, y / a);}
	DO operator ^ (point a) {return x * a.y - y * a.x;}
	DO operator * (point a) {return x * a.x + y * a.y;}
	bool operator < (const point &a) const {
		return fabsl(x - a.x) > eps ? x < a.x : y < a.y;
	}
	bool operator > (const point &a) const {
		return fabsl(x - a.x) > eps ? x > a.x : y > a.y;
	}
	bool operator == (const point &a) const {
		return fabsl(x - a.x) < eps && fabsl(y - a.y) < eps;
	}
	bool operator != (const point &a) const {
		return fabsl(x - a.x) > eps || fabsl(y - a.y) > eps;
	}
	point operator & (point a) {
		return point(x * a.x - y * a.y, x * a.y + y * a.x);
	}
	point rotate (DO al) {return *this & point(cosl(al), sinl(al));}
	point conj() {return point(-y, x);}
	DO al() {return atan2l(y, x);}
	DO nor() {return sqrtl(*this * *this);}
	point norm() {
		DO s = nor();
		return s < eps ? *this : point(x / s, y / s);
	}
	bool pos() {return y > eps || x > -eps && y > -eps;}
	void input() {cin>>x>>y;}
	void print() {printf("%lf %lf\n", (double)x, (double)y);}
};

point p[4];
const DO pi = acosl(-1), inf = 1e22;

bool flag[4];
DO mn, mx;

DO calc_one_direction_difference(point dir, bool ok = 0) {
	mn = inf, mx = -inf;
	for(int i = 4; i--; ) {
		DO d = dir * p[i];
		mn = min(mn, d);
		mx = max(mx, d);
	}
	if(ok) for(int i = 4; i--; ) {
		DO d = dir * p[i];
		if(fabsl(mn - d) < eps) flag[i] = 1;
		if(fabsl(mx - d) < eps) flag[i] = 1;
	}
	return mx - mn;
}

point ori_dir = point(1, 0).rotate(4.43473);

DO calc_difference(DO al, bool ok = 0) {
	point x_dir = ori_dir.rotate(al);
	point y_dir = x_dir.rotate(pi / 2);
	
	DO x = calc_one_direction_difference(x_dir);
	DO y = calc_one_direction_difference(y_dir);
	if(ok) return x - y;
	return fabsl(x - y);
}

DO solve(DO al) {
	point x_dir = point(1, 0).rotate(al);
	point y_dir = x_dir.rotate(pi / 2);
	
	for(int i = 4; i--; ) flag[i] = 0;
	calc_one_direction_difference(x_dir, 1);
	calc_one_direction_difference(y_dir, 1);
	for(int i = 4; i--; ) if(!flag[i]) return -111;
	
	return mx - mn;
}

int sgn(DO a) {return a < -eps ? -1 : a > eps;}

DO calc(DO st, DO ed) {
	for(int k = 150; k--; ) {
		DO a = (st + st + ed) / 3;
		DO b = (st + ed + ed) / 3;
		DO A = calc_difference(a), B = calc_difference(b);
		if(A < B) ed = b;
		else st = a;
	}
	DO al = (st + ed) / 2;
	DO d = calc_difference(al);
	if(d > 0.01) return -100;
	return solve(al) + 10;
}

void solve() {
	for(int i = 4; i--; ) p[i].input();
	
	int k = 70000;
	DO st = 0, step = pi / k, delta = step / 1000;
	
	for(; k--; st += step) {
		DO d = calc(st, st + delta);
		if(d > 9) {printf("%.2lf\n", (double)d); return;}
	}
	puts("no solution");
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	
	int t; scanf("%d", &t);
	for(int i = 1; i <= t; i++) {
		printf("Case %d: ", i);
		solve();
	}
	return 0;
}
