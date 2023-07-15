#include <bits/stdc++.h>
typedef std::vector<int> vi;
bool test(vi s,int k,vi a)
{
	bool g[101][101];
	memset(g,0,sizeof(g));g[0][0]=1;
	bool wf[101][101],bf[101][101];
	memset(wf,0,sizeof(wf));
	memset(bf,0,sizeof(bf));
	for(size_t i=0;i<a.size();++i)
	{
		wf[i][i]=a[i]>=0;
		bf[i][i]=a[i]<=0;
		for(size_t j=i+1;j<a.size();++j)
		{
			wf[i][j]=wf[i][j-1]&&(a[j]>=0);
			bf[i][j]=bf[i][j-1]&&(a[j]<=0);
		}
	}
	for(size_t i=1;i<=a.size();++i)
	{if(a[i-1]==1)break;g[i][0]=1;}
	for(int i=1;i<=k;++i)
	for(size_t j=1;j<=a.size();++j)
	{
		bool x=g[j-1][i];
		bool y=(j>=s[i-1])&&
			wf[j-s[i-1]][j-1]&&
			(((i==1)&&(j==s[i-1]||bf[0][j-s[i-1]-1]))||
			 ((j>s[i-1])&&bf[j-s[i-1]-1][j-s[i-1]-1]&&
			  g[j-s[i-1]-1][i-1]));
		g[j][i]=x&&a[j-1]<=0||y&&a[j-1]>=0;
	}
	return g[a.size()][k];
}
int check(vi s,int k,vi& a)
{
	int ret=0;
	for(size_t i=0;i<a.size();++i)
		if(!a[i])
		{
			a[i]=1;
			if(!test(s,k,a)){a[i]=-1;ret=1;}
			else
			{
				a[i]=-1;
				if(!test(s,k,a)){a[i]=1;ret=1;}else a[i]=0;
			}
		}
	return ret;
}
int n,m,b[101][101],lr[101],lc[101];
int r[101][101],c[101][101];
void print()
{
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
			putchar(b[i][j]?b[i][j]>0?'X':'.':'?');
		puts("");
	}
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
	{
		scanf("%d",&lr[i]);
		for(int j=0;j<lr[i];++j)
		scanf("%d",&r[i][j]);
	}
	for(int i=0;i<m;++i)
	{
		scanf("%d",&lc[i]);
		for(int j=0;j<lc[i];++j)
		scanf("%d",&c[i][j]);
	}
	for(int t=1;t;)
	{
		t=0;
		for(int row=0;row<n;++row)
		{
			vi R;R.resize(m);
			for(int i=0;i<m;++i)R[i]=b[row][i];
			if(check(vi(r[row],r[row]+lr[row]),lr[row],R))
			{
				t=1;
				for(int i=0;i<m;++i)b[row][i]=R[i];
			}
		}
		for(int col=0;col<m;++col)
		{
			vi C;C.resize(n);
			for(int i=0;i<n;++i)C[i]=b[i][col];
			if(check(vi(c[col],c[col]+lc[col]),lc[col],C))
			{
				t=1;
				for(int i=0;i<n;++i)b[i][col]=C[i];
			}
		}
	}
	print();
	return 0;
}
