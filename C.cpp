#include<bits/stdc++.h>
/*
        penguin yes cop code
        https://codeforces.com/profile/Tuanhaiphong2
*/
using namespace std;
#define ll long long
#define fi first
#define se second
#define MOD 1000000007
const int MAXN = 4e5+7;
vector<ll> topo;
static ll in[1000];
ll dx[8] = {-1,0,0,1,-1,-1,1,1};
ll dy[8] = {0,-1,1,0,-1,1,-1,1};
static ll Hash,base = 131,k,n,LCM[MAXN],TICH[MAXN],a[MAXN];
static int GCD[MAXN];
ll gcd(ll a,ll b){
    while(b!=0){
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}
ll lcm_(ll a,ll b){
    if (max(a,b)==5342931457063200)return min(a,b);
    return a/gcd(a,b)*b;
}
void build(ll id,ll l,ll r){
    if (l==r){
        LCM[id] = a[l];
        GCD[id] = a[l];
        TICH[id] = a[l];
        return ;
    }
    ll mid = (l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    GCD[id] = gcd(GCD[id*2],GCD[id*2+1]);
    LCM[id] = lcm_(LCM[id*2],LCM[id*2+1]);
    TICH[id] = (TICH[id*2]%MOD)*(TICH[id*2+1]%MOD)%MOD;
}
void update(ll id,ll l,ll r,ll pos,ll value){
    if (l>pos||pos>r) return ;
    if (l==r){
        LCM[id] = value;
        GCD[id] = value;
        TICH[id] = value;
        return ;
    }
    ll mid = (l+r)/2;
    update(id*2,l,mid,pos,value);
    update(id*2+1,mid+1,r,pos,value);
    LCM[id] = lcm_(LCM[id*2],LCM[id*2+1]);
    GCD[id] = gcd(GCD[id+2],GCD[id*2+1]);
    TICH[id] = (TICH[id*2]%MOD)*(TICH[id*2+1]%MOD)%MOD;
}
namespace tree_LCM{
    ll get(ll id,ll l,ll r,ll u,ll v){
        if (l>v||u>r) return 5342931457063200;
        if (l>=u&&r<=v)return LCM[id];
        ll mid = (l+r)/2;
        return lcm_(get(id*2,l,mid,u,v),get(id*2+1,mid+1,r,u,v));
    }
}
namespace tree_GCD{
    ll get(ll id,ll l,ll r,ll u,ll v){
        if (l>v||u>r)return 1e18;
        if (l>=u||r<=v) return GCD[id];
        ll mid = (l+r)/2;
        ll x = get(id*2,l,mid,u,v);
        ll y = get(id*2+1,mid+1,r,u,v);
        if (x==1e18&&y==1e18) return 1e18;
        if (y==1e18) return x;
        if (x==1e18) return y;
        return gcd(x,y);
    }
}
namespace tree_TICH{
    ll get(ll id,ll l,ll r,ll u,ll v){
        if (l>v||u>r) return 1ll;
        if (l>=u&&r<=v) return TICH[id]%MOD;
        ll mid = (l+r)/2;
        return get(id*2,l,mid,u,v)*get(id*2+1,mid+1,r,u,v)%MOD;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    //freopen("ROBOT.INP","r",stdin);
    //freopen("ROBOT.OUT","w",stdout);
    static ll tt,xx,y,x,z,yy,d,j,l,r,lo,rr,i,res,m,ans,index,note,cnt;
    string ss,stt,sss,str,st,s;
    cin >> n;
    for (i = 1;i <= n;i++)
    cin >> a[i];
    build(1,1,n);
    cin >> tt;
    while(tt--){
        cin >> x;
        if (x==0){
            cin >> x >> y;
            update(1,1,n,x,y);
        }else {
            cin >> st >> l >> r;
            if (st[0]=='L')cout << tree_LCM::get(1,1,n,l,r) << '\n';
            if (st[0]=='G')cout << tree_GCD::get(1,1,n,l,r) << '\n';
            if (st[0]=='T')cout << tree_TICH::get(1,1,n,l,r) << '\n';
        }
    }
    return (0^0)&(200+10);
}
/*
  4 9 2 4
1 0 0 0 0
9 0 1 1 1
7 0 1 1 1
3 0 1 1 1
4 0 1 1 2
5 6
-2 -1 2 10 3
-2 -3 -1 9 12
 T
*/
