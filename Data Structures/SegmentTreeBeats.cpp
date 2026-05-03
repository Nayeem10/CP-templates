class SegTreeBeats {
    const int INF = INT_MAX;
    const LL NEG_INF = LLONG_MIN;

    vector<LL> mx, mn, smx, smn, sum, add;
    vector<int> mxcnt, mncnt;
    int L, R;

    void applyMax(int u, LL x) {
        sum[u] += mncnt[u] * (x - mn[u]);
        if (mx[u] == mn[u]) mx[u] = x;
        if (smx[u] == mn[u]) smx[u] = x;
        mn[u] = x;
    }

    void applyMin(int u, LL x) {
        sum[u] -= mxcnt[u] * (mx[u] - x);
        if (mn[u] == mx[u]) mn[u] = x;
        if (smn[u] == mx[u]) smn[u] = x;
        mx[u] = x;
    }

    void applyAdd(int u, LL x, int tl, int tr) {
        sum[u] += (tr - tl + 1) * x;
        add[u] += x;
        mx[u] += x, mn[u] += x;
        if (smx[u] != NEG_INF) smx[u] += x;
        if (smn[u] != INF) smn[u] += x;
    }

    void push(int u, int tl, int tr) {
        int lft = u << 1, ryt = lft | 1, mid = (tl + tr) >> 1;
        if (add[u] != 0) {
            applyAdd(lft, add[u], tl, mid);
            applyAdd(ryt, add[u], mid + 1, tr);
            add[u] = 0;
        }
        if (mx[u] < mx[lft]) applyMin(lft, mx[u]);
        if (mx[u] < mx[ryt]) applyMin(ryt, mx[u]);

        if (mn[u] > mn[lft]) applyMax(lft, mn[u]);
        if (mn[u] > mn[ryt]) applyMax(ryt, mn[u]);
    }

    void merge(int u) {
        int lft = u << 1, ryt = lft | 1;
        sum[u] = sum[lft] + sum[ryt];

        mx[u] = max(mx[lft], mx[ryt]);
        smx[u] = max(smx[lft], smx[ryt]);
        if (mx[lft] != mx[ryt]) smx[u] = max(smx[u], min(mx[lft], mx[ryt]));
        mxcnt[u] = (mx[u] == mx[lft]) * mxcnt[lft] + (mx[u] == mx[ryt]) * mxcnt[ryt];

        mn[u] = min(mn[lft], mn[ryt]);
        smn[u] = min(smn[lft], smn[ryt]);
        if (mn[lft] != mn[ryt]) smn[u] = min(smn[u], max(mn[lft], mn[ryt]));
        mncnt[u] = (mn[u] == mn[lft]) * mncnt[lft] + (mn[u] == mn[ryt]) * mncnt[ryt];
    }

    void build(const vector<int> &a, int tl, int tr, int u) {
        if (tl == tr) {
            sum[u] = mn[u] = mx[u] = a[tl];
            mxcnt[u] = mncnt[u] = 1;
            smx[u] = NEG_INF;
            smn[u] = INF;
            return;
        }
        int mid = (tl + tr) >> 1, lft = u << 1, ryt = lft | 1;
        build(a, tl, mid, lft);
        build(a, mid + 1, tr, ryt);
        merge(u);
    }

public:
    SegTreeBeats(const vector<int> &a) {
        int n = a.size();
        L = 0;
        R = n - 1;

        mx.resize(4 * n, 0);
        mn.resize(4 * n, 0);
        smx.resize(4 * n, NEG_INF);
        smn.resize(4 * n, INF);
        sum.resize(4 * n, 0);
        add.resize(4 * n, 0);
        mxcnt.resize(4 * n, 0);
        mncnt.resize(4 * n, 0);

        build(a, L, R, 1);
    }
    // a[i] = min(x, a[i]);
    void minimize(int l, int r, LL x) {
        minimize(l, r, x, L, R, 1);
    }
    // a[i] = max(x, a[i]);
    void maximize(int l, int r, LL x) {
        maximize(l, r, x, L, R, 1);
    }
    // a[i] = a[i] + x;
    void increase(int l, int r, LL x) {
        increase(l, r, x, L, R, 1);
    }

    LL getSum(int l, int r) {
        return getSum(l, r, L, R, 1);
    }

    LL getMax(int l, int r) {
        return getMax(l, r, L, R, 1);
    }


private:
    void minimize(int l, int r, LL x, int tl, int tr, int u) {
        if (l > tr || tl > r || mx[u] <= x) return;
        if (l <= tl && tr <= r && smx[u] < x) {
            applyMin(u, x);
            return;
        }
        push(u, tl, tr);
        int mid = (tl + tr) >> 1, lft = u << 1, ryt = lft | 1;
        minimize(l, r, x, tl, mid, lft);
        minimize(l, r, x, mid + 1, tr, ryt);
        merge(u);
    }

    void maximize(int l, int r, LL x, int tl, int tr, int u) {
        if (l > tr || tl > r || mn[u] >= x) return;
        if (l <= tl && tr <= r && smn[u] > x) {
            applyMax(u, x);
            return;
        }
        push(u, tl, tr);
        int mid = (tl + tr) >> 1, lft = u << 1, ryt = lft | 1;
        maximize(l, r, x, tl, mid, lft);
        maximize(l, r, x, mid + 1, tr, ryt);
        merge(u);
    }

    void increase(int l, int r, LL x, int tl, int tr, int u) {
        if (l > tr || tl > r) return;
        if (l <= tl && tr <= r) {
            applyAdd(u, x, tl, tr);
            return;
        }
        push(u, tl, tr);
        int mid = (tl + tr) >> 1, lft = u << 1, ryt = lft | 1;
        increase(l, r, x, tl, mid, lft);
        increase(l, r, x, mid + 1, tr, ryt);
        merge(u);
    }

    LL getSum(int l, int r, int tl, int tr, int u) {
        if (l > tr || tl > r) return 0;
        if (l <= tl && tr <= r) return sum[u];
        push(u, tl, tr);
        int mid = (tl + tr) >> 1, lft = u << 1, ryt = lft | 1;
        return getSum(l, r, tl, mid, lft) + getSum(l, r, mid + 1, tr, ryt);
    }

    LL getMax(int l, int r, int tl, int tr, int u) {
        if (l > tr || tl > r) return NEG_INF;
        if (l <= tl && tr <= r) return mx[u];
        push(u, tl, tr);
        int mid = (tl + tr) >> 1;
        return max(getMax(l, r, tl, mid, u << 1),
                   getMax(l, r, mid + 1, tr, (u << 1) | 1));
    }

};