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
const int N = 5e2 + 10;
const int inf = 1e9 + 10;
const LL INF = 1e18;

vector<int> adj[N], radj[N], comp[N];
vector<int> order;
int compid[N], vis[N];

void dfs(int u){
    if(vis[u]) return;
    vis[u] = 1;
    for(auto v: adj[u]){
        dfs(v);
    }
    order.push_back(u);
}

void asgn(int u, int id){
    if(compid[u]) return;
    compid[u] = id;
    comp[id].push_back(u);
    for(auto v: radj[u]){
        asgn(v, id);
    }
}

void solve (int tc) {
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    for(int i = 0; i < n; i++){
        if(!vis[i]) dfs(i);
    }
    int k = 0;
    reverse(all(order));
    for(int i = 0; i < n; i++){
        if(!compid[order[i]]) asgn(order[i], ++k);
    }
    cout << k << '\n';
    // for(int i = 1; i <= k; i++){
    //     cout << comp[i].size() << ' ';
    //     for(auto u: comp[i])
    //         cout << u << ' ';
    //     cout << '\n';
    // }
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
