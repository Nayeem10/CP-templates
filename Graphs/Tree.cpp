template<typename DT>
struct Tree {
    vector<vector<DT>> adj;
    Tree(int N) : adj(N + 1) {}
    Tree() {}

    void addEdges(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void addEdges(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    void dfs(int u, int p, Tree &Btree, int &T){
        int last = 0, tmp = 0;
        for(auto [v, w]: adj[u]){
            if(v == p) continue;
            tmp++;
            if(tmp == 1){
                Btree.addEdges(u, v, w);
                last = u;
            }else if(tmp == (int) adj[u].size() - (u != 1)){
                Btree.addEdges(last, v, w);
            }else{
                Btree.addEdges(last, ++T, 0);
                Btree.addEdges(T, v, w);
                last = T;
            }
        }
        for(auto [v, w]: adj[u]){
            if(v != p) dfs(v, u, Btree, T);
        }
    }
    Tree<pair<int, int>> binarize(){
        int N = adj.size() - 1;
        int T = N;
        Tree<pair<int, int>> Btree(2 * N);
        dfs(1, 0, Btree, T);
        Btree.adj.resize(T + 1);
        return Btree;
    }
};

class LCA{
    int N, K;
    vector<vector<int>> &adj, anc;
    vector<int> level;

public:
    
    LCA(Tree<int> &tree): adj(tree.adj){
        N = tree.adj.size() - 1;
        K = 33 - __builtin_clz(N);
        anc.assign(N + 1, vector<int>(K));
        level.assign(N + 1, 0);
        initLCA(1);
    }
    
    void initLCA(int u, int p = 0){
        anc[u][0] = p;
        level[u] = level[p] + 1;
        for(int i = 1; i < K; i++){
            anc[u][i] = anc[anc[u][i - 1]][i - 1];
        }
        for(auto v: adj[u]) if(v != p){
            initLCA(v, u);
        }
    }
    int getAnc(int u, int k){
        for(int i = K - 1; i >= 0; i--)
            if(k & (1<<i)) u = anc[u][i];
        return u;
    }
    int lca(int u, int v){
        if(level[u] > level[v]) swap(u, v);
        v = getAnc(v, level[v] - level[u]);
        
        if(u == v) return u;
        for(int i = K - 1; i >= 0; i--){
            if(anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
        }
        return anc[u][0];
    }
    int dis(int u, int v){
        return level[u] + level[v] - 2 * level[lca(u, v)];
    }
};

class CD{
    vector<vector<int>> adj;
    vector<int> sub;
    vector<bool> blocked;
    int N;
public:
    CD(Tree<int> &tree): adj(tree.adj){
        N = tree.adj.size() - 1;
        blocked.assign(N + 1, 0);
        sub.assign(N + 1, 0);
        compute();
    }
    void compute(int u = 1, int p = 0){
        sub[u] = 1;
        for(auto v: adj[u]) if(v != p){
            compute(v, u);
            sub[u] += sub[v];
        }
    }
    int centroid(int u, int p = 0){
        int tot = sub[u]; 
        for(auto v: adj[u]){
            if(v == p || blocked[v]) continue;
            if(2 * sub[v] > tot) {
                sub[u] = tot - sub[v];
                sub[v] = tot;
                return centroid(v, u);
            }
        }
        return u;
    }
    
    int count(int u, int p){  // calculate ans

    }
    void update(int u, int p){   // update
            
    } 

    int decompose(int u = 1){
        u = centroid(u);
        blocked[u] = 1;
        int ans = 0;
        
        /////   Do something here    //// count() update()
        for(auto v: adj[u]) if(!blocked[v]){
            ans += count(v, u);
            update(v, u);
        }
        /// reset updates here

        for(auto v: adj[u]) if(!blocked[v]){
            decompose(v);
        }
        return ans;
    }
};
// ancestor to child distance precalculated
class CD{
    vector<vector<int>> adj, dis;
    vector<int> sub, ans, par, level;
    vector<bool> blocked;
    int N;
public:
    CD(Tree<int> &tree): adj(tree.adj){
        N = tree.adj.size() - 1;
        int K = 33 - __builtin_clz(N);
        dis.assign(N + 1, vector<int> (K));
        blocked.assign(N + 1, 0);
        sub.assign(N + 1, 0);
        par.assign(N + 1, 0);
        level.assign(N + 1, 0);
        ans.assign(N + 1, N + 10);
        compute();
        decompose();
    }
    void compute(int u = 1, int p = 0){
        sub[u] = 1;
        for(auto v: adj[u]) if(v != p){
            compute(v, u);
            sub[u] += sub[v];
        }
    }
    int centroid(int u, int p = 0){
        int tot = sub[u]; 
        for(auto v: adj[u]){
            if(v == p || blocked[v]) continue;
            if(2 * sub[v] > tot) {
                sub[u] = tot - sub[v];
                sub[v] = tot;
                return centroid(v, u);
            }
        }
        return u;
    }
    void getDis(int u, int p, int l, int d){
        dis[u][l] = d;
        for(auto v: adj[u]){
            if(blocked[v] || v == p) continue;
            getDis(v, u, l, d + 1);
        }
    }
    void decompose(int u = 1, int p = 0, int l = 1){
        u = centroid(u);
        blocked[u] = 1, par[u] = p, level[u] = l;
        getDis(u, p, l, 0);
        for(auto v: adj[u]) if(!blocked[v]){
            decompose(v, u, l + 1);
        }
    }
    void update(int u){
        for(int i = u; i; i = par[i])
            ans[i] = min(ans[i], dis[u][level[i]]);
    }
    int query(int u){
        int ret = ans[u];
        for(int i = u; i; i = par[i])
            ret = min(ret, dis[u][level[i]] + ans[i]);
        return ret;
    }
};
