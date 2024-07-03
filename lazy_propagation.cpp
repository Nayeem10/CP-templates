#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define int long long
#define yes cout << "YES" << endl ;
#define no  cout << "NO" << endl ;
#define ln '\n'
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}

const ll mod=998244353;
const int N=2.5e5+10;

inline void debugMode() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // ONLINE_JUDGE
}

struct Tree {
    int val;
    int lazy;  
    Tree* left;
    Tree* right;

    Tree() : val(0), lazy(0), left(nullptr), right(nullptr) {}
    Tree(int x) : val(x), lazy(0), left(nullptr), right(nullptr) {}
    Tree(int x, Tree* left, Tree* right) : val(x), lazy(0), left(left), right(right) {}
};

class segmentTree{
    Tree *root;
    int n;

    void merge(Tree* node){
        node->val = node->left->val + node->right->val;
    }

    int merge(Tree* left, Tree* right){
        return left->val + right->val;
    }

    void propagate(Tree* node,int le,int ri){
        if(node->lazy){
            node->val += (ri-le+1) * node->lazy;
            if(le != ri){
                node->left->lazy += node->lazy;
                node->right->lazy += node->lazy; 
            }
            node->lazy = 0;
        }
    }


    Tree* build(int le, int ri,int a[]){
        if(le==ri){
            Tree* node = new Tree(a[le]);
            return node;
        }

        /*
        Tree* node=new Tree();              
        int mid=(le+ri)/2;
        node->left = build(le,mid,a);
        node->right = build(mid+1,ri,a);
        merge(node);
        */
                                            
        Tree* left = build(le, le+ri >>1, a);
        Tree* right = build((le+ri >>1) + 1, ri, a);

        return new Tree(merge(left,right),left,right);
    }

    void update(Tree* node, int le,int ri,int l,int r,int val){
        propagate(node,le,ri);
        if(r<le || l>ri){
            return;
        }
        if(le>=l && ri<=r){
            node->val += (ri-le+1)*val;
            if(le!=ri){
                node->left->lazy += val;
                node->right->lazy += val;
            }
            return;
        }
        int mid = le+ri >> 1;
        update(node->left,le,mid,l,r,val);
        update(node->right,mid+1,ri,l,r,val);
        merge(node);
    }

    int query(Tree* node,int le,int ri,int l,int r){
        propagate(node,le,ri);
        if(l<=le && r>=ri){
            return node->val;
        }
        if(r<le || l>ri){
            return 0; 
        }
        int mid = le+ri >> 1;
        return query(node->left,le,mid,l,r) + query(node->right,mid+1,ri,l,r);
    }


    public:
    segmentTree(int a[],int m){
        n = m;
        root = build(0,n-1,a);
    }
    void update(int l,int r,int val){
        update(root,0,n-1,l,r,val);
    }
    int query(int l,int r){
        return query(root,0,n-1,l,r);
    }
};

void solve(){
    int n,q;
    cin>>n>>q;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    segmentTree tree(a,n);
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
