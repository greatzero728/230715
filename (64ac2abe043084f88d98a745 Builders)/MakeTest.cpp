#define rnd (((((INT)rand() << 15) | rand()) << 15) | rand())
#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 505, MM = NN * NN;

int a[NN][NN], f[MM];
char s[NN << 1];

int main() {
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	
	int n = 500, m = 500;
//	n = rnd % n + 1, m = rnd % m + 1;
	printf("%d %d\n", n, m);
	int nn = 0, x = 1, y = 1;
	for(int i = 1; i < m; i++) {
		if(rnd & 1) s[nn++] = 'L', y++;
		else s[nn++] = 'R';
	}
	for(int i = 1; i < n; i++) {
		if(rnd & 1) s[nn++] = 'U', x++;
		else s[nn++] = 'D';
	}
	random_shuffle(s, s + nn);
//	for(int i = 0; i < nn; i++) cout<<s[i]<<' '; puts("");
	
	int N = 1;
	int xmn = x, xmx = x;
	int ymn = y, ymx = y;
	for(int k = 0; k < nn; k++) {
		int st = N;
		for(int i = xmn; i <= xmx; i++) {
			for(int j = ymn; j <= ymx; j++) if(!a[i][j]) {
				f[N] = N, N++;
			}
		}
		random_shuffle(f + st, f + N);
		for(int i = xmn; i <= xmx; i++) {
			for(int j = ymn; j <= ymx; j++) if(!a[i][j]) {
				a[i][j] = f[st++];
			}
		}
		if(s[k] == 'L') ymn--;
		else if(s[k] == 'R') ymx++;
		else if(s[k] == 'U') xmn--;
		else xmx++;
	}
	int st = N;
	for(int i = xmn; i <= xmx; i++) {
		for(int j = ymn; j <= ymx; j++) if(!a[i][j]) {
			f[N] = N, N++;
		}
	}
	random_shuffle(f + st, f + N);
	for(int i = xmn; i <= xmx; i++) {
		for(int j = ymn; j <= ymx; j++) if(!a[i][j]) {
			a[i][j] = f[st++];
		}
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			printf("%d ", a[i][j]);
		}
		puts("");
	}
	return 0;
}
