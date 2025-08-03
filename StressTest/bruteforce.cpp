#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define PLL pair<long long, long long>
#define LL long long
 
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(),v.end()
 
const LL mod =  998244353;
const int N = 2e5 + 7;
 
const LL INF = 1e17 + 1;
const int inf = 1e9 + 1;

void solve(int tc) {
    int n, k; cin >> n >> k;
    multiset<int> ms;
    for(int i = 0; i < n; i++){
        int u; cin >> u; ms.insert(u);
    }
    LL ans = 0;
    while(*ms.rbegin() - *ms.begin() - 1 > k){
        ans += k;
        int r = *ms.rbegin() - 1, l = *ms.begin() + 1;
        ms.erase(ms.begin());
        auto it = ms.end(); it--;
        ms.erase(it);
        ms.insert(l); ms.insert(r);
    }
    for(auto u: ms){
        // cout << u << ' ';
        ans += (1LL * u * (u + 1) / 2);
    }
    cout << ans << '\n';
}
 
signed main() {
    faster
    int t = 1;
    // cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
    return 0;
}