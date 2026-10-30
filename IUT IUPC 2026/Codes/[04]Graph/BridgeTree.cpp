vector<PLL> g[N];
vector<int> ng[N];
int disc[N], low[N], mark[N], vis[N], timer = 1;
void find_bridge(int u, int p) {
  disc[u] = low[u] = timer++;
  bool fl = 1;
  for (auto [v, id] : g[u]) {
    if (v == p && fl) {
      fl = 0; continue;
    }
    if (disc[v]) {
      low[u] = min(low[u], disc[v]);
    } else {
      find_bridge(v, u);
      low[u] = min(low[u], low[v]);
      if (disc[u] < low[v]) mark[id] = 1;
    }
  }
}
void colorComponents(int u, int color) {
  if (vis[u]) return;
  vis[u] = color;
  for (auto [v, id] : g[u]) {
    if (mark[id]) continue;
    colorComponents(v, color);
  }
}
void solve() {
  int n, m;
  cin >> n >> m;
  vector<PLL> edges;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    edges.push_back({u, v});
    g[u].push_back({v, i});
    g[v].push_back({u, i});
  }
  find_bridge(1, 0);
  int color = 1;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) colorComponents(i, color++);
  }
  for (int i = 0; i < m; i++) {
    if (mark[i]) {
      ng[vis[edges[i].first]].push_back(vis[edges[i].second]);
      ng[vis[edges[i].second]].push_back(vis[edges[i].first]);
    }
  }
}