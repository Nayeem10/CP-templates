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

    stack<int> st;
    vector<int> left(n, -1);
    for(int i = 0; i < n; i++){
        while(st.size() and a[st.top()] < max(a[i], b[i])) st.pop();
        if(st.size()) left[i] = st.top();
        st.push(i);
    }
    LL ans = 0;
    for(int i = 0; i < n; i++){
        if(a[i] == b[i]){
            ans += 1LL * (i + 1) * (n - i);
        }else{
            if(~left[i] and b[i] <= a[left[i]])
            ans += 1LL * (left[i] + 1) * (n - i);
        }
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