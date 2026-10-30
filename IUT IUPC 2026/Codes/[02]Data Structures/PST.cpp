// this calculates xor/xor_hash of all the element less than 'x' in [0, i].
// query is a walk function
class PST {
#define lc(u) tree[u].left
#define rc(u) tree[u].right;
  struct node {
    int left = 0, right = 0, val = 0;
  };
  node* tree;
  int N, LG, time = 0, I = 0;

  node create(int l, int r) { return {l, r, merge(tree[l].val, tree[r].val)}; }
  int merge(LL a, LL b) { return a ^ b; }
  int build(int le, int ri) {
    int id = ++time;
    if (le == ri) return tree[id] = node(), id;
    int m = (le + ri) / 2;
    return tree[id] = create(build(le, m), build(m + 1, ri)), id;
  }
  int update(int id, int le, int ri, int pos, int val) {
    int nid = ++time;
    if (le == ri)
      return tree[nid] = {0, 0, (tree[id].val ^ val)}, nid;  // change here
    int m = (le + ri) / 2;
    if (pos <= m) {
      tree[nid] =
          create(update(tree[id].left, le, m, pos, val), tree[id].right);
    } else {
      tree[nid] =
          create(tree[id].left, update(tree[id].right, m + 1, ri, pos, val));
    }
    return nid;
  }
  int query(int id, int di, int le, int ri) {
    if (tree[id].val == tree[di].val) return 0;
    if (le == ri) return le;
    int m = (le + ri) >> 1;
    if (tree[tree[id].left].val != tree[tree[di].left].val)
      return query(tree[id].left, tree[di].left, le, m);
    return query(tree[id].right, tree[di].right, m + 1, ri);
  }

 public:
  PST(int N, int U) {  // U --> number of expected updates
    this->N = N;
    LG = 33 - __builtin_clz(N);
    tree = new node[N * 4 + U * LG];
    build(0, N - 1);
  }
  int update(int id, int pos, int val) {
    return update(id, 0, N - 1, pos, val);
  }
  int query(int id, int di) { return query(id, di, 0, N - 1); }
  ~PST() { delete[] tree; }
};