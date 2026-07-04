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

void solve (int tc) {
    int n; cin >> n; 
    string s; cin >> s;
    int pref[3] = {}; pref[0] = 1;
    LL ans = 1LL * n * (n + 1) / 2;
    for(int i = 0, j = 0, sum = 0; i < n; i++){
        if(i and s[i] == s[i - 1]) j = i;
        sum = (3 + sum + (s[i] == '1' ? 1 : -1)) % 3;
        ans -= ((i - j) / 2 + pref[sum]);
        pref[sum]++;
    }
    cout << ans << '\n';
}

signed main() {
    faster
    int t = 1;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
    return signed{};
}