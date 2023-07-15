#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = unsigned long long;
using pii = pair<int, int>;

INT len(INT n, INT m) {
	return n + m - 2 << 1;
}

INT calc(INT n, INT m) {
	if(n == 1) return m;
	if(n == 2) return m + 1;
	if(n == 3) return n + (m - 1) * 2;
	if(n == 4) {
		if(m == 1) return n;
		if(m == 2) return n + 2;
		return len(n, m) - 1;
	}
	if(m == 1) return n;
	if(m == 2) return n + 2;
	if(m == 3) return len(n, m) - 1;
	if(m == 4) return len(n, m);
	
	if(n <= 10000 || m <= 10000) {
		return len(n, m) + calc(n - 4, m - 4);
	}
	INT k = min(n, m) - 1000 >> 2;
	INT st = len(n, m), d = len(n - 4, m - 4) - st;
	return calc(n - 4 * k, m - 4 * k) + (st + st + d * (k - 1)) * k / 2;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	
	INT n, m; cin>>n>>m;
	if(m == 1) cout<<n;
	else if(m == 2) cout<<n + 1;
	else cout<<n + 1 + calc(n, m - 2);
	return 0;
}