1. KRUSKALS SPANNING TREE (MST)
struct info {
  int u, v, w;
};
int parent[N], sz[N];
void initialize(int n) {
  for(int i=0;i<=n;i++) {
    parent[i] = i;
    sz[i] = 1;
  }
}
int root(int x) {
  if(parent[x] == x) return x;
  return parent[x] = root(parent[x]);
}
void merge(int x, int y) {
  int p = root(x);
  int q = root(y);
  if(sz[p] > sz[q]) {
    parent[p] = parent[q];
    sz[p] += sz[q];
    sz[q] = 0;
  }
  else {
    parent[q] = parent[p];
    sz[q] += sz[p];
    sz[p] = 0;
  }
}
// v should be already sorted according to weight
LL kruskal(int n, vector<info> &v) {
  initialize(n);
  LL cost = 0;
  for(auto cur : v) {
    if(root(cur.u) != root(cur.v)) {
      cost += cur.w;
      merge(cur.u, cur.v);
    }    
  }
  return cost;
}
// PRIM'S SPANNING TREE (MST)
bool marked[N];
vector<PII> adj[N]; // adj[from] -> {weight, to}

int prim(int n, int src) {
  for(int i=1;i<=n;i++) marked[i] = false;
  priority_queue<PII, vector<PII>, greater<PII> > pq;
  int cost = 0;
  pq.push({0, src});
  while(!pq.empty()) {
    PII cur = pq.top(); pq.pop();
    if(marked[cur.second]) continue;
    cost += cur.first;
    marked[cur.second] = true;
    cc++;
    for(auto next : adj[cur.second]) {
      if(!marked[next.second]) pq.push(next);
    }
  }
  return cost;
}
2.Dijkstra
struct node {
  int to;
  LL weight;
  bool operator<(const node &a) const {
    return weight > a.weight;
  }
};
vector<node> adj[N];
void dijkstra(int src, vector<LL> &dist, vector<int> &parent) {
  parent.assign(n + 1, -1);
  priority_queue<node> pq;
  pq.push({src, 0});
  dist[src] = 0;
  parent[src] = -1;
  while(!pq.empty()) {
    auto cur = pq.top(); pq.pop();
    for(auto next : adj[cur.to]) {
      if(dist[next.to] > dist[cur.to] + next.weight) {
        dist[next.to] = dist[cur.to] + next.weight;
        pq.push({next.to, dist[next.to]});
        parent[next.to] = cur.to;
      }
    }
  }
}

3. STRONGLY CONNECTED COMPONENT - KORASAJU ALGORITHM
vii adj[MAXN], rev_adj[MAXN], components[MAXN];
vii visited(MAXN), toposorted;
ll cnt = 0;
void dfs(ll now)
{
  visited[now] = 1;
  for(auto next : adj[now]) {
      if(!visited[next]) dfs(next);
  }
  toposorted.pb(now);
}
void dfs2(ll now){
  visited[now] = 1;
  components[cnt].pb(now);
  for(auto next : rev_adj[now]) {
      if(!visited[next]) dfs(next);
  }
}
void strongly_connected_component(ll n, ll m){
  visited.assign(n + 1, 0);
  for(ll i=0;i<m;i++) {
    ll a, b; cin >> a >> b;
    adj[a].pb(b);
    rev_adj[b].pb(a);
  }
  for(ll i=1;i<=n;i++) {
      if(!visited[i]) dfs(i);
  }
  reverse(all(toposorted));
  visited.assign(n + 1, 0);
  for(auto now : toposorted) {
      if(!visited[now]) {
          dfs2(now); cnt++;
      }
  }
}
4. K th shortest path
void K_shortest(int n,int m){
	int st,des,k,u,v;
	LL w;
	scanf("%d%d%d", &st,&des,&k);
	st--,des--;
	vector <vector<pii > > edges(n);
	for(int i=0;i<m;i++){
		scanf("%d%d%lld", &u,&v,&w);
		u--,v--;
		edges[u].push_back({w,v});
	}
	vector < vector <LL> > dis(n,vector <LL> (k+1,1e8));
	vector <int> vis(n); 
	priority_queue <pii ,vector <pii >, greater< pii > > q;

	q.emplace(0LL,st);
	while(!q.empty()){
		v = q.top().second, w = q.top().first;
		q.pop();
		if(vis[v]>=k) continue;
		// for the varient, check if this path is greater than previous, if not, continue
		//if(vis[v]>0 && w == dis[v][vis[v]-1]) continue; 
		dis[v][vis[v]] = w; 
		vis[v]++;
		for(auto nd:edges[v]){
			q.emplace(w+nd.first,nd.second);
		}
	}
	LL ans = dis[des][k-1];
	if(ans==1e8) ans = -1;
	printf("%lld\n", ans);
}
5. LCA Related
using vec = vector <int>;
using mat = vector <vector <int>>;
namespace ta {
  int time;
  void dfs(int u, int p, vec &par, vec &lvl, Tree &T) {
    for(int e: T[u]) {
      int v = T(e).to(u);
      if(v == p) continue;
      par[v] = u, lvl[v] = lvl[u] + 1;
      dfs(v, u, par, lvl, T);
    }
  }
  mat ancestorTable(vec &par) {
    int n = par.size(), sz = __lg(n) + 1;
    mat anc(sz, par);
    for(int k = 1; k < sz; k++) {
      for(int i = 0; i < n; i++) {
          anc[k][i] = anc[k - 1][anc[k - 1][i]];
      }
    }
    return anc;
  }
  int getAncestor(int u, int ht, mat &anc) {
    int sz = anc.size();
    for (int k = 0; k < sz; k++) {
        if (ht >> k & 1) u = anc[u][k];
    }
    return u;
  }
  bool isAncestor(int u, int par, vec &st, vec &en) {
      return st[par] <= st[u] and en[par] >= en[u];
  }
  int subtreeSize(int u, vec &st, vec &en) {
      return en[u] - st[u] + 1 >> 1;
  }
  int lca(int u, int v, vec &lvl, mat &anc) {
    if (lvl[u] > lvl[v]) swap(u, v);
    for (int k = anc.size() - 1; ~k; k--) {
        if (lvl[u] + (1 << k) <= lvl[v]) v = anc[k][v];
    }
    if (u == v) return u;
    for (int k = anc.size() - 1; ~k; k--) {
        if (anc[k][u] != anc[k][v]) u = anc[k][u], v = anc[k][v];
    }
    return anc[0][u];
  }
  int dis(int u, int v, vec &lvl, mat &anc) {
    int g = lca(u, v, lvl, anc);
    return lvl[u] + lvl[v] - 2 * lvl[g];
  }
}
6.
void bellmanford(int n, int m, vector<int> edge[], int dist[], int src){
  fill(dist, dist + n, INT_MAX);
  dist[src] = 0;
  int i, j, k;
  vector<int> v;
  for (i = 0; i < n; i++){
    for (j = 0; j < m; j++) {
      v = edge[j];
      if (dist[v[1]] > dist[v[0]] + v[2])
        dist[v[1]] = dist[v[0]] + v[2];
    }
  }
  for (j = 0; j < m; j++){ // For checking negative loop
      v = edge[j];
      if (dist[v[1]] > dist[v[0]] + v[2]){
          fill(dist, dist + n, INT_MIN); // Negative loop detected 
          return;
      }
  }
}

