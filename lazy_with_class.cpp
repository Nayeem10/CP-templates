#include<bits/stdc++.h>
using namespace std;
#define ln '\n'
#define LL long long

const int N = 1e5;


void solve(){
    cin>>n;
    for(int i=0;i<=4*n;i++) segTree[i] = 0, lazy[i] = 0;
    int q; cin>>q;
    while(q--){
        int tp; cin>>tp;
        if(tp == 1){
            int l,r,val; cin>>l>>r>>val; updateRange(1,1,n,l+1,r+1,val);
        }else{
            int l,r; cin>>l>>r;
            int range=(r-l+1);
            int sum=queryRange(1,1,n,l+1,r+1);
            if(sum%range){
                int g=__gcd(sum,range);
                sum /= g, range /= g;
                cout<<sum<<'/'<<range<<ln;
            }else
            cout<<sum/range<<endl;
        }
    } 
}

int main(){
    int t; cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case "<<i<<":\n";
        solve();
    }
    return 0;
}