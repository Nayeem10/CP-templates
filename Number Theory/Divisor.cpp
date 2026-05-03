// calculate divisor in range[1,n]
LL sum_in_range(LL n) {
  return n * (n + 1) / 2;
}
LL sum_all_divisors(LL n) {
  LL ans = 0;
  for(LL i=1;i*i<=n;i++) {
    LL hello = i * (n / i - i + 1);
    LL world = sum_in_range(n / i) - sum_in_range(i);
    ans += hello + world;
  }
  return ans;
}
