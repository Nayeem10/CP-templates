class DSU {
  vector<int> parent, size;

 public:
  DSU(int n) : parent(n + 1), size(n + 1, 1) {
    iota(parent.begin(), parent.end(), 0);
  }
  int root(int u) {
    if (parent[u] == u) return u;
    return parent[u] = root(parent[u]);
  }
  bool same(int u, int v) { return root(u) == root(v); }
  void merge(int u, int v) {
    u = root(u), v = root(v);
    if (u == v) return;
    if (size[u] < size[v]) swap(u, v);
    parent[v] = u, size[u] += size[v];
  }
};
int kruskal(vector<tuple<int, int, int>> edges, int n) {
  sort(edges.begin(), edges.end());
  DSU mst(n);
  int cost = 0;
  for (auto& [w, u, v] : edges) {
    if (mst.same(u, v)) continue;
    mst.merge(u, v);
    cost += w;
  }
  return cost;
} /* PRIM'S SPANNING TREE (MST) */
DIJKSTRA code... start from a node,
    and push nodes which are not marked popped edges weight are taken