//https://codeforces.com/problemset/problem/757/G
#include <bits/stdc++.h>
using namespace std;

#define PLL pair<long long, long long>
#define LL long long
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}

const int mod = 1e9+7;
const int N = 2e5+10;
int inf = 1e8+1;

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

// use global array for better performance
class PCD{
    vector<vector<pair<int, int>>> &adj;
    vector<vector<int>> ct;
    vector<vector<long long>> dis;
    vector<int> sub, level, st, en, cnt, id; // id --> represent the id of original tree in persistent centroid tree
    vector<long long> ans, contrib;
    vector<bool> blocked;
    int N, T;
public:
    PCD(Tree<pair<int, int>> &tree, int U): adj(tree.adj){
        N = tree.adj.size() - 1; T = 0;
        int K = 33 - __builtin_clz(N);

        // These are calculated on original cetroid tree. Will not be affected in future update
        dis.assign(N + 1, vector<long long> (K));
        blocked.assign(N + 1, 0);
        sub.assign(N + 1, 0);
        level = st = en = sub;

        // These are calculated in the node of persistent centroid tree;
        N = N + U * K; 
        ct.assign(N, vector<int> (0));
        ans.assign(N, 0);
        contrib.assign(N, 0);
        cnt.assign(N, 0);
        id.assign(N, 0);

        compute();
        decompose();
    }
    void compute(int u = 1, int p = 0){
        sub[u] = 1;
        for(auto [v, w]: adj[u]) if(v != p){
            compute(v, u);
            sub[u] += sub[v];
        }
    }
    int centroid(int u, int p = 0){
        int tot = sub[u]; 
        for(auto [v, w]: adj[u]){
            if(v == p || blocked[v]) continue;
            if(2 * sub[v] > tot) {
                sub[u] = tot - sub[v];
                sub[v] = tot;
                return centroid(v, u);
            }
        }
        return u;
    }
    void getDis(int u, int p, int l, long long d){
        dis[u][l] = d;
        for(auto [v, w]: adj[u]){
            if(blocked[v] || v == p) continue;
            getDis(v, u, l, d + w);
        }
    }
    int decompose(int u = 1, int p = 0, int l = 1){
        u = centroid(u); 
        int cur = ++T;
        id[cur] = u; 
        blocked[u] = 1, level[u] = l, st[u] = T;
        getDis(u, p, l, 0); // precalculating distance from every node of subtree(u) to u / level of u 
        for(auto [v, w]: adj[u]) if(!blocked[v]){
            v = decompose(v, u, l + 1);
            ct[cur].push_back(v);
        }
        en[u] = T;
        return cur;
    }
    // check if v is in the subtree of u in centroid tree
    bool insub(int u, int v){
        return st[u] <= st[v] && en[v] <= en[u];
    }
    // traversing from root node to u;
    int update(int node, int u){ // cur is on persistent tree and u is on original tree
        int cur = ++T;
        id[cur] = id[node], ct[cur] = ct[node]; 
        ans[cur] = ans[node], contrib[cur] = contrib[node], cnt[cur] = cnt[node];
        ans[cur] += dis[u][level[id[cur]]], cnt[cur]++;
        for(auto &child: ct[cur]){
            if(insub(id[child], u)){
                child = update(child, u);
                contrib[child] += dis[u][level[id[cur]]];
            }
        }
        return cur;
    }
    // traversing from root node to u;
    long long query(int cur, int u){ // cur is on persistent tree and u is on original tree
        long long ret = 0;
        while(id[cur] != u){
            int next = 0;
            for(auto child: ct[cur]){
                if(insub(id[child], u)) next = child;
            }
            ret += ((ans[cur] - contrib[next]) + (dis[u][level[id[cur]]] * (cnt[cur] - cnt[next])));
            cur = next;
        }
        ret += ans[cur];
        return ret;
    }
};

void solve(int tc) {
    int n, q; cin>>n>>q;
    vector<int> p(n + 1);
    for(int i = 1;i <= n; i++) 
        cin>>p[i];
    Tree<pair<int, int>> tree(n);
    for(int i = 0, u, v, w; i < n - 1; i++){
        cin>>u>>v>>w;
        tree.addEdges(u, v, w);
    }

    tree = tree.binarize();
    PCD pcd(tree, n + q);
    vector<int> root(n + 1); root[0] = 1;
    for(int i = 1; i <= n; i++){
        root[i] = pcd.update(root[i - 1], p[i]);
    }
    LL m = (1LL << 30), ans = 0;
    while(q--){
        int t; cin>>t;
        if(t == 1){
            int l, r, v; cin>>l>>r>>v;
            l ^= (ans % m);
            r ^= (ans % m);
            v ^= (ans % m);
            ans = pcd.query(root[r], v) - pcd.query(root[l - 1], v);
            cout<<ans<<'\n';
        }else{
            int i; cin>>i;
            i ^= (ans % m);
            root[i] = pcd.update(root[i - 1], p[i + 1]);
            swap(p[i], p[i + 1]);
        }
    }
}

signed main(){
    faster
    int t = 1;
    // cin >> t;
    for(int tc = 1; tc <= t; tc++){
        solve(tc);
    }
    return 0;
}