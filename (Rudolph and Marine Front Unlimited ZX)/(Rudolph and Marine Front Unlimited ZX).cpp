#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long int
#define pb push_back
#define all(x) x.begin(),x.end()
#define Max 10000000000000000

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using min_heap=priority_queue<T, vector<T>, greater<T>>;

ll x[27][27];

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ll n,m,c=0;
    scanf("%lli %lli",&n,&m);

    for(ll i=1;i<=n*m;i++){
        string s;
        cin>>s;
        ll p=s[0]-'a',q=s[1]-'0';
        if(s.size()==3) q=q*10+s[2]-'0';
        q--; 
        ll a=1,b=1;
        for(ll j=p+1;j<=p+3 && j<n;j++){
            if(x[j][q]) break;
            a++;
        }
        for(ll j=p-1;j>=p-3 && j>=0;j--){
            if(x[j][q]) break;
            a++;
        }
        for(ll j=q+1;j<=q+3 && j<m;j++){
            if(x[p][j]) break;
            b++;
        }
        for(ll j=q-1;j>=q-3 && j>=0;j--){
            if(x[p][j]) break;
            b++;
        }
        //cout<<p<<" "<<q<<endl;
        if(a<4 && b<4) continue;
        x[p][q]=++c;
    }

    // for(ll i=0;i<n;i++){
    //     for(ll j=0;j<m;j++) cout<<x[i][j]<<" ";
    //     cout<<endl;
    // }

    ll ans=0;
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++){
            ll v=Max;
            for(ll k=0;k<4 && j+3<m;k++){
                if(!x[i][j+k]) continue;
                v=min(v,x[i][j+k]);
            }
            v+=3;
            if(j+3<m) ans=max(ans,v);

            v=Max;
            for(ll k=0;k<4 && i+3<n;k++){
                if(!x[i+k][j]) continue;
                v=min(v,x[i+k][j]);
            }
            v+=3;
            if(i+3<n) ans=max(ans,v);
        }
    }
    printf("%lli\n",ans);

    return 0;
}