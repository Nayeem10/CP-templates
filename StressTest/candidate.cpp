#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define PLL pair<long long, long long>
#define LL long long

#define faster { ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); }
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(), v.end()

const int N = 2e5 + 7;
const LL mod = 1e9 + 7;
const LL INF = 1e17 + 10;
const int inf = 1e9 + 10;

void solve(int tc) {
    LL n, k; cin >> n >> k;
    vector<LL> a(n), fr(n + 1, 1);
    for(auto &u: a)
        cin >> u;
    sort(all(a));
    LL sum = 0;
    LL ans = 0;
    for(int i = 0; i < n; i++){
        ans = (ans + sum * a[i] % mod) % mod;
        sum = (sum + a[i]) % mod;
    cout << sum  << ' ' << k << '\n';
    }
    for(int i = 0; i < n; i++){
        LL diff = (i == n - 1 ? INF : a[i + 1]) - a[i];
        LL taken = min(diff, k / fr[i]);
        LL cost = taken * fr[i];
        k -= cost;
        LL cur = (sum - a[i] + mod) % mod;
        LL f = fr[i], d = fr[i] - 1;
        ans = (ans + (f * (cur * taken % mod + (d * ((taken * (taken - 1) / 2) % mod)) % mod) % mod + (f * (f - 1) / 2) % mod) * taken % mod) % mod;
        sum = (sum + cost) % mod;
        a[i] += taken;

        if(taken == diff) fr[i + 1] += fr[i], fr[i] = 0;
        if(fr[i]){
            cur = (sum - a[i] + mod) % mod;
            ans = (ans + cur * k % mod + k * (k - 1) / 2) % mod;
            k = 0;
        }
    }
}

signed main() {
    faster
    int t = 1;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
    return 0;
}