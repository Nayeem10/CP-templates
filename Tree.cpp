struct Tree{
    vector<vector<int>> adj;
    Tree(int N): adj(N + 1) {}
    void addEdges(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

class LCA{
    int N, K;
    vector<vector<int>> adj, anc;
    vector<int> level;

public:
    
    LCA(Tree &tree): adj(tree.adj){
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
    CD(Tree &tree): adj(tree.adj){
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