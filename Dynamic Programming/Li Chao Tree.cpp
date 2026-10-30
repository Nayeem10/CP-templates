template<typename T = LL>
struct LiChao {
    struct Line {
        T m, c;
        T eval(LL x) const { return (T) m * x + c; }
    };
    struct Node { Line ln; int lc = 0, rc = 0; };

    LL L, R;
    T it;
    int sz = 0, root = 0;
    vector<Node> t;

    // Use lowest() instead of min() so it correctly defaults to -INF for both ints and doubles
    LiChao(LL L, LL R, int q, T inf_val = numeric_limits<T>::lowest() / 2)
        : L(L), R(R), it(inf_val) {
        int depth = 64 - __builtin_clzll(max(1LL, R - L + 1));
        t.resize(q * 4 * depth + 5);
    }

    void add(int &u, LL l, LL r, LL ql, LL qr, Line nw) {
        if (!u) { u = ++sz; t[u].ln = {0, it}; }
        LL m = l + (r - l) / 2;
        if (ql <= l && r <= qr) {
            bool lef = nw.eval(l) > t[u].ln.eval(l);
            bool mid = nw.eval(m) > t[u].ln.eval(m);
            if (mid) swap(t[u].ln, nw);
            if (l == r || nw.c <= it) return; // Prune unallocated dummy -INF line
            if (lef != mid) add(t[u].lc, l, m, ql, qr, nw);
            else            add(t[u].rc, m + 1, r, ql, qr, nw);
            return;
        }
        if (ql <= m) add(t[u].lc, l, m, ql, qr, nw);
        if (qr > m)  add(t[u].rc, m + 1, r, ql, qr, nw);
    }

    T merge(T a, T b) const { return max(a, b); }

    T query(int u, LL l, LL r, LL x) {
        if (!u) return it;
        T ans = t[u].ln.eval(x);
        if (l == r) return ans;
        LL m = l + (r - l) / 2;
        return merge(ans, x <= m ? query(t[u].lc, l, m, x) : query(t[u].rc, m + 1, r, x));
    }

    void add_segment(Line nw, LL l, LL r) { add(root, L, R, l, r, nw); }
    T query(LL x) { return query(root, L, R, x); }
};