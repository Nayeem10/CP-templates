template<typename T>
class segmentTree{
    T *seg, I;
    int n;
    T(*merge)(T, T);
    
    void build(int idx,int le, int ri,vector<T> &v){
        if(le == ri){
            seg[idx] = v[le];
            return;
        }
        int mid = (le + ri) >> 1;
        build (2*idx+1, le, mid, v);
        build (2*idx+2, mid+1, ri, v);
        seg[idx] = merge (seg[2*idx+1], seg[2*idx+2]);
    }

    void update(int idx, int le, int ri, int pos, T val){
        if(le == ri){
            seg[idx] = val;
            return;
        }
        int mid = (le + ri) >> 1;
        if(pos <= mid)
            update (2*idx+1, le, mid, pos, val);
        else
            update (2*idx+2, mid+1, ri, pos, val);
        seg[idx] = merge (seg[2*idx+1], seg[2*idx+2]);
    }

    T query(int idx, int le, int ri, int l, int r){
        if(l <= le && r >= ri){
            return seg[idx];
        }
        if(r < le || l > ri){
            return I;
        }
        int mid = (le + ri) >> 1;
        return  merge (query (2*idx+1, le, mid, l, r) , query (2*idx+2, mid+1, ri, l, r));
    }

    //finding the leftmost appearence of value <= val in [l....r] range
    //need minimum segment tree
    int walk(int idx, int le, int ri, int l, int r, T val){
        if(r < le || l > ri){
            return r; 
        }
        if(le == ri){
            if(seg[idx] <= val) return le;
            return r;
        }
        if(l <= le && r >= ri){
            int mid = (le + ri) >> 1;
            if(seg[2*idx+1] <= val) return walk (2*idx+1, le, mid, l, r, val);
            return walk (2*idx+2, mid+1, ri, l, r, val);
        }
        int mid = (le + ri) >> 1;
        return  merge (walk (2*idx+1, le, mid, l, r, val) , walk (2*idx+2, mid+1, ri, l, r, val));
    }

    public:
    segmentTree(vector<T> &v, T(*fptr)(T, T), T _I){
        n = v.size(); I = _I;
        merge = fptr;
        seg = new T [4*n];
        build(0, 0, n-1, v);
    }
    void update(int pos, int val){
        update(0, 0, n-1, pos, val);
    }
    int walk(int l, int r, T val){
        if(query (l,r) > val) return r;
        return walk (0, 0, n-1, l, r, val);
    }
    T query(int l, int r){
        return query(0, 0, n-1, l, r);
    }
};

int fun1(int a,int b){
    return max(a,b);
}
int fun2(int a,int b){
    return min(a,b);
}


void compressarray(){
    int n,q;
    cin>>n;
    int a[n],b[n];

    for(int i=0;i<n;i++){
        cin>>a[i];
        b[i] = a[i];
    }
    sort(b,b+n);
    int l[n], r[n];
    vector<int> v(n,0);
    segmentTree treel(v,fun1,-1e9),treer(v,fun1,-1e9);
    
    //calculating maximum increasing subsequence from 0 to i (if i is included)
    for(int i=0;i<n;i++){
        int pos = lower_bound(b,b+n,a[i])-b;
        int val = (treel.query(0,pos-1));
        l[i] = val;
        treel.update(pos,val+1);
    }

    //calculating maximum increasing subsequence from n-1 to i (if i is included)
    for(int i=n-1;i>=0;i--){
        int pos = lower_bound(b,b+n,a[i])-b;
        int val = (treer.query(0,pos-1));
        r[i] = val;
        treer.update(pos,val+1);
    }
    
    int ans = -1;
    
    for(int i=0;i<n;i++){
        if(l[i] && r[i]){
            ans = max(ans,l[i]+r[i]+1);
        }
    }
    cout<<ans<<'\n';
}