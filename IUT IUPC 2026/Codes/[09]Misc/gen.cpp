mt19937 rng(random_device{}());
LL randomInt(LL low, LL high) {
  uniform_int_distribution<LL> dist(low, high);
  return dist(rng);
}
vector<pair<int, int>> generate_random_tree(int n) {
  vector<int> prufer(n - 2);
  for (int i = 0; i < n - 2; ++i) prufer[i] = randomInt(1, n);
  vector<int> degree(n + 1, 1);
  for (int x : prufer) degree[x]++;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 1; i <= n; ++i)
    if (degree[i] == 1) pq.push(i);
  vector<pair<int, int>> edges;
  for (int x : prufer) {
    int leaf = pq.top();
    pq.pop();
    edges.emplace_back(leaf, x);
    degree[leaf]--, degree[x]--;
    if (degree[x] == 1) pq.push(x);
  }
  int u = pq.top(); pq.pop();
  int v = pq.top(); pq.pop();
  edges.emplace_back(u, v);
  return edges;
}
vector<int> permutation(int n) {
  vector<int> p(n); iota(p.begin(), p.end(), 1);
  shuffle(p.begin(), p.end(), rng);
  return p;
}