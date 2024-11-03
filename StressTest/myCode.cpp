#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds; 
using namespace std;
 
typedef pair<long long,long long> PLL;
typedef long long LL;

#define all(v) v.begin(),v.end()
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_multiset tree<int, null_type,less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>    

const LL mod = 998244353;
const int N = 2e5 + 10;
const LL inf = 1e9;

void solve(int test){
    int n; cin>>n;
    vector<int> a(n);
    LL ans = 0;
    for(int i = 0; i < n; i++){
        cin>>a[i];
        if(a[i] != 2) ans++;
    }
    LL cnt = (a[0] != 2);
    for(int i = 1; i < n; i++){
        if(a[i] != a[i - 1]){
            ans += cnt * (cnt - 1) / 2;
            cnt = 0;
        }else if(a[i] != 2){
            cnt++;
        }
    }
    ans += cnt * (cnt - 1) / 2;
    vector<int> tmp; 
    map<int, LL> mp;
    int one = 0, three = 0; tmp.push_back(0);
    for(int i = 0; i < n; i++){
        if(a[i] == 2){
            for(auto u: tmp) mp[u]++;
            tmp.clear();
            ans += 1LL * mp[one - three];
            tmp.push_back(one - three);
        }else{
            if(a[i] == 1) one++;
            else three++;
            tmp.push_back(one - three);
            ans += 1LL * mp[one - three];
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    faster
    int t = 1; 
    // cin>>t;
    for(int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}
