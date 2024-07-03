#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

#define int long long
#define pii pair<int,int> 
#define yes cout << "YES" << endl 
#define no  cout << "NO" << endl 
#define ln '\n'
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}

const int mod=998244353;
const int N=2e5+10;

inline void debugMode() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
}
 
int a[N],bin[N];
 
void update(int idx, int val, int n){
    while(idx<=n){
        bin[idx]+=val;
        idx += idx&-idx;
    }
}
 
int helper(int idx){
    int sum = 0;
    while(idx>0){
        sum+=bin[idx];
        idx -= idx&-idx;
    }
    return sum;
}

int query(int l,int r){
    return helper(r)-helper(l-1);
}

void solve(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        update(i,a[i],n);
    }
    while(q--){
        int check;
        cin>>check;
        if(check == 1){
            int k,u;
            cin>>k>>u;
            update(k,u-a[k],n);
            a[k]=u;
        }else if(check == 2){
            int a,b;
            cin>>a>>b;
            cout<<query(a,b)<<ln;
        }
    }
    
}
    

signed main(){
    faster
    debugMode();
    int t=1;
    //cin>>t;
    for(int cs=1;cs<=t;cs++){
        //cout<<"Case "<<cs<<": ";
        solve();
    }
    return 0;
}