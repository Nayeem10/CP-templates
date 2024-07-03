// Problem: https://cses.fi/problemset/task/1649/
 
#include <bits/stdc++.h>
using namespace std;
 
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
#define int long long
#define endl "\n"
 
template<typename node, typename change>
class SegmentTree
{
public:
    int n;
 
    node *tree, identity;
    node (*merge)(node, node);
 
    change *lazy, noChange;
    void (*applyUpdate)(int, int, node&, change);
    void (*mergeUpdate)(int, int, change&, change);
 
    void build(vector<node> &input, int lo, int hi, int root=0)
    {
        if(lo==hi)
        {
            tree[root]=input[lo];
            return;
        }
 
        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        build(input, lo, mid, leftChild);
        build(input, mid+1, hi, rightChild);
 
        tree[root]=merge(tree[leftChild], tree[rightChild]);
    }
 
    void propagate(int lo, int hi, int root)
    {
        applyUpdate(lo, hi, tree[root], lazy[root]);
 
        if(lo<hi)
        {
            int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
 
            mergeUpdate(lo, mid, lazy[leftChild], lazy[root]);
            mergeUpdate(mid+1, hi, lazy[rightChild], lazy[root]);
        }
 
        lazy[root]=noChange;
    }
 
    void update(int from, int to, int lo, int hi, int root, change delta)
    {
        if(lo>hi) return;
        
        propagate(lo, hi, root);
        if(from>hi || to<lo) return;
 
        if(from<=lo && to>=hi)
        {
            mergeUpdate(lo, hi, lazy[root], delta);
            propagate(lo, hi, root);
            return;
        }
 
        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        update(from, to, lo, mid, leftChild, delta);
        update(from, to, mid+1, hi, rightChild, delta);
 
        tree[root]=merge(tree[leftChild], tree[rightChild]);
    }
 
    node query(int from, int to, int lo, int hi, int root)
    {
        if(lo>hi) return identity;
        
        propagate(lo, hi, root);
        if(from>hi || to<lo) return identity;
 
        if(from<=lo && to>=hi) return tree[root];
        
        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        node q1=query(from, to, lo, mid, leftChild), q2=query(from, to, mid+1, hi, rightChild);
        return merge(q1, q2);
    }
 
public:
    SegmentTree(SegmentTree& st):
        tree(st.tree), lazy(st.lazy), n(st.n),
        merge(st.merge), identity(st.identity),
        applyUpdate(st.applyUpdate), mergeUpdate(st.mergeUpdate), noChange(st.noChange)
    {}
 
    SegmentTree(
        vector<node> &input,
        node (*merge)(node, node),
        node identity,
        void (*applyUpdate)(int, int, node&, change),
        void (*mergeUpdate)(int, int, change&, change),
        change noChange
        ):
        n(input.size()),
        merge(merge), identity(identity),
        applyUpdate(applyUpdate), mergeUpdate(mergeUpdate), noChange(noChange)
    {
        tree=new node[n<<2];
        build(input, 0, n-1);
 
        lazy=new change[n<<2];
        fill(lazy, lazy+(n<<2), noChange);
    }
 
    node query(int from, int to)
    {
        if(from>to || to>n) return identity;
        return query(from, to, 0, n-1, 0);
    }
 
    void update(int from, int to, change delta)
    {
        update(from, to, 0, n-1, 0, delta);
    }
 
    ~SegmentTree()
    {
        delete[] tree;
        delete[] lazy;
    }
};
 
void pre()
{
    fastio;
 
    
}
 
int minVal(int a, int b)
{
    return min(a, b);
}
 
void applyReplace(int lo, int hi, int& val, pair<bool,int> delta)
{
    auto [flag, newVal]=delta;
    if(flag==true) val=newVal;
}
 
void mergeReplace(int lo, int hi, pair<bool,int>& delta1, pair<bool,int> delta2)
{
    auto [flag, newVal]=delta2;
    if(flag==true) delta1=delta2;
}
 
void solve(int tc)
{
    int i, n, q, k, u, l, r, t;
    cin >> n >> q;
 
    vector<int> v(n);
    for(auto &it: v) cin >> it;
 
    pair<bool,int> noChange={0, 123}, delta;
    SegmentTree<int,pair<bool,int>> st(v, minVal, LLONG_MAX, applyReplace, mergeReplace, noChange);
 
    while(q--)
    {
        cin >> t;
 
        if(t==1)
        {
            cin >> k >> u;
            k--;
 
            delta={1, u}; // flag=true, value = u
            st.update(k, k, delta); // from=k, to=k, delta=delta
        }
 
        if(t==2)
        {
            cin >> l >> r;
            l--; r--;
 
            cout << st.query(l, r) << endl;
        }
    }
}
 
signed main()
{
    pre();
 
    int tc, tt=1;
    // cin >> tt;
    
    for(tc=1; tc<=tt; tc++)
    {
        solve(tc);
        // cout << endl;
    }
 
    return 0;
}