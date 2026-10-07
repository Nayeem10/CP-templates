template <class T, class L, T it, T (*mergeT)(T, T), T (*applyL)(T, L)>
struct SegTree {
  int n;
  vector<T> tree;
  void update(int pos, L val) {
    pos += n;
    tree[pos] = applyL(tree[pos], val);
    while (pos > 1) {
      pos >>= 1;
      tree[pos] = mergeT(tree[pos << 1], tree[pos << 1 | 1]);
    }
  }
  T query(int l, int r) {
    l += n, r += n + 1;
    T lft = it, ryt = it;
    while (l < r) {
      if (l & 1) lft = mergeT(lft, tree[l++]);
      if (r & 1) ryt = mergeT(tree[--r], ryt);
      l >>= 1;
      r >>= 1;
    }
    return mergeT(lft, ryt);
  }
  SegTree(vector<T>& v) : n(v.size()) {
    tree.assign(2 * n, it);

    for (int i = 0; i < n; i++) tree[i + n] = v[i];
    for (int i = n - 1; i > 0; i--)
      tree[i] = mergeT(tree[i << 1], tree[i << 1 | 1]);
  }
};
