struct Dinic{
    struct edge{
        int to, rid, isRev;
        LL cap, flow;
    };
    int n, s, t;
    vector<vector<edge>> g;
    vector<int> level;
    Dinic(int _n) : n(_n + 5){
        g.resize(n);
    }
    
    void addEdge(int u, int v, LL cap){
        g[u].push_back({v, (int) g[v].size(), 0, cap, 0LL});
        g[v].push_back({u, (int) g[u].size() - 1, 1, 0LL, 0LL});
    }
    bool bfs(){
        level.assign(n, -1);
        queue<int> q;
        q.push(s); level[s] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &e: g[u]){
                int v = e.to;
                if(level[v] == -1 and e.cap > e.flow)
                    level[v] = level[u] + 1, q.push(v);
            }
        }
        return level[t] != -1;
    }
    LL dfs(int u, LL flow){
        if(u == t) return flow;
        LL ret = 0;
        for(int i = 0; i < (int) g[u].size() and flow; i++){
            edge &e = g[u][i];
            int v = e.to;
            if(level[v] != level[u] + 1 or e.cap <= e.flow) continue;
            LL cflow = dfs(v, min(flow, e.cap - e.flow));
            ret += cflow; flow -= cflow;
            e.flow += cflow, g[v][e.rid].flow -= cflow;
        }
        return ret;
    }
    LL maxFlow(int s, int t){
        this->s = s, this->t = t;
        LL flow = 0;
        while(bfs()){
            flow += dfs(s, INF);
        }
        return flow;
    }
};