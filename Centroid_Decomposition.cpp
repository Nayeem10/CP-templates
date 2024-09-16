//  https://codeforces.com/contest/321/problem/C

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> g[N];
int height[N], tsize[N];

int dfs(int u, int p = 0){
    int &sz = tsize[u]; sz = 1;
    for(auto v: g[u]){
        if(v != p) sz += dfs(v, u);
    }
    return sz;
}

int centroid(int u, int p, int sz){
    for(auto v: g[u]){
        if(v == p || height[v]) continue;
        if(2 * tsize[v] > sz) return centroid(v, u, sz);
    }
    return u;
}

void decompose(int u = 1, int h = 1){
    u = centroid(u, -1, dfs(u));
    height[u] = h;
    for(auto v: g[u]){
        if(!height[v]) decompose(v, h + 1);
    }
}

int main(){
    int n; cin>>n;
    for(int i = 1, u, v; i < n; i++){
        cin>>u>>v;
        g[u].push_back(v); g[v].push_back(u);
    }

    decompose();
    for(int i = 1; i <= n; i++){
        cout<<(char)('A' + height[i] - 1)<<" ";
    }
    cout<<'\n';
}