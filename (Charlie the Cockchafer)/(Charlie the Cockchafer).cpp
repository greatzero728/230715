#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using DO = long double;

struct Point {
	int x, y, z;
	Point(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
	void input() {
		scanf("%d %d %d", &x, &y, &z);
		return;
	}
	bool operator == (Point a) {
		return x == a.x && y == a.y && z == a.z;
	}
	bool operator != (Point a) {
		return x != a.x || y != a.y || z != a.z;
	}
	Point operator + (Point a) {
		return Point(x + a.x, y + a.y, z + a.z);
	}
	Point operator - (Point a) {
		return Point(x - a.x, y - a.y, z - a.z);
	}
};

const int NN = 20202;

Point ST, ED;
Point U[NN], V[NN];

DO inf = 1e10, pi = acosl(-1);

DO sq(DO x) {
	return x * x;
}

DO dist(Point u, Point v) {
	return sqrtl(sq(u.x - v.x) + sq(u.y - v.y) + sq(u.z - v.z));
}
DO dist2(Point u, Point v) {
	return sq(u.x - v.x) + sq(u.y - v.y) + sq(u.z - v.z);
}

using pdi = pair<DO, int>;
priority_queue<pdi, vector<pdi>, greater<pdi> > q;

using pid = pair<int, DO>;
vector<pid> adj[NN];
DO d[NN];

DO calc_angle(Point A, Point C, Point B) {
	DO a2 = dist2(B, C), a = sqrtl(a2);
	DO b2 = dist2(A, C), b = sqrtl(b2);
	DO c2 = dist2(A, B);
	return acosl((a2 + b2 - c2) / 2 / a / b);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	
	int n; DO s, t;
	while(~scanf("%d", &n)) {
		cin>>s>>t, t *= pi / 180;
		
		ST.input(), ED.input();
		for(int i = n; i--; ) {
			U[i].input(), V[i].input();
			U[n + i] = V[i], V[n + i] = U[i];
		}
		n <<= 1;
		
		for(int i = n; i--; ) {
			adj[i].clear();
			if(U[i] == V[i]) continue;
			for(int j = n; j--; ) if(i % (n / 2) != j % (n / 2)) {
				if(U[j] == V[j]) continue;
				if(V[i] == U[j]) {
					adj[i].push_back({j, calc_angle(V[i] + V[i] - U[i], V[i], V[j]) / t + dist(U[j], V[j]) / s});
				}
			}
			if(ST != U[i]) d[i] = inf;
			else q.push({d[i] = dist(U[i], V[i]) / s, i});
		}
		
		while(!q.empty()) {
			pdi p = q.top(); q.pop();
			int u = p.y;
			if(p.x > d[u]) continue;
			
			for(pid x : adj[u]) {
				int v = x.x; DO w = x.y;
				if(d[v] > d[u] + w) {
					q.push({d[v] = d[u] + w, v});
				}
			}
		}
		
		DO ans = inf;
		for(int i = n; i--; ) if(V[i] == ED) {
			ans = min(ans, d[i]);
		}
		printf("%.3lf\n", (double)ans);
	}
	return 0;
}