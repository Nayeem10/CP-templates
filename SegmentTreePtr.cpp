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
