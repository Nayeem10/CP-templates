Data Structures
1. Ordered Structures
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
#define ordered_multiset tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
X.order_of_key(d) -> number of elements less than d in X
*X.find_by_order(d) -> number at index d in X
2. BIT
int a[N],bin[N];
 
void update(int idx, int val, int n){  
  while(idx<=n){                     
    bin[idx]+=val;
    idx += idx&-idx;
  }
}
int helper(int idx){
    int sum = 0;
    while(idx>0){
        sum+=bin[idx];
        idx -= idx&-idx;
    }
    return sum;
}
int query(int l,int r){             
    return helper(r)-helper(l-1);
}
3. 2D-BIT (forest query problem)
int a[10001][10001],bin[10001][10001];
void update(int x,int y, int val, int n){
    for(int i=x; i<=n; i += i&-i){
        for(int j=y; j<=n; j += j&-j){
            bin[i][j]+=val;
        }
    }
}
int query(int x,int y){
  int sum = 0;
  for(int i=x; i>0; i -= i&-i){
    for(int j=y; j>0; j -= j&-j){
      sum += bin[i][j];
    }
  }
  return sum;
// check --> query(x2,y2)-query(x2,y1-1)-query(x1-1,y2)+query(x1-1,y1-1)
}

4. Sparse Table
#define log_2(n) 63-__builtin_clzll(n)
 
LL sparseTable[MAXN][(LL)log_2(MAXN) + 5];
void build(LL n, vector<LL> &v){
  for(LL i = 0; i < n; i++) sparseTable[i][0] = v[i];
  for(LL j = 1; (1 << j) <= n; j++) {
    for(LL i = 0; (i + (1 << j) - 1) < n; i++) 
      sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
  }
}
LL query(LL L, LL R){
  LL j = (LL)log_2(R - L + 1);
  return min(sparseTable[L][j], sparseTable[R - (1 << j) + 1][j]);
}

// 2-DIMENTIONAL SPARSE TABLE FOR A MATRIX/GRID
ll grid[MAXN][MAXN];
ll sparseTable[MAXN][MAXN][10];
void build(ll n){
  for(ll k=0;(1 << k)<=n;k++) {
    for(ll i=0;i+(1 << k)-1 < n;i++) {
      for(ll j=0;j+(1 << k)-1 < n;j++) {
        if(!k) sparseTable[i][j][k] = grid[i][j];
        else {
          ll power = 1 << (k - 1);
          sparseTable[i][j][k] = max({sparseTable[i][j][k - 1], sparseTable[i + power][j][k - 1], sparseTable[i][j + power][k - 1], sparseTable[i + power][j + power][k - 1]});
        }
      }
    }
  }
}
ll query(ll i, ll j, ll s){
  ll k = log2(s);
  ll power = 1 << k;
  return max({sparseTable[i][j][k], sparseTable[i + s - power][j][k], sparseTable[i][j + s - power][k], sparseTable[i + s - power][j + s - power][k]});
}
void SPARSE_TABLE(){
  build(n);
  while(q--) {
    ll R, C, S; cin >> R >> C >> S;
    R--; C--;
    cout << query(R, C, S) << endl;
  }
}
5. Segment Tree
class segmentTree{
  int *seg; int n;
  int merge(int a,int b){
      return max(a,b);
  }
  void build(int idx,int le, int ri,vector<int> &v){
    if(le==ri){
      seg[idx] = v[le]; return;
    }
    int mid=(le+ri)>>1;
    build(2*idx+1, le,mid,v);
    build(2*idx+2,mid+1,ri,v);
    seg[idx] = merge(seg[2*idx+1],seg[2*idx+2]);
  }
  void update(int idx, int le,int ri,int k,int val){ 
    if(le==ri){
      seg[idx] = val; return;
    }
    int mid = (le+ri) >> 1;
    if(k<=mid) update(2*idx+1,le,mid,k,val);
    else update(2*idx+2,mid+1,ri,k,val);
    seg[idx] = merge(seg[2*idx+1],seg[2*idx+2]);
  }
  int query(int idx,int le,int ri,int l,int r){
    if(l<=le && r>=ri) return seg[idx];
    if(r<le || l>ri) return 0;  ///////identity
    int mid = (le+ri) >> 1;
    return  merge(query(2*idx+1,le,mid,l,r) , query(2*idx+2,mid+1,ri,l,r));
  }
  public:
  segmentTree(int m,vector<int> &v){
    n = m;
    seg = new int [4*n];
    build(0,0,n-1,v);
  }
  void update(int k,int val){
    update(0,0,n-1,k,val);
  }
  int query(int l,int r){
    return query(0,0,n-1,l,r);
  }
};
//extra part: use of array compression with segment tree
void compressarray(){  //longest increasing and decreasing subsequence
  int n; cin>>n;
  int a[n],b[n];
  for(int i=0;i<n;i++){
    cin>>a[i];
    b[i] = a[i];
  }
  sort(b,b+n);
  int l[n], r[n]; //increasing and decreasing subsequence from each i[0,n-1]
  vector<int> v(n,0);
  segmentTree treel(n,v),treer(n,v);
  for(int i=0;i<n;i++){
    int pos = lower_bound(b,b+n,a[i])-b;
    int val = (treel.query(0,pos-1));
    l[i] = val;
    treel.update(pos,val+1);
  }
  for(int i=n-1;i>=0;i--){
    int pos = lower_bound(b,b+n,a[i])-b;
    int val = (treer.query(0,pos-1));
    r[i] = val;
    treer.update(pos,val+1);
  }
}
6. Segment Tree with Lazy Propagation
template<typename T1,typename T2>
//T1 is main array and T2 is the data type of segment tree
class segtree{
  private:
  int n;
  T2 (*seg);
  T2 identity;
  int *lazy;
  T2 merge(T2 a,T2 b){
    return max(a,b);
  }
  void propagate(int idx,int val,int le,int ri){//change propagate function accordingly
    seg[idx] += (ri-le+1)*val;
    if(le != ri){
      lazy[2*idx+1] += val;
      lazy[2*idx+2] += val;
    }
    lazy[idx] = 0;
  }
  void build(int idx,int le, int ri,T1 a[]){
    if(le==ri){
      seg[idx] = a[le];       //how the main array will affect the segment tree
      return;
    }
    int mid=(le+ri)/2;
    build(idx*2+1,le,mid,a);
    build(idx*2+2,mid+1,ri,a);
    seg[idx] = merge(seg[2*idx+1],seg[2*idx+2]);
  }
  void update(int idx,int le,int ri,int l,int r,int val){
    if(lazy[idx]) propagate(idx,lazy[idx],le,ri);
    if(r<le || l>ri) return;
    if(le>=l && ri<=r){
      propagate(idx,val,le,ri); return;
    }
    int mid=(le+ri)/2;
    update(idx*2+1,le,mid,l,r,val);
    update(idx*2+2,mid+1,ri,l,r,val);
    seg[idx] = merge(seg[2*idx+1],seg[2*idx+2]);
  }

