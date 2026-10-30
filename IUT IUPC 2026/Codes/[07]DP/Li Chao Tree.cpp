struct Line {
  double m, c;
  double eval(double x) { return m * x + c; }
};
struct node {
  Line line;
  node* left = nullptr;
  node* right = nullptr;
  node(Line line) : line(line) {}
  void add_segment(Line nw, LL l, LL r, LL L, LL R) {
    if (l > r || r < L || l > R) return;
    LL m = (l + 1 == r ? l : (l + r) / 2);
    if (l >= L and r <= R) {
      bool lef = nw.eval(l) < line.eval(l);
      bool mid = nw.eval(m) < line.eval(m);
      if (mid) swap(line, nw);
      if (l == r) return;
      if (lef != mid) {
        if (left == nullptr)
          left = new node(nw);
        else
          left->add_segment(nw, l, m, L, R);
      } else {
        if (right == nullptr)
          right = new node(nw);
        else
          right->add_segment(nw, m + 1, r, L, R);
      }
      return;
    }
    if (max(l, L) <= min(m, R)) {
      if (left == nullptr) left = new node({0, inf});
      left->add_segment(nw, l, m, L, R);
    }
    if (max(m + 1, L) <= min(r, R)) {
      if (right == nullptr) right = new node({0, inf});
      right->add_segment(nw, m + 1, r, L, R);
    }
  }
  double query_segment(LL x, LL l, LL r, LL L, LL R) {
    if (l > r || r < L || l > R) return inf;

    double ans = line.eval(x);
    if (l == r) return ans;

    LL m = (l + r) >> 1;

    if (x <= m && left) ans = min(ans, left->query_segment(x, l, m, L, R));
    if (x > m && right) ans = min(ans, right->query_segment(x, m + 1, r, L, R));

    return ans;
  }
};
struct LiChaoTree {
  LL L, R;
  node* root;
  LiChaoTree(LL L, LL R) : L(L), R(R) { root = new node({0, inf}); }
  void add_segment(Line line, LL l, LL r) {
    root->add_segment(line, L, R, l, r);
  }
  double query(LL x) { return root->query_segment(x, L, R, L, R); }
};

void solve(int tc) {
  int n;
  cin >> n;
  LiChaoTree tree(-INF, INF);
  for (int i = 0; i < n; i++) {
    LL x, v;
    cin >> x >> v;
    double m = -1.0 / v, c = 1.0 * x / v;
    tree.add_segment({m, c}, -INF, x);
    tree.add_segment({-m, -c}, x, INF);
  }
  int q;
  cin >> q;
  while (q--) {
    char t;
    cin >> t;
    if (t == '+') {
      LL x, v;
      cin >> x >> v;
      double m = -1.0 / v, c = 1.0 * x / v;
      tree.add_segment({m, c}, -INF, x);
      tree.add_segment({-m, -c}, x, INF);
    } else {
      LL x;
      cin >> x;
      cout << fixed << setprecision(9) << tree.query(x) << '\n';
    }
  }
}