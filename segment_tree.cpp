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
    Tree* left;
    Tree* right;

    Tree() : val(0), left(nullptr), right(nullptr) {}
    Tree(int x) : val(x), left(nullptr), right(nullptr) {}
    Tree(int x, Tree* left, Tree* right) : val(x), left(left), right(right) {}
};

class segmentTree{
    Tree *root;
    int n;

    void merge(Tree* node){
        node->val = min (node->left->val , node->right->val);
    }

    Tree* build(int le, int ri,int a[]){
        if(le==ri){
            Tree* node = new Tree(a[le]);
            return node;
        }

        Tree* node=new Tree();

        int mid=(le+ri)>>1;
        node->left = build(le,mid,a);
        node->right = build(mid+1,ri,a);
        merge(node);
        return node;
    }

    void update(Tree* node, int le,int ri,int k,int v){
        
        if(le==ri){
            node->val = v;
            return;
        }
        int mid = (le+ri) >> 1;
        if(k<=mid)
        update(node->left,le,mid,k,v);
        else
        update(node->right,mid+1,ri,k,v);
        merge(node);
    }

    int query(Tree* node,int le,int ri,int l,int r){
        if(l<=le && r>=ri){
            return node->val;
        }
        if(r<le || l>ri){
            return 0; 
        }
        int mid = (le+ri) >> 1;
        return min (query(node->left,le,mid,l,r) , query(node->right,mid+1,ri,l,r));
    }


    public:
    segmentTree(int a[],int m){
        n = m;
        root = build(0,n-1,a);
    }
    void update(int k,int val){
        update(root,0,n-1,k,val);
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
            int k,val;
            cin>>k>>val;
            tree.update(k-1,val);
        }else{
            int l,r;
            cin>>l>>r;
            cout<<tree.query(l-1,r-1)<<endl;
        }
    }
}

signed main(){
    faster
    debugMode();
    int t=1;
    //cin>>t;
    for(int cs=1;cs<=t;cs++){
        //cout<<"Case "<<cs<<": ";
        solve();
    }
    return 0;
}