  T2 query(int idx,int le,int ri,int l,int r){
    if(lazy[idx]){
        propagate(idx,lazy[idx],le,ri);
    }
    if(l<=le && r>=ri) return seg[idx];
    if(r<le || l>ri) return identity;
    int mid=(le+ri)/2;
    return merge(query(idx*2+1,le,mid,l,r) , query(idx*2+2,mid+1,ri,l,r));
  }
  public:
  segtree(T1 arr[],int m,,T2 Identity){
    n=m;
    identity = Identity;
    seg = new T2[n*4];
    lazy = new int[n*4];
    memset(lazy,0,sizeof(lazy));
    build(0,0,n-1,arr);
  }
  void update(int l,int r,int val){
    update(0,0,n-1,l,r,val);
  }
  T2 query(int l,int r){
    return query(0,0,n-1,l,r);
  }
};

7. DSU
struct DSU {
  vector <int> par, size;
  DSU(int n) : par(n), size(n) {
      fill(size.begin(), size.end(), 1);
      iota(par.begin(), par.end(), 0);
  }
  int root(int node){
      if(par[node] == node) return node;
      return par[node] = root(par[node]); 
  }
  bool same(int x, int y){
      return root(x) == root(y);
  }
  void merge(int x, int y){
      x = root(x), y = root(y);
      if(x == y) return;
      if(size[x] < size[y]) swap(x, y);
      size[x] += size[y], par[y] = x;
  }
};

8.merge sort tree const int inf = 1e9 + 7;
const int N = 5e4 + 7;
int n, m;
int a[N];
vector<int> tree[N * 4];
vector<int> merge(vector<int> a,vector<int> b){
  int i=0, j=0, sza=a.size(), szb=b.size();
  vector<int> ret;
  while (i < sza or j < szb){
    if (i == sza) ret.emplace_back(b[j++]);
    else if (j == szb) ret.emplace_back(a[i++]);
    else{
      if (a[i] < b[j]) ret.emplace_back(a[i++]);
      else ret.emplace_back(b[j++]);
    }
  }
  return ret;
}
void build(int v, int l, int r){
  if (l == r) return void(tree[v] = {a[l]});
  int m = l + (r - l) / 2;
  build(v * 2, l, m);
  build(v * 2 + 1, m + 1, r);
  tree[v] = merge(tree[v * 2], tree[v*2+1]);
}
int query(int v, int l, int r, int ql,int qr, int k){
  if (r < ql or qr < l) return 0;
  if (l >= ql and r <= qr){
    int lo = 0, hi = (int)tree[v].size() - 1, pos = -1;
    while (lo <= hi){
      int mid = lo + (hi - lo) / 2;
      if (tree[v][mid] > k) hi = mid - 1;
      else pos = mid, lo = mid + 1;
    }
    return pos + 1;
  }
  else{
      int m = l + (r - l) / 2;
      return query(v * 2, l, m, ql, qr, k) + query(v * 2 + 1, m + 1, r, ql, qr, k);
  }
}
void update(int v, int b, int e, int i,int x){
  if (b == e) return void(tree[v] = {x});
  int mid = b + (e - b) / 2;
  if (mid < i) update(v * 2 + 1, mid + 1, e, i, x);
  else update(v * 2, b, mid, i, x);
  tree[v] = merge(tree[v * 2], tree[v*2+1]);
}
//build(1, 0, n - 1),query(1, 0, n - 1, l - 1, r - 1, k)
