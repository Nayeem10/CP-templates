class CD {
  vector<vector<int>> adj;
  vector<int> sub;
  vector<bool> blocked;
  int N;
 public:
  CD(vector<vector<int>> adj) : adj(adj) {
    N = tree.adj.size() - 1;
    blocked.assign(N + 1, 0);
    sub.assign(N + 1, 0);
    compute();
  }
  void compute(int u = 1, int p = 0) {
    sub[u] = 1;
    for (auto v : adj[u])
      if (v != p) {
        compute(v, u);
        sub[u] += sub[v];
      }
  }
  int centroid(int u, int p = 0) {
    int tot = sub[u];
    for (auto v : adj[u]) {
      if (v == p || blocked[v]) continue;
      if (2 * sub[v] > tot) {
        sub[u] = tot - sub[v];
        sub[v] = tot;
        return centroid(v, u);
      }
    }
    return u;
  }
  int count(int u, int p) { /* calculate ans */ }
  void update(int u, int p) { /* update */ }
  int decompose(int u = 1) {
    u = centroid(u);
    blocked[u] = 1;
    int ans = 0;
    /////   Do something here    //// count() update()
    for (auto v : adj[u])
      if (!blocked[v]) {
        ans += count(v, u);
        update(v, u);
      }
    /// reset updates here
    for (auto v : adj[u])
      if (!blocked[v])
        decompose(v);
    return ans;
  }
};