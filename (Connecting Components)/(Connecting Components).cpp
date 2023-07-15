#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i, x, n) for(int i = x; i < (int)(n); ++i)
typedef vector<pair<int, int> > vp;

int const N = 100000, inf = 1e9;
vp g[N + 1];
vector<int> cy[N];
int vis[N + 1], vs = 1, n;

struct CM{
	vector<set<int> > v;
	set<int> all;
	CM(){}
	bool operator <(CM const &o)const { return v.size() > o.v.size(); }
	bool in(int x) { return all.find(x) != all.end(); }
};

bool in(int x, set<int> const &st) { return st.find(x) != st.end(); }

int getCost(int x, set<int> const &st){
	set<int>::iterator it = st.lower_bound(x);
	int an = it == st.end() ? inf : *it - x;
	if (it == st.begin())return an;
	--it;
	return min(an, x - *it);
}

int getCost(set<int> const &a, set<int> const &b){
	int an = inf;
	set<int>::iterator ita = a.begin(), itb = b.begin();
	while (ita != a.end() && itb != b.end()){
		an = min(an, abs(*ita - *itb));
		if (*ita < *itb)++ita; else ++itb;
	}
	return an;
}

vector<CM> cm;
map<vector<int>, int> mp;

int getId(vector<int> const &v){
	map<vector<int>, int>::iterator it = mp.find(v);
	if (it == mp.end()){
		int an = mp.size();
		cm.back().v.push_back(set<int>());
		return mp[v] = an;
	}
	return it->second;
}

int C;
vp build(int v, int p = 0){
	vp c;
	vis[v] = 0;
	f(i, 0, g[v].size()){
		int u = g[v][i].first;
		if (u == p)continue;
		if (vis[u] == 0)c.push_back(make_pair(C, u)), cy[g[v][i].second].push_back(C++);
		else {
			vp t = build(u, v);
			while (t.size())c.push_back(t.back()), cy[g[v][i].second].push_back(t.back().first), t.pop_back();
		}
	}
	f(i, 0, c.size())if (c[i].second == v)c.erase(c.begin() + i), --i;
	vis[v] = 1;
	return c;
}

void geted(int v){
	vis[v] = 0;
	cm.back().all.insert(v);
	f(i, 0, g[v].size()){
		int u = g[v][i].first;
		int id = g[v][i].second;
		if (!cy[id].empty()){
			sort(cy[id].begin(), cy[id].end());
			int cid = getId(cy[id]);
			cm.back().v[cid].insert(v);
			cm.back().v[cid].insert(u);
			cy[id].clear();
		}
		if (vis[u] == 0)continue;
		geted(u);
	}
}

void visi(int v){
	if (vis[v] == vs)return;
	vis[v] = vs;
	f(i, 0, g[v].size())visi(g[v][i].first);
}

int go(int v, int p, int mn = inf){
	int an = mn + getCost(v, cm[0].v[0]);
	mn = min(mn, getCost(v, cm[1].all));
	f(i, 0, g[v].size()){
		int u = g[v][i].first;
		if (u == p)continue;
		an = min(an, go(u, v, mn));
	}
	return an;
}

int solve(){
	scanf("%d", &n);
	f(i, 1, n + 1)g[i].clear();
	f(i, 1, n)cy[i].clear();
	f(i, 1, n){
		int a, b;
		scanf("%d%d", &a, &b);
		g[a].push_back(make_pair(b, i));
		g[b].push_back(make_pair(a, i));
	}
	int cmp = 0;
	f(i, 1, n + 1)vis[i] = inf;
	f(i, 1, n + 1)if (vis[i] > vs)++vs, visi(i), ++cmp;
	if (cmp == 1)return 0;
	if (cmp > 3)return -1;
	cm.clear();
	f(i, 1, n + 1)if (vis[i] > 1){
		cm.push_back(CM());
		mp.clear();
		build(i);
		geted(i);
	}
	sort(cm.begin(), cm.end());
	int an = inf;
	if (cmp == 2){
		an = getCost(cm[0].v[0], cm[1].all);
		f(i, 1, n + 1)if (in(i, cm[0].v[0]))f(j, 0, g[i].size())if (!in(g[i][j].first, cm[0].v[0]))an = min(an, go(g[i][j].first, i));
		return an;
	}
	if (cm[0].v.size() > 1){
		f(i, 0, cm[0].v.size())f(j, 0, cm[0].v.size())if (i != j)an = min(an, getCost(cm[0].v[i], cm[1].all) + getCost(cm[0].v[j], cm[2].all));
		return an;
	}
	int a = getCost(cm[0].v[0], cm[1].all);
	int b = getCost(cm[0].v[0], cm[2].all);
	int c = getCost(cm[1].v[0], cm[0].all);
	int d = getCost(cm[1].v[0], cm[2].all);
	return min(b + min(c, d), d + min(a, b));
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	int t;
	scanf("%d", &t);
	while (t--)printf("%d\n", solve());
}