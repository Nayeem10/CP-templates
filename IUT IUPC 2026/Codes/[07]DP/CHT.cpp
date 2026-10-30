struct Line {
  mutable LL m, c, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(LL x) const { return p < x; }
};
/* this calculates maximum value of m * x + c over all lines */
/* to get minimum value use m = -m , c = -c , query(x) = -query(x) */
struct LineContainer : multiset<Line, less<>> {
  /* (for doubles, use inf = 1/.0, div(a,b) = a/b) */
  static const LL inf = LLONG_MAX;
  LL div(LL a, LL b) { /* floored division */
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->m == y->m)
      x->p = x->c > y->c ? inf : -inf;
    else
      x->p = div(y->c - x->c, x->m - y->m);
    return x->p >= y->p;
  }
  void add(LL m, LL c) {
    auto z = insert({m, c, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  LL query(LL x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.c;
  }
};
