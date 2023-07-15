#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 505, MM = NN * NN;

int a[NN][NN];
pii pos[MM];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
			pos[a[i][j]] = {i, j};
		}
	}
	int xmn = pos[1].x, xmx = xmn;
	int ymn = pos[1].y, ymx = ymn;
	int cnt = 1;
	
	while(cnt < n * m) {
		int u = cnt + 1;
		if(pos[u].x == xmn - 1) putchar('U'), xmn--, cnt += ymx - ymn + 1;
		else if(pos[u].x == xmx + 1) putchar('D'), xmx++, cnt += ymx - ymn + 1;
		else if(pos[u].y == ymn - 1) putchar('L'), ymn--, cnt += xmx - xmn + 1;
		else putchar('R'), ymx++, cnt += xmx - xmn + 1;
	}
	return 0;
}