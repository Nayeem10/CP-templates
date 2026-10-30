// Finds global min cut in n^3
LL stoer_wagner(vector<vector<LL>> g, vector<int>& cut) {
    int n = g.size();
    cut.clear();
    if (n <= 1) { if (n == 1) cut = {0}; return 0; }

    vector<vector<int>> v(n);
    vector<int> p(n);
    vector<LL> w(n);
    for (int i = 0; i < n; ++i) v[i] = {i}, p[i] = i;

    LL ans = 4e18;
    for (int rem = n; rem > 1; --rem) {
        for (int i = 1; i < rem; ++i) w[p[i]] = g[p[0]][p[i]];
        for (int step = 1; step < rem; ++step) {
            int mx = step;
            for (int i = step + 1; i < rem; ++i)
                if (w[p[i]] > w[p[mx]]) mx = i;
            swap(p[step], p[mx]);
            if (step < rem - 1)
                for (int i = step + 1; i < rem; ++i) w[p[i]] += g[p[step]][p[i]];
        }

        int s = p[rem - 2], t = p[rem - 1];
        if (w[t] < ans) ans = w[t], cut = v[t];

        v[s].insert(v[s].end(), v[t].begin(), v[t].end());
        for (int i = 0; i < rem - 1; ++i) {
            int u = p[i];
            g[s][u] = (g[u][s] += g[t][u]);
        }
        g[s][s] = 0;
    }
    return ans;
}