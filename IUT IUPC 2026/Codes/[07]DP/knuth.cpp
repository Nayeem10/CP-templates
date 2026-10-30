// opt(i, j) = maximum value of k that minimizes dp(i, j)
// C(i, j) = cost of single merging of (i, j)
// dp(i, j) = min cost of total merging of (i, j)
// necessary condition opt(i, j - 1) <= opt(i, j) <= opt(i + 1, j)
// above condition is true if (not the only condition) C(b, c) <= C(a, d) and C(a, c) + C(b, d) <= C(a, d) + C(b, c) where a <= b <= c <= d
int solve() {
    int dp[N][N], opt[N][N];
    auto C = [&](int i, int j) {};
    for (int i = 0; i < N; i++) opt[i][i] = i;
    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            int mn = INT_MAX;
            int cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }
    return dp[0][N-1];
}
