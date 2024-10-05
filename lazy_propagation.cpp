#include<bits/stdc++.h>
using namespace std;

class LazySegmentTree {
    vector<int> tree;  
    vector<int> lazy; 
    int n, I;

    int merge(int a, int b) {
        return a + b;
    }

    void propagate(int node, int le, int ri) {
        if (lazy[node] != 0) {
            tree[node] += (ri - le + 1) * lazy[node]; 
            if (le != ri) { 
                lazy[2 * node + 1] += lazy[node];  
                lazy[2 * node + 2] += lazy[node]; 
            }
            lazy[node] = 0; 
        }
    }

    void build(int node, int le, int ri, vector<int> &arr) {
        if (le == ri) {
            tree[node] = arr[le]; 
            return;
        }
        int mid = (le + ri) / 2;
        build(2 * node + 1, le, mid, arr); 
        build(2 * node + 2, mid + 1, ri, arr);
        tree[node] = merge(tree[2 * node + 1] , tree[2 * node + 2]);
    }

    void update(int node, int le, int ri, int l, int r, int val) {
        propagate(node, le, ri); 
        if (r < le || l > ri) { 
            return;
        }
        if (le >= l && ri <= r) { 
            tree[node] += (ri - le + 1) * val;
            if (le != ri) {
                lazy[2 * node + 1] += val;  
                lazy[2 * node + 2] += val; 
            }
            return;
        }
        int mid = (le + ri) / 2;
        update(2 * node + 1, le, mid, l, r, val);      
        update(2 * node + 2, mid + 1, ri, l, r, val); 
        tree[node] = merge(tree[2 * node + 1] , tree[2 * node + 2]);
    }

    int query(int node, int le, int ri, int l, int r) {
        propagate(node, le, ri); 
        if (l <= le && r >= ri) {
            return tree[node];
        }
        if (r < le || l > ri) {
            return I;
        }
        int mid = (le + ri) / 2;
        return merge(query(2 * node + 1, le, mid, l, r) , query(2 * node + 2, mid + 1, ri, l, r));
    }

public:
    LazySegmentTree(vector<int> &arr, int I) {
        n = arr.size(); this->I = I;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1, arr); 
    }

    void update(int l, int r, int val) {
        update(0, 0, n - 1, l, r, val);
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};


void solve(){
    int n,q;
    cin>>n>>q;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    LazySegmentTree tree(a,n);
    while(q--){
        int c;
        cin>>c;
        if(c==1){
            int l,r,val;
            cin>>l>>r>>val;
            tree.update(l-1,r-1,val);
        }else{
            int a,b;
            cin>>a>>b;
            cout<<tree.query(a-1,b-1)<<endl;
        }
    }
}

signed main(){
    faster
    //debugMode();
    int t=1;
    //cin>>t;
    for(int cs=1;cs<=t;cs++){
        //cout<<"Case "<<cs<<": ";
        solve();
    }
    return 0;
}
