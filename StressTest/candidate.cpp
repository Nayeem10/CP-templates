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

vector<int> adj[N], comp[N];
vector<int> order;
int vis[N], id[N], in[N], tmr = 1;

int dfs(int u){
    // cout << u << '\n';
    if(vis[u]) return id[u];
    vis[u] = 2, id[u] = u, in[u] = tmr++;
    for(auto v: adj[u]){
        int x = dfs(v);
        if(vis[x] == 2 and in[id[u]] > in[x]) id[u] = id[id[u]] = x;
    }
    vis[u] = 1;
    // cout << u << ' ' << id[u] << '\n';
    comp[id[u]].push_back(u);
    order.push_back(id[u]);
    return id[u];
}

int upd(int u){
    if(id[u] == u) return u;
    id[u] = upd(id[u]);
    comp[id[u]].push_back(u);
    return id[u];
}

void solve (int tc) {
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for(int i = 0; i < n; i++){
        if(!vis[i]) dfs(i);
    }
    int k = 0;
    for(int i = 0; i < n; i++){
        upd(i);
        if(id[i] == i) comp[i].push_back(i), k++;
    }

    cout << k << '\n';
    vector<int> vis(n + 1);
    reverse(all(order));

    // for(int i = 0; i < n; i++){
    //     int id = order[i];
    //     if(vis[id]) continue;
    //     vis[id] = 1;
    //     cout << comp[id].size() << ' ';
    //     for(auto u: comp[id])
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
