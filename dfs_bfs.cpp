#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e5+10;

/*

int dx[]={-1,1,0,0}, dy[]={0,0,-1,1};  // for grid problems
char dp[]="UDLR";
bool vis[101][101];
char g[101][101];

*/


vector<int> g[N];
bool vis[N];

void dfs(int node){
    vis[node]=1;
    for(auto child:g[node]){
        if(!vis[child])
            dfs(child);
    }
}

void bfs(int node){
    queue<int> q;
    q.push(node);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        vis[cur]=1;
        for(auto child : g[cur]){
            if(!vis[child]){
                q.push(child);
            }
        }
    }
}


vector<pii> wg[N];
bool vis[N];
vector<ll> dis(N,INT_MAX);

void djikstra(int node){
    priority_queue<pii,vector<pii>,greater<pii>> q;
    q.push({0,node});
    dis[node]=0;
    while(!q.empty()){
        int cur = q.top().second;
        q.pop();
        if(vis[cur])continue;
        vis[cur]=1;
        for(auto [child,cost] : wg[cur]){
            if(dis[child] > dis[cur]+cost){
                dis[child]=dis[cur]+cost;
                q.push({dis[child],child});
            }
        }
    }
}


int min(){

}


