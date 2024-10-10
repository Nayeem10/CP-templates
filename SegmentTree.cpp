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

int fun(int a,int b){
    return max(a,b);
}
