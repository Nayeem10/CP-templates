template<typename DT>
class SparsedTable {
private:
    vector<vector<DT>> table;
    vector<int> log;
    int n;
 
public:
    SparsedTable() {}
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
 
vector<int> g[N], vg[N];
vector<pair<int, int>> order;
int tout[N];
SparsedTable<pair<int, int>> spt;
 
void dfs(int u, int p, int d){
    for(auto v: g[u]){
        if(v == p) continue;
        order.push_back({d, u});
        dfs(v, u, d + 1);
    }
    order.push_back({d, u});
    tout[u] = (int) order.size() - 1;
}
int lca(int u, int v){
    if(tout[u] > tout[v]) swap(u, v);
    return spt.query(tout[u], tout[v]).second;
}
int dis(int u, int v){
    int w = lca(u, v);
    u = tout[u], v = tout[v], w = tout[w];
    return order[u].first + order[v].first - 2 * order[w].first;
}

LL getAns(vector<int> comp){

    /////////////////////////////////////////////////////  Build Tree
    sort(all(comp), [&](int i, int j){
        return tout[i] < tout[j];
    });
 
    int n = comp.size();
    for(int i = 1; i < n; i++){
        comp.push_back(lca(comp[i - 1], comp[i]));
    }
 
    sort(all(comp), [&](int i, int j){
        return tout[i] < tout[j];
    });
    comp.erase(unique(all(comp)), comp.end());
 
    for(int i = 0; i < (int) comp.size() - 1; i++){
        int u = comp[i], v = comp[i + 1], w = lca(u, v);
        vg[w].push_back(u);
        vg[u].push_back(w);
    }
    /////////////////////////////////////////////////////




    /////////////////////////////////////////////////////  Clean Tree
    for(auto u: comp){
        vg[u].clear();
    }
    /////////////////////////////////////////////////////

    return ans;
}