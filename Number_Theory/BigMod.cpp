LL bigmod(LL x, LL n, LL M){
    if (n == -1) n = M - 2;
    LL ans = 1;
    while (n) {
        if (n & 1) ans = (1LL * ans * x) % M;
        n >>= 1;
        x = (1LL * x * x) % M;
    }
    return ans;
}

