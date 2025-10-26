//  https://codeforces.com/contest/832/problem/D

template<typename DT>
class SparsedTable {
private:
    vector<vector<DT>> table;
    vector<int> log;
    int n;

public:
    SparsedTable(const vector<DT>& arr){
        n = arr.size();
        log.resize(n + 1);
        buildLog();
        table = vector<vector<DT>>(n, vector<DT>(log[n] + 1));
        for (int i = 0; i < n; i++) 
            table[i][0] = arr[i];

        for (int j = 1; (1 << j) <= n; j++) 
            for (int i = 0; i + (1 << j) <= n; i++) 
                table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    
    }
    DT merge(DT &a, DT &b){ return min(a, b); }
    void buildLog() {
        log[1] = 0;
        for (int i = 2; i <= n; i++)
            log[i] = log[i / 2] + 1;
    }
    DT query(int L, int R) {
        int j = log[R - L + 1];
        return merge(table[L][j], table[R - (1 << j) + 1][j]);
    }
};

void dfs(int u, int p, int d, vector<int> g[], vector<pair<int, int>> &order, vector<int> &mp){
    for(auto v: g[u]){
        if(v == p) continue;
        order.push_back({d, u});
        dfs(v, u, d + 1, g, order, mp);
    }
    order.push_back({d, u});
    mp[u] = (int) order.size() - 1;
}

void solve(int tc) {
    int n, q; cin >> n >> q;
    vector<int> g[n + 1], mp(n + 1);
    vector<pair<int, int>> order;
    
    for(int u = 2, v; u <= n; u++){
        cin >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0, 0, g, order, mp);
    SparsedTable<pair<int, int>> sp(order);

    auto lca = [&](int u, int v){
        if(mp[u] > mp[v]) swap(u, v);

        return sp.query(mp[u], mp[v]).second;
    };
    auto dis = [&](int u, int v){
        int w = lca(u, v);
        u = mp[u], v = mp[v], w = mp[w];
        return order[u].first + order[v].first - 2 * order[w].first + 1;
    };
    auto ans = [&](int u, int v, int w){
        if(lca(u, w) == lca(v, w)) return dis(lca(u, v), w);
        return min(dis(lca(u, w), w), dis(lca(v, w), w));
    };
    while(q--){
        int u, v, w; cin >> u >> v >> w;
        cout << max({ans(u, v, w), ans(v, w, u), ans(w, u, v)}) << '\n';
    }
}