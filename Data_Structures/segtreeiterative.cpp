
template<typename T, typename L>
struct LazySegTree{
    int n, h;
    vector<T> tree; 
    vector<L> lazy;
    T it; L il;

    function<T(T, T)> mergeT;
    function<L(L, L)> mergeL;
    function<T(T, L)> applyL;

    void apply(int id, L val){
        tree[id] = applyL(tree[id], val);
        if(id < n) lazy[id] = mergeL(lazy[id], val);
    }
    void pushUp(int id){
        while (id > 1) 
            id >>= 1, tree[id] = applyL(mergeT(tree[id << 1], tree[id << 1 | 1]), lazy[id]);
    }
    void pushDown(int id){
        for(int i = h; i > 0; i--){
            int pid = (id >> i);
            if(lazy[pid] == il) continue;
            apply(pid << 1, lazy[pid]);
            apply(pid << 1 | 1, lazy[pid]);
            lazy[pid] = il;
        }
    }

    void update(int l, int r, L val){
        l += n, r += n;
        for (int i = l, j = r; i < j; i >>= 1, j >>= 1) {
            if (i & 1) apply(i++, val);
            if (j & 1) apply(--j, val);
        }
        pushUp(l), pushUp(r - 1);
    }

    T query(int l, int r){
        l += n, r += n;
        pushDown(l), pushDown(r - 1);
        T ans = it;
        for(int i = l, j = r; i < j; i >>= 1, j >>= 1){
            if(i & 1) ans = mergeT(ans, tree[i++]);
            if(j & 1) ans = mergeT(ans, tree[--j]);
        }
        return ans;
    }

    LazySegTree(vector<T> &v, T it, L il,
     	function<T(T, T)> mergeT, 
     	function<L(L, L)> mergeL, 
     	function<T(T, L)> applyL)
        : n(v.size()), it(it), il(il), 
        mergeT(mergeT), mergeL(mergeL), applyL(applyL) {
		
		h = 32 - __builtin_clz(n);
        tree.assign(2 * n, it);
        lazy.assign(n, il);
        for(int i = 0; i < n; i++)
            tree[i + n] = v[i];
        for(int i = n - 1; i > 0; i--)
            tree[i] = mergeT(tree[i << 1], tree[i << 1 | 1]);
    }
};

void solve(int tc){
    int n, m; cin >> n >> m;
    vector<pair<LL, LL>> a(n, {0, 1});

    auto mergeT = [&](pair<LL, LL> a, pair<LL, LL> b) -> pair<LL, LL> {
        return {a.first + b.first, a.second + b.second};
    };
    auto mergeL = [&](LL a, LL b) -> LL {
        return a + b;
    };
    auto applyL = [&](pair<LL, LL> a, LL b) -> pair<LL, LL> {
        return {a.first + b * a.second, a.second};
    };

    LazySegTree<pair<LL, LL>, LL> lztree(a, {0, 0}, 0, mergeT, mergeL, applyL);
    for(int i = 0; i < m; i++){
        int t, l, r; cin >> t >> l >> r;
        if(t == 1){
            int v; cin >> v;
            lztree.update(l, r, v);
        }else{
            cout << lztree.query(l, r).first << '\n';
        }
    }
}