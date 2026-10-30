struct node { LL l, r, idx; };
bool cmp(const node &x, const node &y) { 
  return x.r < y.r; 
}
LL curr = 0, BLOCK_SIZE, m;
vector<node> query[M];
vector<LL> mp(N, 0);
void add(LL x) {
  if(!mp[x]) curr++;
  mp[x]++;
}
void diminish(LL x) {
  mp[x]--;
  if(!mp[x]) curr--;
}
void solve() {
  int n, q; cin >> n >> q;
  vector<int> v(n), answer(q);
  for(int &i : v) cin >> i;
  BLOCK_SIZE = sqrt(n) + 1, m = 0;
  for(int i=0;i<q;i++) {
    LL x, y; cin >> x >> y; x--; y--;
    query[x / BLOCK_SIZE].push_back({x, y, i});
    m = max(m, x / BLOCK_SIZE);
  }
  for(int i=0;i<=m;i++) sort(all(query[i]), cmp);
  LL mo_left = 0, mo_right = -1;
  for(int i=0;i<=m;i++) {
    for(auto cur : query[i]) {
      LL left = cur.l, right = cur.r, id = cur.idx;
      while(mo_right < right) add(v[++mo_right]);
      while(mo_right > right) diminish(v[mo_right--]);
      while(mo_left < left) diminish(v[mo_left++]);
      while(mo_left > left) add(v[--mo_left]);
      answer[id] = curr;
    }
  }
  for(int i=0;i<q;i++) cout << answer[i] << '\n';
}