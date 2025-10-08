#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define PLL pair<long long, long long>
#define LL long long

#define faster { ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); }
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(), v.end()
 
const int N = 2e5 + 7;
const LL mod = 1e9 + 7;
const LL INF = 1e17 + 10;
const int inf = 1e9 + 10;

void solve(int tc){
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(auto &u: a)
        cin >> u;
    for(auto &u: b)
        cin >> u;
    LL cnt = 0;
    for(int l = 0; l < n; l++){
        for(int r = l; r < n; r++){
            int mx = 0;
            for(int i = l; i <= r; i++){
                if(a[i] > mx) {
                    if(a[i] == b[i]) cnt++;
                    mx = a[i];
                }else{
                    if(b[i] <= mx) cnt++;
                }
            }
        }
    }
    cout << cnt << '\n';
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