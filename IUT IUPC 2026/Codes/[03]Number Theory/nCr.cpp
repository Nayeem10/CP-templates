namespace com {
LL fact[N], inv[N], inv_fact[N];
void init() {
  fact[0] = inv_fact[0] = 1;
  for (LL i = 1; i < N; i++) {
    inv[i] = i == 1 ? 1 : (LL)inv[i - mod % i] * (mod / i + 1) % mod;
    fact[i] = (LL)fact[i - 1] * i % mod;
    inv_fact[i] = (LL)inv_fact[i - 1] * inv[i] % mod;
} }
LL C(int n, int r) {
  return (r < 0 or r > n) ? 0 : fact[n] * inv_fact[r] % mod * inv_fact[n - r] % mod;
} }  // namespace com