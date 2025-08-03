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
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(all(a));
    auto checkHigh = [&](int limit){
        LL extra = 0, empty = 0;
        for(int i = 0; i < n; i++){
            extra += max(0, a[i] - limit);
            empty += max(0, limit - k - a[i] + 1);
        }
        return empty >= extra;
    };

    LL l = 1, r = 1e6, up = 1e6;
    while(r >= l){
        int m = (l + r) / 2;
        if(checkHigh(m)){
            up = m; r = m - 1;
        }else{
            l = m + 1;
        }
    }
    LL ans = 0, tot = 0;
    vector<LL> pref(n);
    for(int i = 0; i < n; i++){
        tot += max(0LL, a[i] - up);
        a[i] = min(up, 1LL * a[i]);
        pref[i] = a[i] + (i ? pref[i - 1] : 0);
    }
    ans += tot * k;
    for(int i = n - 1; i >= 0; i--){
        LL need = tot - a[i] * i + (i ? pref[i - 1] : 0);
        if(need <= 0) continue;
        need = (need + i) / (i + 1);
        a[i] += need; tot -= need;
    }
    int i = 0, j = 1;
    while(j < n and i < j){
        if(a[j] - a[i] >= k + 1){
            a[i]++, a[j]--, ans += k;//i++;
            if(a[j] - a[i] - 1 == k + 1) i++; 
        } 
        j++;
    }
    // ans = 0;
    for(int i = 0; i < n; i++){
        // cout << a[i] << ' ';
        ans += (1LL * a[i] * (a[i] + 1)) / 2;
    }
    // cout << '\n';
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