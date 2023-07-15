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
	int n = 300000, q = 300000;
	cout<<n<<' '<<q<<endl;
	for(int i = n; i--; ) {
		printf("%d ", 2 + i);
	}
	puts("");
	while(q--) {
		int L = rnd % n + 1, R = rnd % n + 1;
		if(L > R) swap(L, R);
		printf("1 %d %d %d\n", L, R, rnd % n + 1);
	}
	return 0;
}
