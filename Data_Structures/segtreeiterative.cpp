// https://codeforces.com/contest/2145/problem/E
#include <bits/stdc++.h> 
using namespace std;
 
#define PLL pair<long long, long long>
#define LL long long

#define faster { ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); }
#define all(v) v.begin(), v.end()

const int N = 500 + 7;
const LL mod = 1e9 + 7;
const LL INF = 1e17 + 10;
const int inf = 1e9 + 10;

template<typename T, typename L>
struct SegTree{
    int n, h;
    vector<T> tree; 
    vector<L> lazy;
    T it; L il;

    function<T(T, T)> mergeT;
    function<L(L, L)> mergeL;
    function<T(T, L)> applyL;
    function<bool(T, T)> compLe;
    function<bool(T, T)> compRi;

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
            if(i & 1) lft = mergeT(lft, tree[i++]);
            if(j & 1) ryt = mergeT(tree[--j], ryt);
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
    SegTree(vector<T> &v, T it, L il,
        function<T(T, T)> mergeT,
        function<L(L, L)> mergeL,
        function<T(T, L)> applyL,
        function<bool(T, T)> compLe,
        function<bool(T, T)> compRi)
        : n(v.size()), it(it), il(il), 
        mergeT(mergeT), mergeL(mergeL), applyL(applyL), compLe(compLe), compRi(compRi) {
        
        h = 33 - __builtin_clz(n);
        tree.assign(2 * n, it);
        lazy.assign(n, il);
        for(int i = 0; i < n; i++)
            tree[i + n] = v[i];
        for(int i = n - 1; i > 0; i--)
            tree[i] = mergeT(tree[i << 1], tree[i << 1 | 1]);
    }
};

void solve(int tc){
    int ac, dr; cin >> ac >> dr;
    int n; cin >> n;
    vector<int> a(n), d(n);
    for(auto &u: a){
        cin >> u;
    }
    for(auto &u: d){
        cin >> u;
    }
    vector<int> freq(n), pref(n), score(n);
    for(int i = 0; i < n; i++){
        int tot = max(0, a[i] - ac) + max(0, d[i] - dr);
        if(tot < n) freq[tot]++;
        score[i] = tot;
    }
    for(int i = 1; i < n; i++){
        pref[i] = pref[i - 1] + freq[i - 1];
    }
    for(int i = 0; i < n; i++){
        pref[i] -= i;
    }

    auto Sum = [&](int a, int b) -> int{
        return a + b;
    };
    auto Min = [&](int a, int b) -> int{
        return min(a, b);
    };
    auto comp = [&](int a, int b) -> bool{
        return a < b;
    };
    SegTree<int, int> segMax(pref, inf, 0, Min, Sum, Sum, comp, NULL);
    SegTree<int, int> segSum(freq, 0, 0, Sum, NULL, Sum, NULL, NULL);

    int q; cin >> q;
    while(q--){
        int k, na, nd; cin >> k >> na >> nd; k--;
        
        if(score[k] < n - 1) segMax.update(score[k] + 1, n - 1, -1);
        if(score[k] < n) segSum.update(score[k], score[k], -1);
    
        score[k] = max(0, na - ac) + max(0, nd - dr);
        if(score[k] < n - 1) segMax.update(score[k] + 1, n - 1, 1);
        if(score[k] < n) segSum.update(score[k], score[k], 1);

        int lft = segMax.findL(0, 0);
        cout << segSum.query(0, lft - 1) << '\n';
    }

}

signed main() {
    faster
    int t = 1;
    // cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
    return 0;
}