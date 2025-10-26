template<class T, class L, T it, L il, T(*mergeT)(T, T), T(*applyL)(T, L), L(*mergeL)(L, L)>
struct SegTree{
    int n, h;
    vector<T> tree; 
    vector<L> lazy;
 
    bool (*compLe)(T, T);
    bool (*compRi)(T, T);
 
    void apply(int id, L val){
        tree[id] = applyL(tree[id], val);
        if(id < n) lazy[id] = mergeL(lazy[id], val);
    }
    void pushUp(int id){
        while (id > 1) {
            id >>= 1, tree[id] = mergeT(tree[id << 1], tree[id << 1 | 1]);
            tree[id] = lazy[id] == il ? tree[id] : applyL(tree[id], lazy[id]);
        }
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
        l += n, r += n + 1;
        pushDown(l), pushDown(r - 1);
        for (int i = l, j = r; i < j; i >>= 1, j >>= 1) {
            if (i & 1) apply(i++, val);
            if (j & 1) apply(--j, val);
        }
        pushUp(l), pushUp(r - 1);
    }
 
    T query(int l, int r){
        l += n, r += n + 1;
        pushDown(l), pushDown(r - 1);
        T lft = it, ryt = it;
        for(int i = l, j = r; i < j; i >>= 1, j >>= 1){
            lft = (i & 1) ? mergeT(lft, tree[i++]) : lft;
            ryt = (j & 1) ? mergeT(tree[--j], ryt) : ryt;
        }
        return mergeT(lft, ryt);
    }
    int findL(int l, T val){
        l += n, pushDown(l), pushDown(2 * n - 1);
        int id = 2 * n;
        for(int i = l, j = 2 * n; i < j; i >>= 1, j >>= 1){
            if(i & 1 && compLe(tree[i++], val)) { id = i - 1; break; }
            if(j & 1 && compLe(tree[--j], val)) { id = j; }
        }
        while(id < n){
            int le = id << 1, ri = id << 1 | 1;
            if(lazy[id] != il){
                apply(le, lazy[id]);
                apply(ri, lazy[id]);
                lazy[id] = il;
            }
            id <<= 1;
            if(!compLe(tree[le], val)) id++;
        }
        return id - n;
    }
    int findR(int r, T val){
        r += n + 1, pushDown(n), pushDown(r - 1);
        int id = 2 * n;
        for(int i = n, j = r; i < j; i >>= 1, j >>= 1){
            if(i & 1 && compRi(tree[i++], val)) { id = i - 1; }
            if(j & 1 && compRi(tree[--j], val)) { id = j; break; }
        }
        while(id < n){
            int le = id << 1, ri = id << 1 | 1;
            if(lazy[id] != il){
                apply(le, lazy[id]);
                apply(ri, lazy[id]);
                lazy[id] = il;
            }
            id <<= 1;
            if(compRi(tree[ri], val)) id++;
        }
        if(id == 2 * n) id = n - 1;
        return id - n;
    }
    SegTree() {}
    SegTree(int n, bool (*compLe)(T, T), bool (*compRi)(T, T))
        : n(n), compLe(compLe), compRi(compRi) {
        h = 32 - __builtin_clz(n);
        tree.assign(2 * n, it);
        lazy.assign(n, il);
    }
    SegTree(vector<T> &v, bool (*compLe)(T, T), bool (*compRi)(T, T))
        : n(v.size()), compLe(compLe), compRi(compRi) {
        h = 32 - __builtin_clz(n);
        tree.assign(2 * n, it);
        lazy.assign(n, il);
 
        for(int i = 0; i < n; i++)
            tree[i + n] = v[i];
        for(int i = n - 1; i > 0; i--)
            tree[i] = mergeT(tree[i << 1], tree[i << 1 | 1]);
    }
};