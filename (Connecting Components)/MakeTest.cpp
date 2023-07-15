#define rnd (((((INT)rand() << 15) | rand()) << 15) | rand())
#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

int main() {
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	int t = 50;
	printf("%d\n", t);
	while(t--) {
		int n = 100000;
		printf("%d\n", n);
		if(rnd % 10 < 7) {
			for(int i = 2; i <= n; i++) {
				int x = rnd % (i - 1) + 1;
				printf("%d %d\n", x, i);
			}
		}
		else {
			for(int i = 1; i < n; i++) {
				int u = rnd % (n - 1) + 2;
				int x = rnd % (u - 1) + 1;
				printf("%d %d\n", u, x);
			}
		}
	}
	return 0;
}
