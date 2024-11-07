namespace rho{
  inline LL mul(LL a, LL b, LL mod) {
    LL result = 0;
    while (b) {
      if (b & 1) result = (result + a) % mod;
      a = (a + a) % mod;
      b >>= 1;
    }
    return result;
  }
  inline LL bigmod(LL num,LL pow,LL mod){
    LL ans = 1;
    for( ;  pow > 0;  pow >>= 1, num = mul(num, num, mod))
      if(pow&1) ans = mul(ans,num,mod);
    return ans;
  }
  inline bool is_prime(LL n){
    if(n < 2 or n % 6 % 4 != 1) return (n|1) == 3;
    LL a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    LL s = __builtin_ctzll(n-1), d = n >> s;
    for(LL x: a){
      LL p = bigmod(x % n, d, n), i = s;
      for( ; p != 1 and p != n-1 and x % n and i--; p = mul(p, p, n));
      if(p != n-1 and i != s) return false;
    }
    return true;
  }
  LL f(LL x, LL n) {
    return mul(x, x, n) + 1;
  }
  LL get_factor(LL n) {
    LL x = 0, y = 0, t = 0, prod = 2, i = 2, q;
    for(  ; t++ %40 or __gcd(prod, n) == 1;   x = f(x, n), y = f(f(y, n), n) ){
      (x == y) ? x = i++, y = f(x, n) : 0;
      prod = (q = mul(prod, max(x,y) - min(x,y), n)) ? q : prod;
    }
    return __gcd(prod, n);
  }
  void _factor(LL n, map <LL, int> &res) {
    if(n == 1) return;
    if(is_prime(n)) res[n]++;
    else {
      LL x = get_factor(n);
      _factor(x, res);
      _factor(n / x, res);
    }
  }
  map <LL, int> factorize(LL n){
    map <LL, int> res;
    if(n < 2)   return res;
    LL small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
    for (LL p: small_primes)
      for( ; n % p == 0; n /= p, res[p]++);
    _factor(n, res);
    return res;
  }
}
