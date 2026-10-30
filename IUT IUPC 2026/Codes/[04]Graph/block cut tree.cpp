const int N = 4e5 + 1;
bitset<N> art;
vector<int> g[N], tree[N], st, comp[N];
int n, ptr, cur, in[N], low[N], id[N];
void memclear() {
  for (int i = 1; i <= n; i++) {
    g[i].clear(); in[i] = low[i] = art[i] = 0;
  }
  for (int i = 1; i <= ptr; i++) {
    tree[i].clear(); comp[i].clear();
  }
  st.clear();
  ptr = cur = 0;
}
void dfs(int u, int from = -1) {
  in[u] = low[u] = ++ptr;
  st.emplace_back(u);
  for (int v : g[u])
    if (v ^ from) {
      if (!in[v]) {
        dfs(v, u); low[u] = min(low[u], low[v]);
        if (low[v] >= in[u]) {
          art[u] = ~from or in[v] > in[u] + 1;
          comp[++cur].emplace_back(u);
          while (comp[cur].back() ^ v) {
            comp[cur].emplace_back(st.back()); st.pop_back();
          } }
      } else low[u] = min(low[u], in[v]);
    }
}
void build_tree() {
  ptr = 0;
  for (int i = 1; i <= n; ++i)
    if (art[i]) id[i] = ++ptr;
  for (int i = 1; i <= cur; ++i) {
    int x = ++ptr;
    for (int u : comp[i]) {
      if (art[u]) {
        tree[x].emplace_back(id[u]); tree[id[u]].emplace_back(x);
      } else id[u] = x;
    } }
}
