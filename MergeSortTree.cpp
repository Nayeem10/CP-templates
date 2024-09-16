class MergeSortTree{
    int n;
    vector<vector<int>> tree;
    void build(int id, int le, int ri, vector<int> &a){
        if(le == ri){
            tree[id].push_back(a[le]);
            return;
        }
        int mid = (le + ri) >> 1;
        build(2 * id + 1, le, mid, a);
        build(2 * id + 2, mid + 1, ri, a);
        auto &left = tree[2 * id + 1], &right = tree[2 * id + 2];
        int i = 0, j = 0, n = left.size(), m = right.size();
        while(i < n && j < m){
            if(left[i] < right[j]) tree[id].push_back(left[i]), i++;
            else tree[id].push_back(right[j]), j++;
        }
        while(i < n) tree[id].push_back(left[i]), i++;
        while(j < m) tree[id].push_back(right[j]), j++;
    }
    int query(int id, int le, int ri, int l, int r, int val){
        if(le > r || ri < l){
            return 0;
        }
        if(le >= l && ri <= r){
            return ri - le + 1 - (lower_bound(tree[id].begin(), tree[id].end(), val) - tree[id].begin());
        }
        int mid = (le + ri) >> 1;
        return query(2 * id + 1, le, mid, l, r, val) + query(2 * id + 2, mid + 1, ri, l, r, val);
    }
public:
    MergeSortTree(vector<int> &a){
        n = a.size();
        tree.resize(n * 4);
        build(0, 0, n - 1, a);
    }
    int query(int l, int r, int val) { return query(0, 0, n - 1, l, r, val); }
};