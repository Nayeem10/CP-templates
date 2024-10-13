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
const int N = 1e5 + 10;
const LL inf = 1e18;

struct Node {
    bool is_inc;
    int minV;
    int maxV;
};

class SegmentTree {
private:
    vector<Node> tree;
    vector<int> arr;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node].is_inc = true;
            tree[node].minV = arr[start];
            tree[node].maxV = arr[start];
        } else {
            int mid = (start + end) / 2;
            int left = 2 * node + 1;
            int right = 2 * node + 2;
            build(left, start, mid);
            build(right, mid + 1, end);
            merge(node, left, right);
        }
    }

    void merge(int node, int left, int right) {
        tree[node].is_inc = tree[left].is_inc && tree[right].is_inc &&
                                   tree[left].maxV <= tree[right].minV;
        tree[node].minV = min(tree[left].minV, tree[right].minV);
        tree[node].maxV = max(tree[left].maxV, tree[right].maxV);
    }

    Node query(int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return {true, INT_MAX, INT_MIN};
        }

        if (L <= start && end <= R) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        Node left_result = query(2 * node + 1, start, mid, L, R);
        Node right_result = query(2 * node + 2, mid + 1, end, L, R);

        Node result;
        result.is_inc = left_result.is_inc && right_result.is_inc &&
                               left_result.maxV <= right_result.minV;
        result.minV = min(left_result.minV, right_result.minV);
        result.maxV = max(left_result.maxV, right_result.maxV);
        return result;
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            arr[start] = value;
            tree[node].is_inc = true;
            tree[node].minV = value;
            tree[node].maxV = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, value);
            } else {
                update(2 * node + 2, mid + 1, end, idx, value);
            }
            merge(node, 2 * node + 1, 2 * node + 2);
        }
    }

public:
    SegmentTree(vector<int> &arr) {
        this->arr = arr;
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    bool isIncreasing(int L, int R) {
        Node result = query(0, 0, n - 1, L, R);
        return result.is_inc;
    }

    void update(int idx, int value) {
        update(0, 0, n - 1, idx, value);
    }
};

void solve(int test){
    int n, m, q; cin>>n>>m>>q;
    set<int> appear[n + 1];
    vector<int> a(n), b(m), id(n);
    for(int i = 0; i < n; i++) {
        cin>>a[i]; a[i]--; id[a[i]] = i;
    }
    for(auto &i: b) {
        cin>>i; i--;
    }
    vector<int> c(n + 10, n);
    for(int i = 0; i < m; i++){
        appear[b[i]].insert(i);
        // c[id[b[i]]] = min(c[id[b[i]]], i);
    } 
    for(int i = 0; i < n; i++){
        if(appear[a[i]].empty()) c[i] = n;
        else c[i] = *appear[a[i]].begin();
    }
    SegmentTree tree(c);
    if(tree.isIncreasing(0, n - 1)) cout<<"YA\n";
    else cout<<"TIDAK\n";
    while(q--){
        int s, t; cin>>s>>t; s--, t--;
        // cout<<
        // cout<<*appear[b[s]].begin()<<" "<<b[s] + 1<<'\n';
        appear[b[s]].erase(s);
        if(appear[b[s]].empty()) tree.update(id[b[s]], n);
        else tree.update(id[b[s]], *appear[b[s]].begin());
        
        b[s] = t;
        appear[b[s]].insert(s);
        // cout<<*appear[b[s]].begin()<<" "<<b[s] + 1<<'\n';
        
        tree.update(id[b[s]], *appear[b[s]].begin());
        if(tree.isIncreasing(0, n - 1)) cout<<"YA\n";
        else cout<<"TIDAK\n";
        // for(int i = 0; i < m; i++){
        //     cout<<b[i]+1<<" ";
        // }
        // cout<<'\n';
    }
}

signed main(){
    faster
    int t = 1; 
    // cin>>t;
    for(int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}
