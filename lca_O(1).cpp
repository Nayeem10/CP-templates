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

void eularTour(int u, int p, int d, vector<int> g[], vector<pair<int, int>> &circuit, vector<int> &invMap){
    for(auto v: g[u]){
        if(v == p) continue;
        circuit.push_back({d, u});
        eularTour(v, u, d + 1, g, circuit, invMap);
    }
    circuit.push_back({d, u});
    invMap[u] = (int) circuit.size() - 1;
}

void solve(int tc) {
    int n, q; cin >> n >> q;
    vector<int> g[n + 1], invMap(n + 1);
    vector<pair<int, int>> circuit;
    for(int u = 2, v; u <= n; u++){
        cin >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    eularTour(1, 0, 0, g, circuit, invMap);
    SparsedTable<pair<int, int>> sp(circuit);

    auto lca = [&](int u, int v){
        if(invMap[u] > invMap[v]) swap(u, v);

        return sp.query(invMap[u], invMap[v]).second;
    };
    auto dis = [&](int u, int v){
        int w = lca(u, v);
        u = invMap[u], v = invMap[v], w = invMap[w];
        return circuit[u].first + circuit[v].first - 2 * circuit[w].first + 1;
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