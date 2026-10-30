const int N = 2E5 + 69;
int n;
// seg tree here
vector <int> adj[N];
int cur_pos;
bool WEIGHT_IN_EDGE = false;
int Parent[N], Depth[N], Heavy[N], Head[N], Pos[N]; 
int Start[N], End[N]; vector <int> Euler; /// ONLY NEEDED FOR SUBTREE QUERIES
void reset (bool WIE = false) {
  cur_pos = 0;
  WEIGHT_IN_EDGE = WIE;
  fill (Heavy, Heavy + n, -1);
  // build (vector <T> (n, I));
}
int dfs (int v = 0) {
  int size = 1, max_c_size = 0;
  for (int c : adj[v]) {
    if (c != Parent[v]) {
      Parent[c] = v;
      Depth[c] = Depth[v] + 1;
      int c_size = dfs(c);
      size += c_size;
      if (c_size > max_c_size) {
        max_c_size = c_size;
        Heavy[v] = c;
  } } }
  return size;
}
void decompose (int v = 0, int h = 0) {
  Head[v] = h; Pos[v] = cur_pos++;
  Euler.push_back(v);
  Start[v] = (int)Euler.size() - 1;
  if (Heavy[v] != -1) decompose(Heavy[v], h);
  for (int c : adj[v]) if (c != Parent[v] && c != Heavy[v]) decompose(c, c);
  End[v] = Euler.size() - 1;
}
void update_path (int a, int b, LL val) {
  while (Head[a] != Head[b]) {
    if (Depth[Head[a]] < Depth[Head[b]]) swap(a, b);
    update(Pos[Head[a]], Pos[a], val);
    a = Parent[Head[a]];
  }
  if (Depth[a] > Depth[b]) swap(a, b);
  update(Pos[a] + WEIGHT_IN_EDGE, Pos[b], val);
}
// LL query_path (int a, int b) {
//   LL res = 0;
//   while (Head[a] != Head[b]) {
//     if (Depth[Head[a]] < Depth[Head[b]]) swap(a, b);
//     res = merge (res, query(Pos[Head[a]], Pos[a]));
//     a = Parent[Head[a]];
//   }
//   if (Depth[a] > Depth[b]) swap(a, b);
//   res = merge (res, query(Pos[a] + WEIGHT_IN_EDGE, Pos[b]));
//   return res;
// }
vector <T> query_up(int u, int anc) {
  vector <T> res;
  while (Head[u] != Head[anc]) {
    res.emplace_back (query(Pos[Head[u]], Pos[u]));
    u = Parent[Head[u]];
  }
  res.emplace_back (query(Pos[anc] + 1, Pos[u]));
  return res;
}
LL query_path(int u, int v) {
  int w = LCA:: lca(u, v);
  auto left  = query_up(u, w); 
  auto right = query_up(v, w); 
  node res = I;
  for (auto e : left) res = merge (e, res);
  if (not WEIGHT_IN_EDGE) res = merge(query(Pos[w], Pos[w]), res);
  swap (res.AP, res.PA);
  auto res2 = I;
  for (auto e : right) res2 = merge (e, res2); 
  res = merge (res, res2);
  return max ({res.PP, res.PA, res.AP, res.AA});
}
void update_subtree (int v, LL val) { update(Start[v], End[v], val); }
LL query_subtree (int v) { return query(Start[v], End[v]); }
void HLD_initialize (vector<LL> &weight) {
  reset (true); Parent[0] = -1;
  dfs(); decompose();
  for (int i = 0; i < n; i++) update(Pos[i], Pos[i], weight[i]);
}
