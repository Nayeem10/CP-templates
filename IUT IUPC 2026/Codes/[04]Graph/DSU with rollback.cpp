struct Rollback_DSU {
  int n;
  vector <int> par, sz;
  vector <pair <int, int>> op;
  Rollback_DSU(int n) : par(n), sz(n, 1) {
    iota(par.begin(), par.end(), 0);
    op.reserve(n);
  }
  int Anc(int node) {
    for(; node != par[node]; node = par[node]);
    return node;
  }
  bool Unite(int x, int y) {
    x = Anc(x), y = Anc (y);
    if (x == y) return false;
    if(sz[x] < sz[y]) swap(x, y);
    op.emplace_back(x, y);
    par[y] = x;
    sz[x] += sz[y];
    return true;
  }
  void Undo(size_t t) {
    for(; op.size() > t; op.pop_back()) {
      par[op.back().second] = op.back().second;
      sz[op.back().first] -= sz[op.back().second];
    }
  }
};
