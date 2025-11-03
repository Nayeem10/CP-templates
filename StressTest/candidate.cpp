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
    int a, b; cin >> a >> b;
    int n = a + b;
    vector<int> l, r;
    for(int i = 1; i <= n; i++){
        l.push_back(i);
    }
    for(int i = 1; i <= b; i++){
        r.push_back(a + i);
    }
    for(int i = 1; i <= a; i++){
        r.push_back(i);
    }
    set<pair<int, int>> s;
    for(int i = 0; i < n; i++){
        int x = l[i], y = r[i];
        if(x > y) swap(x, y);
        s.insert({x, y});
        cout << x << ' ' << y << '\n';
    }
    for(int i = 0; i < n; i++){
        int x = l[i], y = r[(i - 1 + n) % n];
        if(x > y) swap(x, y);
        s.insert({x, y});
        cout << x << ' ' << y << '\n';
        
    }
    cout << s.size() << '\n';
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