#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

#define pc _putchar_nolock
static char fjf[1010], so[44];
void pt(INT x) {
	int n = 0;
	while(so[n++] = x % 10, x /= 10);
	while(n--) pc(so[n] + 48);
}
char gc() {
	static char *L = fjf, *R = L;
	if(L == R) {
		int n = fread(fjf, 1, 1010, stdin);
		if(!n) return -1; L = fjf, R = L + n;
	}
	return *L++;
}
bool gn(int &x) {
	char c; while(c = gc(), (c < 48 || 57 < c) && ~c);
	for(x = c - 48; c = gc(), 48 <= c && c <= 57; x = 10 * x + c - 48);
	return 1;
}

const int NN = 303030;
const INT inf = 1e17;

int pa[NN], son[NN][2], sz[NN], nc, rt;
INT val[NN], sum[NN], mx[NN][2], flag_add[NN], flag_smn[NN];
int cnt[NN][2];

int make(INT x) {
	sz[++nc] = 1;
	
	val[nc] = sum[nc] = x;
	flag_add[nc] = 0, flag_smn[nc] = inf;
	
	mx[nc][1] = x, cnt[nc][1] = 1;
	mx[nc][0] = 0, cnt[nc][0] = 0;
	
	pa[nc] = son[nc][0] = son[nc][1] = 0;
	return nc;
}

void add(int u, INT x) {
	if(!u) return;
	val[u] += x, sum[u] += (INT)x * sz[u];
	
	mx[u][1] += x;
	if(cnt[u][0]) mx[u][0] += x;
	
	flag_add[u] += x;
	if(flag_smn[u] < inf) flag_smn[u] += x;
}
void update(int u, INT x) {
	if(!u || x >= mx[u][1]) return;
	if(x > mx[u][0]) {
		sum[u] -= (mx[u][1] - x) * cnt[u][1];
		mx[u][1] = x;
	}
	flag_smn[u] = min(flag_smn[u], x);
	if(flag_add[u]) flag_smn[u] -= flag_add[u];
}

void push_down(int u) {
	int &ls = son[u][0], &rs = son[u][1];
	if(flag_add[u]) {
		add(ls, flag_add[u]);
		add(rs, flag_add[u]);
		flag_add[u] = 0;
	}
	if(flag_smn[u] < inf) {
		update(ls, flag_smn[u]);
		update(rs, flag_smn[u]);
		flag_smn[u] = inf;
	}
}
using pIi = pair<INT, int>;
vector<pIi> vec;

void push_up(int u) {
	int ls = son[u][0], rs = son[u][1];
	sz[u] = 1, sum[u] = val[u];
	mx[u][1] = val[u], cnt[u][1] = 1;
	mx[u][0] = 0, cnt[u][1] = 0;
	
	if(ls) {
		sz[u] += sz[ls];
		sum[u] += sum[ls];
		
		vec.clear();
		for(int i = 2; i--; ) {
			if(cnt[u][i]) vec.push_back({mx[u][i], cnt[u][i]});
			if(cnt[ls][i]) vec.push_back({mx[ls][i], cnt[ls][i]});
			mx[u][i] = cnt[u][i] = 0;
		}
		sort(vec.begin(), vec.end(), [&](pIi a, pIi b) {
			return a.x > b.x;
		});
		
		for(int i = 0, j = 0, nn = 2; i < vec.size(); i = j) {
			int num = 0;
			for(; j < vec.size() && vec[i].x == vec[j].x; j++) num += vec[j].y;
			
			if(nn--) mx[u][nn] = vec[i].x, cnt[u][nn] = num;
			else break;
		}
	}
	if(rs) {
		sz[u] += sz[rs];
		sum[u] += sum[rs];
		
		vec.clear();
		for(int i = 2; i--; ) {
			if(cnt[u][i]) vec.push_back({mx[u][i], cnt[u][i]});
			if(cnt[rs][i]) vec.push_back({mx[rs][i], cnt[rs][i]});
			mx[u][i] = cnt[u][i] = 0;
		}
		sort(vec.begin(), vec.end(), [&](pIi a, pIi b) {
			return a.x > b.x;
		});
		
		for(int i = 0, j = 0, nn = 2; i < vec.size(); i = j) {
			int num = 0;
			for(; j < vec.size() && vec[i].x == vec[j].x; j++) num += vec[j].y;
			
			if(nn--) mx[u][nn] = vec[i].x, cnt[u][nn] = num;
			else break;
		}
	}
}

void smn(int u, INT h) {
	if(!u || h >= mx[u][1]) return;
	if(h > mx[u][0]) {
		update(u, h);
		return;
	}
	push_down(u);
	smn(son[u][0], h), smn(son[u][1], h);
	if(val[u] > mx[u][1]) val[u] = mx[u][1];
	push_up(u);
}

void rot(int x, bool d) {
	int y = pa[x], z = pa[y];
	if(son[z][0] == y) son[z][0] = x;
	else if(son[z][1] == y) son[z][1] = x;
	pa[x] = pa[pa[son[y][!d] = son[x][d]] = y];
	push_up(son[pa[y] = x][d] = y);
}
void splay(int x, int g) {
	bool d;
	for(int y; pa[x] ^ g; rot(x, d))
	if(pa[y = pa[x]] == g) d = son[y][0] == x;
	else son[y][d = son[pa[y]][0] == y] == x ? rot(x, !d) : rot(y, d);
	push_up(x);
	if(!g) rt = x;
}
int find(int u, int k) {
	int s;
	while(1) {
		push_down(u);
		if(k <= sz[s = son[u][0]]) {u = s; continue;}
		if(!(k -= sz[s] + 1)) return u;
		u = son[u][1];
	}
}
void insert(int k, int c) {
	int x = find(rt, k);
	splay(x, 0), splay(k = find(x, k + 1), x);
	push_up(pa[son[k][0] = make(c)] = k), push_up(x);
}

void init() {
	make(nc = 0), make(0);
	sz[rt = pa[2] = 1] = son[1][1] = 2;
}

INT a[NN << 1];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	init();
	int n, q; gn(n), gn(q);
	
	INT ans = 0;
	for(int i = 1, x; i <= n; i++) {
		gn(x), a[i] = x, ans += x;
	}
	
	while(q--) {
		int t, L, R, h; gn(t), gn(L), gn(R);
		
		if(t == 1) {
			gn(h);
			for(int i = L; i <= R; i++) {
				ans -= a[i];
				a[i] = min(a[i], (INT)h);
				ans += a[i];
			}
		}
		else if(t == 2) {
			for(int i = L; i <= R; i++) a[i - L + n + 1] = a[i];
			for(int i = L; i <= n; i++) a[i] = a[i - L + R + 1];
		}
		else {
			gn(h);
			for(int i = L; i <= R; i++) {
				a[i] += h;
				ans += h;
			}
		}
		pt(ans), pc(10);
	}
	return 0;
}