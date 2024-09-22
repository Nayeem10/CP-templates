#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ln '\n'
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}

//  https://codeforces.com/contest/2014/problem/H

const int N = 2e5 + 10;
const int BLOCK = 450;  
int a[N], fr[1000010];
int odd = 0;

struct Query {
    int l, r, idx;
    bool operator<(const Query &other) const {
        if (l / BLOCK != other.l / BLOCK) {
            return l / BLOCK < other.l / BLOCK;
        }
        return r < other.r;
    }
};

void add(int idx) {
    fr[a[idx]]++;
    if (fr[a[idx]] % 2) {
        odd++;
    }else{
        odd--;
    }
}

void remove(int idx) {
    fr[a[idx]]--;
    if (fr[a[idx]] % 2) {
        odd++;
    }else{
        odd--;
    }
}

vector<bool> mo_algorithm(vector<Query> &queries, int n, int q) {
    sort(queries.begin(), queries.end());
    
    int currl = 0, curr_r = -1;
    vector<bool> result(q);
    for (auto &query : queries) {
        int l = query.l, r = query.r, idx = query.idx;
        while (curr_r < r) {
            add(++curr_r);
        }
        while (curr_r > r) {
            remove(curr_r--);
        }

        while (currl < l) {
            remove(currl++);
        }
        while (currl > l) {
            add(--currl);
        }
        if (!odd) {
            result[idx] = 1;
        } else {
            result[idx] = 0;
        }
    }
    return result;
}

void solve(int test){ 
    int n, q;
    cin>>n>>q;
    for(int i = 0; i < n; i++) {
        cin>>a[i]; 
    }
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin>>l>>r; l--, r--;
        queries[i] = {l, r, i}; 
    }

    vector<bool> res = mo_algorithm(queries, n, q);
    for(auto u: res){
        cout<<(u ? "YES" : "NO")<<'\n';
    }
    for(int i = 0; i < n; i++){
        fr[a[i]] = 0;
    }
    odd = 0;
}

signed main() {
    faster;
    int t; cin>>t;
    for(int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}
