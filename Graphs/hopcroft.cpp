// do everything 1-based 
class BipartiteMatcher {
 private:
  int n, m;                // Number of vertices in left and right sets
  vector<vector<int>> adj; // Adjacency list for the bipartite graph
  vector<int> dist;        // Distance array for BFS
  // matchL[u] is the right vertex matched with u; 
  // matchR[v] is the left vertex matched with v
 public:
  vector<int> matchL, matchR;
  BipartiteMatcher(int n, int m) : n(n), m(m) {
    adj.resize(n + 1);
    matchL.resize(n + 1, 0);
    matchR.resize(m + 1, 0);
    dist.resize(n + 1);
  }
  void addEdge(int u, int v) { adj[u].push_back(v); }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (matchL[u] == 0) {
        dist[u] = 0;
        q.push(u);
      } else {
        dist[u] = INT_MAX;
      }
    }
    dist[0] = INT_MAX;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (dist[u] < dist[0]) {
        for (int v : adj[u]) {
          if (dist[matchR[v]] == INT_MAX) {
            dist[matchR[v]] = dist[u] + 1;
            q.push(matchR[v]);
          }
        }
      }
    }
    return dist[0] != INT_MAX;
  }
  bool dfs(int u) {
    if (u != 0) {
      for (int v : adj[u]) {
        if (dist[matchR[v]] == dist[u] + 1 and dfs(matchR[v])) {
          matchL[u] = v; matchR[v] = u;
          return true;
        }
      }
      dist[u] = INT_MAX;
      return false;
    }
    return true;
  }
  int hopcroftKarp() {
    int matching = 0;
    while (bfs())
      for (int u = 1; u <= n; u++)
        if (matchL[u] == 0 && dfs(u)) matching++;
    return matching;
  }
};
