// NUMBER = p_1^a_1 * p_2^a_2 .... p_n^a_n
LL NOD = 1, SOD = 1, POD = 1, POWER = 1;
for (int i = 0; i < n; i++) {
  LL p, a; cin >> p >> a;
  NOD = (NOD * (a + 1)) % MOD;
  SOD = ((SOD * (bigmod(p, a + 1, MOD) + MOD - 1)) % MOD * inv[p - 1]) % MOD;
  POD = bigmod(POD, a + 1, MOD) * bigmod(bigmod(x, a * (a + 1) / 2, MOD), POWER, MOD) % MOD;
  POWER = (POWER * (a + 1)) % (MOD - 1);
}
LL csod(LL n) {
  LL ans = 0;
  for (LL i = 2; i * i <= n; ++i) {
    LL j = n / i;
    ans += (i + j) * (j - i + 1) / 2;
    ans += i * (j - i);
  }
  return ans;
}
// summation of NOD(d)[d | n] = product of g(e_k + 1)[n = p_k ^ a_k] g(x) = x * (x + 1) / 2