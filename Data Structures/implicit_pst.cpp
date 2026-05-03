#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds; 
using namespace std;
 
typedef pair<long long,long long> PLL;
typedef long long LL;

#define all(v) v.begin(),v.end()
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_multiset tree<int, null_type,less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>    
 
const LL mod = 1e9 + 7;
const int N = 2e5 + 10;
const LL inf = 1e18;

class PST{
    struct node{
        int left = 0, right = 0, val = 0;
    };
    vector<node> tree;

    int N, LG, time = 0, I = 0;

    node create(int l, int r){
        return {l, r, merge(tree[l].val, tree[r].val)};
    }

    int update(int id, int le, int ri, int pos, int val){
        int nid = ++time;
        if(le == ri) return tree.push_back({0, 0, (tree[id].val ^ val)}), nid;
        int m = (le + ri) / 2;
        tree.push_back(node());
        if(pos <= m){
            tree[nid] = create(update(tree[id].left, le, m, pos, val), tree[id].right);
        }else{
            tree[nid] = create(tree[id].left, update(tree[id].right, m + 1, ri, pos, val));
        }
        return nid;
    }
    int query(int id, int di, int le, int ri){
        if(tree[id].val == tree[di].val) return -1;
        if(le == ri) return le;
        int m = (le + ri) >> 1;
        
        if(tree[tree[id].right].val != tree[tree[di].right].val) 
            return query(tree[id].right, tree[di].right, m + 1, ri);
        return query(tree[id].left, tree[di].left, le, m);
    }
    int merge(LL a, LL b){ 
        return a ^ b;
    }
public:
    PST(int N){
        this->N = N;   
        tree.push_back(node());     
    }
    int update(int id, int pos, int val){
        return update(id, 1, N, pos, val);
    }
    int query(int id, int di){
        return query(id, di, 1, N);
    }
    ~PST(){
    }
};


struct custom_double_hash {
    static uint32_t splitmix32(uint32_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static uint32_t splitmix32_second(uint32_t x) {
        x += 0x85ebca6b;
        x = (x ^ (x >> 13)) * 0xc2b2ae35;
        x = (x ^ (x >> 16)) * 0x27d4eb2f165667c5;
        return x ^ (x >> 15);
    }

    size_t operator()(uint32_t x) const {
        static const uint32_t FIXED_RANDOM_1 = chrono::steady_clock::now().time_since_epoch().count();
        static const uint32_t FIXED_RANDOM_2 = chrono::steady_clock::now().time_since_epoch().count() + 0x517cc1b727220a95;
        
        uint32_t hash1 = splitmix32(x + FIXED_RANDOM_1);
        uint32_t hash2 = splitmix32_second(x + FIXED_RANDOM_2);
        
        return hash1 ^ hash2;
    }
} rng;

void solve(int test){
    int n; cin>>n;

    PST tree(1000000009);
    vector<int> ver(n + 10); ver[1] = 0;

    int u = 2;
    for(int i = 0; i < n; i++){
        int t; cin >> t;
        if(t == 1){
            int p, x; cin >> p >> x;
            ver[u++] = tree.update(ver[p], x, rng(x)); 
        }else{
            int a, b; cin >> a >> b;
            int ans = tree.query(ver[a], ver[b]);
            cout << ans << endl;
        }
    }
}
 
signed main(){
    // faster
    int t = 1; 
    // cin>>t;
    for(int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}