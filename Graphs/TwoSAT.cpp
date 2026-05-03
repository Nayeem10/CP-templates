struct TwoSatSolver{
    int n_var;
    vector<vector<int>> adj, radj;
    vector<int> order, vis, comp, assignment;

    void dfs(int u){
        if(vis[u]) return;
        vis[u] = 1;
        for(auto v: adj[u])
            dfs(v);
        order.push_back(u);
    }
    void asgn(int u, int id){
        if(comp[u]) return;
        comp[u] = id;
        for(auto v: radj[u])
            asgn(v, id);
    }

    TwoSatSolver(int n) : n_var(n + 1), adj(2 * n_var), radj(2 * n_var), vis(2 * n_var), comp(2 * n_var), assignment(n_var) {
        order.reserve(2 * n_var);
    }

    void add(int a, int nega, int b, int negb){
        a = 2 * a ^ nega, b = 2 * b ^ negb;
        adj[a ^ 1].push_back(b);
        radj[b].push_back(a ^ 1);
        adj[b ^ 1].push_back(a);
        radj[a].push_back(b ^ 1);
    }
    bool isSatisfiable(){
        order.clear();
        for(int i = 0; i < 2 * n_var; i++){
            if(!vis[i]) dfs(i);
        }
        reverse(all(order));
        for(int i = 0, j = 1; i < 2 * n_var; i++){
            if(!comp[order[i]]) asgn(order[i], j++);
        }
        bool fl = 1;
        for(int i = 0; i < n_var; i++){
            int l = 2 * i, r = 2 * i + 1;
            if(comp[l] == comp[r]) fl = 0;
            if(comp[l] < comp[r]) assignment[i] = 1;
        }
        return fl;
    }
};