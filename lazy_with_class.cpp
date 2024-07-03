#include<bits/stdc++.h>
using namespace std;
#define ln '\n'
#define LL long long

const int N = 1e5;

LL n;
std::vector<int> lazy(4 * N), segTree(4 * N);
void pushdown(LL node, LL val) {
  lazy[node*2] = val;
  lazy[node*2+1] = val;
}
void apply(LL node, LL curLeft, LL curRight) {
  if(lazy[node] != -1) {
    segTree[node] = lazy[node] * (curRight - curLeft + 1);
    if(curLeft != curRight) pushdown(node, lazy[node]);
    lazy[node] = -1;
  }
}
void updateRange(LL node, LL curLeft, LL curRight, LL l, LL r, LL val) {
  apply(node, curLeft, curRight);
  if(curLeft > curRight or curLeft > r or curRight < l) return;
  if(curLeft >= l and curRight <= r) {
    segTree[node] = val * (curRight - curLeft + 1);
    if(curLeft != curRight) pushdown(node, val);
    return;
  }
  LL mid = (curLeft + curRight) / 2;
  updateRange(node*2, curLeft, mid, l, r, val);        
  updateRange(node*2 + 1, mid + 1, curRight, l, r, val);   
  segTree[node] = segTree[node*2] + segTree[node*2+1];        
}

LL queryRange(LL node, LL curLeft, LL curRight, LL l, LL r) {
  if(curLeft > curRight or curLeft > r or curRight < l) return 0;
  apply(node, curLeft, curRight);
  if(curLeft >= l and curRight <= r) return segTree[node];
  LL mid = (curLeft + curRight) / 2;
  LL sumL = queryRange(node*2, curLeft, mid, l, r);         
  LL sumR = queryRange(node*2 + 1, mid + 1, curRight, l, r); 
  return (sumL + sumR);
}

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