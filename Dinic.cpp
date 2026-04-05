#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define PLL pair<long long, long long>
#define LL long long

#define faster { ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); }
#define ordered_multiset tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(), v.end()

const int N = 2e5 + 7;
const LL mod = 1e9 + 7;
const LL INF = 1e17 + 10;
const int inf = 1e9 + 10;

struct Dinic{
    struct edge{
        int to, rid, isRev;
        LL cap, flow;
    };
    int n, s, t;
    vector<vector<edge>> g;
    vector<int> level, ptr;
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
        for(int &i = ptr[u]; i < (int) g[u].size(); i++){
            edge &e = g[u][i];
            int v = e.to;
            if(level[v] != level[u] + 1 or e.cap <= e.flow) continue;
            LL cflow = dfs(v, min(flow, e.cap - e.flow));
            if(cflow){
                e.flow += cflow, g[v][e.rid].flow -= cflow;
                return cflow;
            }
        }
        return 0;
    }
    LL maxFlow(int s, int t){
        this->s = s, this->t = t;
        LL flow = 0;
        while(bfs()){
            ptr.assign(n, 0);
            while(LL cflow = dfs(s, INF)) flow += cflow;
        }
        return flow;
    }
};

void solve(int tc) {
    
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