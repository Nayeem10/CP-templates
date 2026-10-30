const int K = lg(N) + 1;
vector<int> adj[N];
int anc[N][K], lvl[N];
namespace lca {
  void init(int u = 1, int p = 0, int d = 0) {
    lvl[u] = d;
    anc[u][0] = p;
    for (int i = 1; i < K; i++)
      anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (auto v : adj[u])
      if (v != p)
        init(v, u, d + 1);
  }
  int getAnc(int u, int k) {
    for (int i = 0; u and i < K; i++)
      if ((k >> i) & 1)
        u = anc[u][i];
    return u;
  }
  int lca(int u, int v) {
    if (lvl[u] < lvl[v]) swap(u, v);
    u = getAnc(u, lvl[u] - lvl[v]);
    if (u == v) return u;
    for (int i = K - 1; ~i; i--)
      if (anc[u][i] != anc[v][i])
        u = anc[u][i], v = anc[v][i];
    return anc[u][0];
  }
  int dist(int u, int v) {
    return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];
  }
};