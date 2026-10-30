const int N = 2000, L = 105;
struct AhoCorasick {
  int N, P;
  const int A = 256;
  vector<vector<int>> next;
  vector<int> link, out_link, end_in_pattern;
  vector<vector<int>> out;
  AhoCorasick() : N(0), P(0) { node(); }
  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back(0);
    end_in_pattern.emplace_back(0);
    return N++;
  }
  inline int get(char c) { return c; }
  int addPattern(const string T) {
    int u = 0;
    for (auto c : T) {
      if (!next[u][get(c)]) next[u][get(c)] = node();
      u = next[u][get(c)];
    }
    out[u].push_back(P);
    end_in_pattern[u] = 1;
    return P++;
  }
  void pushLinks() {
    queue<int> q;
    for (q.push(0); !q.empty();) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) next[u][c] = next[link[u]][c];
        else {
          link[v] = u ? next[link[u]][c] : 0;
          out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
          q.push(v);
        }
        end_in_pattern[v] |= end_in_pattern[out_link[v]];
  } } }
  int advance(int u, char c) {
    while (u && !next[u][get(c)]) u = link[u];
    u = next[u][get(c)]; return u;
} };
