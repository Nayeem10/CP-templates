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
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 0; i < n; i++){
        ans = (ans + sum * a[i] % mod) % mod;
        sum = (sum + a[i]) % mod;
        pq.push(a[i]);
    }
    while(k){
        int cur = pq.top(); pq.pop(); pq.push(cur + 1);
        cout << sum << ' ' << cur << '\n';
        ans += (sum - cur); sum++; cur++, k--;
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
    return 0;
}