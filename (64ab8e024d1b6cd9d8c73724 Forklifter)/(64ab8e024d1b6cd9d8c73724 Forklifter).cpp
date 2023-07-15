#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

int n, m;

const int NN = 101010;

vector<INT> a[NN], b[NN];
vector<bool> flag[NN];

int dx[] = {1, -1, 0, 0, -1, 1};
int dy[] = {0, 0, 1, -1, 1, -1};

bool out(int x, int y) {
	return x < 1 || y < 1 || x > n || y > m;
}

using pIp = pair<INT, pii>;
vector<pIp> vec;

bool can(INT s, INT k) {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) flag[i][j] = 0;
	}
	
	int x, y, i, j, I;
	INT c;
	for(pIp p : vec) {
		x = p.y.x, y = p.y.y, c = p.x;
		for(I = 6; I--; ) {
			i = x + dx[I], j = y + dy[I];
			if(!out(i, j) && flag[i][j]) c = max(c, b[i][j] - s);
		}
		b[x][y] = c, flag[x][y] = 1;
		k -= c - p.x;
		if(k < 0) return 0;
	}
	return k >= 0;
}

void solve() {
	INT k; scanf("%d %d %I64d", &n, &m, &k);
	
	vec.clear();
	for(int i = 1; i <= n; i++) {
		a[i].resize(m + 1), b[i] = a[i];
		flag[i].resize(m + 1);
		for(int j = 1; j <= m; j++) {
			scanf("%I64d", &a[i][j]);
			vec.push_back({a[i][j], {i, j}});
		}
	}
	sort(vec.begin(), vec.end(), [&](pIp a, pIp b) {
		return a.x > b.x;
	});
	
	INT st = -1, ed = 1e12 - 1;
	while(ed - st > 1) {
		INT md = st + ed >> 1;
		if(can(md, k)) ed = md;
		else st = md;
	}
	printf("%I64d\n", ed);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	
	int t; scanf("%d", &t);
	while(t--) solve();
	return 0;
}