#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define PLL pair<long long, long long>
#define LL long long

#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_multiset tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(),v.end()

const LL mod = 1e9 + 7;
const int N = 8e3 + 10;
LL inf = 1e17 + 1;

LL get(LL n){
    LL ret = (n % 4 == 2 || n % 4 == 3);
    for(LL i = 1; i < 63; i++){
        LL r = (1LL << i), d = (r << 1);
        LL m = n % d;
        if(m <= r) continue;
        if(m & 1) ret |= (1LL<<i);
    }
    return ret;
}

LL getk(LL n, LL p, LL k){
    p = (1LL << p);
    LL ret = n / p;
    n %= p;
    ret += (n >= k);
    return ret;
}

void solve(int tc) {
    LL l, r, i, k; cin>>l>>r>>i>>k;
    LL ans = get(r + 1) ^ get(l);
    LL cnt = getk(r, i, k) - getk(l - 1, i, k); 
    if(cnt & 1) ans ^= k;
    LL R = (r >> i);
    if(r % (1LL << i) < k) R--;
    l--;
    LL L = (l >> i);
    if(l % (1LL << i) < k) L--; 
    LL extra = get(R + 1) ^ get(L + 1);
    cout<<(ans ^ (extra << i))<<'\n';
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