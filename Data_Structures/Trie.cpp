struct node{
    int path, leaf;
    vector<int> child;
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
    bool find(string &s){
        int cur = 0;
        for(auto u: s){
            cur = tree[cur].child[u - '0'];
            if(cur == -1 || !tree[cur].path) return 0;
        }
        return tree[cur].leaf > 0;
    }
    int maxor(string &s){
        int cur = 0, p = 0, ans = 0;
        for(auto u: s, p++){
            int zero = tree[cur].child[0], one = tree[cur].child[1];
            cur = (u == '0' ? ~one ? one : zero : ~zero ? zero : one);
            ans |= (((u == '0' && ~one) || (u == '1' && ~zero)) << p);
        }
        return ans;
    }
};
