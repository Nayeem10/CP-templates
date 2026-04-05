#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
using LL = long long;
using PLL = pair<LL, LL>;

#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_set tree<LL, null_type,less<LL>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(), v.end()

const LL mod = 998244353;
const int N = 5e5 + 10;
const int inf = 1e9 + 10;
const LL INF = 1e18;

template<class T, class L, T it, L il, 
         T(*mergeT)(T, T), 
         T(*applyL)(T, L), 
         L(*mergeL)(L, L)>
struct SegTree{
    int n;
    vector<T> tree;

    bool (*compLe)(T, T);
    bool (*compRi)(T, T);

    SegTree() {}
    SegTree(int n, bool (*compLe)(T, T), bool (*compRi)(T, T))
        : n(n), compLe(compLe), compRi(compRi) {
        tree.assign(2 * n, it);
    }

    SegTree(vector<T> &v, bool (*compLe)(T, T), bool (*compRi)(T, T))
        : n(v.size()), compLe(compLe), compRi(compRi) {
        tree.assign(2 * n, it);
        for(int i = 0; i < n; i++)
            tree[i + n] = v[i];
        for(int i = n - 1; i > 0; i--)
            tree[i] = mergeT(tree[i << 1], tree[i << 1 | 1]);
    }

    // point update only
    void update(int l, int r, L val){
        // assume l == r
        int i = l + n;
        tree[i] = applyL(tree[i], val);
        for(i >>= 1; i > 0; i >>= 1)
            tree[i] = mergeT(tree[i << 1], tree[i << 1 | 1]);
    }

    T query(int l, int r){
        l += n, r += n + 1;
        T lft = it, ryt = it;
        for(; l < r; l >>= 1, r >>= 1){
            if(l & 1) lft = mergeT(lft, tree[l++]);
            if(r & 1) ryt = mergeT(tree[--r], ryt);
        }
        return mergeT(lft, ryt);
    }
};

struct node {
    LL sumr[31];
    int minr[31];
    constexpr node() : sumr{}, minr{} {
        for (int i = 0; i < 31; i++) {
            minr[i] = inf;
        }
    }
};
node mergeT(node a, node b){
    for(int i = 0; i <= 30; i++){
        a.sumr[i] += b.sumr[i];
        a.minr[i] = min(a.minr[i], b.minr[i]);
    }
    return a;
}
node applyL(node a, int x){
    for(int i = 30; x < (1LL << i); i--){
        a.sumr[i] = x;
    }
    a.minr[31 - __builtin_clz(x) + 1] = x;
    return a;
}
int mergeL(int a, int b){
    return 0;
}

void solve (int tc) {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    while(q--){
        int l, r; cin >> l >> r; l--, r--;
        vector<int> b;
        for(int i = l; i <= r; i++)
            b.push_back(a[i]);
        sort(all(b));
        LL miss = 1;
        for(auto u: b){
            if(u <= miss) miss += u;
            else break;
        }
        cout << miss << '\n';
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