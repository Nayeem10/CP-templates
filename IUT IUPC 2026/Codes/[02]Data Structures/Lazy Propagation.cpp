template <typename T, typename U>
struct LazySegmentTree {
  vector<T> tree;
  vector<U> lazy;
  int n;
  T I;
  function<T(T, T)> merge;
  void updateLazy(int id, U val) { lazy[id] += val; }
  void push(int id, int le, int ri) {
    tree[id] += (ri - le + 1) * lazy[id];
    if (le != ri) {
      updateLazy(2 * id + 1, lazy[id]);
      updateLazy(2 * id + 2, lazy[id]);
    }
    lazy[id] = 0;
  }
  void fix(int id) { tree[id] = merge(tree[2 * id + 1], tree[2 * id + 2]); }
  void build(int id, int le, int ri, vector<T>& arr) {
    if (le == ri) {
      tree[id] = arr[le];
      return;
    }
    int mid = (le + ri) / 2;
    build(2 * id + 1, le, mid, arr);
    build(2 * id + 2, mid + 1, ri, arr);
    fix(id);
  }
  void update(int id, int le, int ri, int l, int r, U val) {
    push(id, le, ri);
    if (r < le || l > ri) return;
    if (le >= l && ri <= r) {
      updateLazy(id, val), push(id, le, ri);
      return;
    }
    int mid = (le + ri) / 2;
    update(2 * id + 1, le, mid, l, r, val);
    update(2 * id + 2, mid + 1, ri, l, r, val);
    fix(id);
  }
  T query(int id, int le, int ri, int l, int r) {
    push(id, le, ri);
    if (r < le || l > ri) return I;
    if (l <= le && ri <= r) return tree[id];
    int mid = (le + ri) / 2;
    return merge(query(2 * id + 1, le, mid, l, r),
                 query(2 * id + 2, mid + 1, ri, l, r));
  }
  int findL(int id, int le, int ri, int l, int r, T val) {
    push(id, le, ri);
    if (r < le || l > ri) return r + 1;
    if (l <= le && ri <= r && tree[id] > val) return r + 1;
    if (le == ri) return le;

    int mid = (le + ri) / 2;
    int left = findL(2 * id + 1, le, mid, l, r, val);
    if (left <= r) return left;
    return findL(2 * id + 2, mid + 1, ri, l, r, val);
  }
 public:
  LazySegmentTree(vector<T>& arr, T I, function<T(T, T)> merge)
      : n(arr.size()), I(I), merge(merge) {
    tree.assign(4 * n, I);
    lazy.assign(4 * n, 0);
    build(0, 0, n - 1, arr);
  }
  LazySegmentTree(int n, T I, function<T(T, T)> merge)
      : n(n), I(I), merge(merge) {
    tree.assign(4 * n, I);
    lazy.assign(4 * n, 0);
  }
  void update(int l, int r, U val) { update(0, 0, n - 1, l, r, val); }
  T query(int l, int r) { return query(0, 0, n - 1, l, r); }
  int findL(int l, int r, T val) { return findL(0, 0, n - 1, l, r, val); }
};