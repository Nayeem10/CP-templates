#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <vector>
typedef long long LL;
using namespace std;
inline int read() {
    int num = 0 ,f = 1; char c = getchar();
    while (!isdigit(c)) f = c == '-' ? -1 : f ,c = getchar();
    while (isdigit(c)) num = (num << 1) + (num << 3) + (c ^ 48) ,c = getchar();
    return num * f;
}
const int N = 1e2 + 5;
int n ,tot;
int a[N] ,b[N] ,vis[N] ,ids[N] ,q[N] ,len[N] ,minn[N] ,to[N] ,tos[N] ,used[N] ,done[N] ,res[N];
vector <int> cir[N] ,vc[N] ,lens;
inline bool cmp(int x ,int y) {return minn[x] > minn[y];}
inline void fuling_solve() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = b[i] = vis[i] = ids[i] = q[i] = len[i] = 0;
        minn[i] = to[i] = tos[i] = used[i] = done[i] = res[i] = 0;
        cir[i].clear(); vc[i].clear();
    }
    lens.clear();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) b[i] = read();
    tot = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        tot++;
        cir[tot].clear();
        minn[tot] = n + 1;
        to[tot] = tos[tot] = used[tot] = done[tot] = 0;
        int x = i;
        while (!vis[x]) {
            vis[x] = 1;
            ids[x] = tot;
            q[x] = cir[tot].size();
            cir[tot].emplace_back(x);
            minn[tot] = min(minn[tot] ,x);
            x = a[x];
        }
        len[tot] = cir[tot].size();
    }
    for (int i = 1; i <= n; i++) {
        if (b[i] == -1) continue;
        int x = ids[i] ,y = ids[b[i]];
        if (len[x] != len[y]) return puts("No") ,void();
        int now = q[b[i]] - q[i];
        if (now < 0) now += len[x];
        if (!to[x]) to[x] = y ,tos[x] = now;
        else if (to[x] != y || tos[x] != now) return puts("No") ,void();
    }
    for (int i = 1; i <= tot; i++) {
        if (!to[i]) continue;
        if (used[to[i]]) return puts("No") ,void();
        used[to[i]] = 1;
    }
    for (int i = 1; i <= tot; i++) {
        if (!to[i]) continue;
        int x = to[i] ,s = tos[i];
        for (int j = 0; j < len[i]; j++) res[cir[i][j]] = cir[x][(j + s) % len[i]];
    }
    for (int i = 1; i <= tot; i++) {
        if (used[i]) continue;
        if (vc[len[i]].empty()) lens.emplace_back(len[i]);
        vc[len[i]].emplace_back(i);
    }
    for (auto v : lens) sort(vc[v].begin() ,vc[v].end() ,cmp);
    for (int i = 1; i <= n; i++) {
        int x = ids[i];
        if (to[x] || done[x]) continue;
        if (vc[len[x]].empty()) return puts("No") ,void();
        int y = vc[len[x]].back();
        vc[len[x]].pop_back();
        int s = q[minn[y]] - q[i];
        if (s < 0) s += len[x];
        for (int j = 0; j < len[x]; j++) res[cir[x][j]] = cir[y][(j + s) % len[x]];
        done[x] = 1;
    }
    puts("Yes");
    for (int i = 1; i <= n; i++) printf("%d%c" ,res[i] ," \n"[i == n]);
    for (int i = 1; i <= tot; i++) cir[i].clear();
    for (auto v : lens) vc[v].clear();
    lens.clear();
}
signed main() {
    // freopen("test.out" ,"w" ,stdout);
    int t = 1;
    while (t--) fuling_solve();
    return 0;
}
