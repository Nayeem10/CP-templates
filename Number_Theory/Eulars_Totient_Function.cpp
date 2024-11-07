int phi(int n) {
  int ret = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % p == 0) n /= i;
      ret -= ret / i;
    }
  }
  if (n > 1) ret -= ret / n;
  return ret;
}
void phi_in_range() {
  int N = 1e6, phi[N + 1];
  for (int i = 0; i <= N; i++) phi[i] = i;
  for (int i = 2; i <= N; i++) {
    if (phi[i] != i) continue;
    for (int j = i; j <= N; j += i) {
      phi[j] -= phi[j] / i;
    }
  }
}

#some important properties of phi
phi(p) = p-1  ,where p is a prime number
phi(a*b) = phi(a)*phi(b)  ,where a and b are co-prime
phi(a*b) = phi(a)*phi(b)*(gcd(a,b)/phi(gcd(a,b)))  ,for any number
phi(p^k) = p^k - p^(k-1)  ,where p is a prime number, '^' indicates power
Sum of values of totient functions of all divisors of n is equal to n.
