#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
using LL = long long;
using PLL = pair<LL, LL>;

#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_set tree<LL, null_type,less<LL>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(), v.end()

const LL mod = 998244353;
const int N = 1e6 + 10;
const int inf = 1e9 + 10;
const LL INF = 1e18 + 10;

void pre() {
    
}

void solve (int tc) {
    int n; cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    LL ans = 0;
    for(int i = 1; i <= n; i++){
        LL cur = 0;
        for(int j = i; j <= n; j++){
            if(cur + 1 == a[j]) cur++;
            ans += cur;
        }
    }
    cout << ans << '\n';
}

signed main() {
    faster
    pre();
    int t = 1;
    // cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
    return signed{};
}

/*
 
 * WRITE STUFFS DOWN
 * DON'T GET STUCK ON ONE APPROACH
 
*/