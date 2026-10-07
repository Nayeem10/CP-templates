struct node{
    vector<int> child;
    int path, leaf;
    node(int n = 0) : child(n, -1), path(0), leaf(0) {}
};
class Trie{
    int n, ptr;
    vector<node> tree;
public:
    Trie(int n) : n(n), ptr(0){
        tree.emplace_back(node(n));
    }
    void insert(string &s){
        int cur = 0;
        for(auto u: s){
            int &next = tree[cur].child[u - '0'];
            if(next == -1){
                tree.emplace_back(node(n));
                next = ++ptr;
            }
            tree[cur].path++;
            cur = next;
        }
        tree[cur].path++;
        tree[cur].leaf++;
    }
    void erase(string &s){
        int cur = 0;
        for(auto u: s){
            tree[cur].path--;
            cur = tree[cur].child[u - '0'];
        }
        tree[cur].path--;
        tree[cur].leaf--;
    }
    int find(string &s, int k){
        int cur = 0, ret = 0, b = 29;
        for(auto u: s){
            int l = tree[cur].child[u - '0'];
            int r = tree[cur].child[(u - '0') ^ 1];

            int cnt = 0;
            if(cur != -1) cnt = tree[l].path;

            if(cnt >= k){
                if(l == -1) return inf;
                cur = l;
            }else{
                if(r == -1) return inf;
                k -= cnt, cur = r;
                ans |= (1 << b);
            }
            b--;
        }
        return ret;
    }
};
