
vector<int> sieve(const int N, const int Q = 17, const int L = 1 << 15) {
  static const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
  struct P { 
    P(int p) : p(p) {}
    int p; int pos[8];
  };
  auto approx_prime_count = [] (const int N) -> int {
    return N > 60184 ? N / (log(N) - 1.1)
                     : max(1., N / (log(N) - 1.11)) + 1;
  };

  const int v = sqrt(N), vv = sqrt(v);
  vector<bool> isp(v + 1, true);
  for (int i = 2; i <= vv; ++i) if (isp[i]) {
    for (int j = i * i; j <= v; j += i) isp[j] = false;
  }

  const int rsize = approx_prime_count(N + 30);
  vector<int> primes = {2, 3, 5}; int psize = 3;
  primes.resize(rsize);

  vector<P> sprimes; size_t pbeg = 0;
  int prod = 1; 
  for (int p = 7; p <= v; ++p) {
    if (!isp[p]) continue;
    if (p <= Q) prod *= p, ++pbeg, primes[psize++] = p;
    auto pp = P(p); 
    for (int t = 0; t < 8; ++t) {
      int j = (p <= Q) ? p : p * p;
      while (j % 30 != rs[t]) j += p << 1;
      pp.pos[t] = j / 30;
    }
    sprimes.push_back(pp);
  }

  vector<unsigned char> pre(prod, 0xFF);
  for (size_t pi = 0; pi < pbeg; ++pi) {
    auto pp = sprimes[pi]; const int p = pp.p;
    for (int t = 0; t < 8; ++t) {
      const unsigned char m = ~(1 << t);
      for (int i = pp.pos[t]; i < prod; i += p) pre[i] &= m;
    }
  }

  const int block_size = (L + prod - 1) / prod * prod;
  vector<unsigned char> block(block_size); unsigned char* pblock = block.data();
  const int M = (N + 29) / 30;

  for (int beg = 0; beg < M; beg += block_size, pblock -= block_size) {
    int end = min(M, beg + block_size);
    for (int i = beg; i < end; i += prod) {
      copy(pre.begin(), pre.end(), pblock + i);
    }
    if (beg == 0) pblock[0] &= 0xFE;
    for (size_t pi = pbeg; pi < sprimes.size(); ++pi) {
      auto& pp = sprimes[pi];
      const int p = pp.p;
      for (int t = 0; t < 8; ++t) {
        int i = pp.pos[t]; const unsigned char m = ~(1 << t);
        for (; i < end; i += p) pblock[i] &= m;
        pp.pos[t] = i;
      }
    }
    for (int i = beg; i < end; ++i) {
      for (int m = pblock[i]; m > 0; m &= m - 1) {
        primes[psize++] = i * 30 + rs[__builtin_ctz(m)];
      }
    }
  }
  assert(psize <= rsize);
  while (psize > 0 && primes[psize - 1] > N) --psize;
  primes.resize(psize);
  return primes;
}


mod = {1500000007, 1500000013, 1500000023, 1500000057, 1500000077};
1. Sieve
const int N = 1e6;
int divisor[N+1];
void sieve(){                        
	for(int i=1;i<=N;i++) divisor[i]=i;
	for(int i=2;i<=N;i+=2) divisor[i]=2;
	for(int i=3;i<=N;i+=2){
		if(divisor[i]==i){
			for(int j=i*i;j<=N;j+=i){   
				if(divisor[j]==j) divisor[j]=i;
			}
		}
	}
}
2. Pollard rho 
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
3. Eulars Totient Function
int phi(int n){
	int ret=n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			while(n%p==0) n/=i;
			ret -= ret/i;
		}
	}
	if(n>1) ret -= ret/n;
	return ret;
}
void phi_in_range(){
	int N=1e6, phi[N+1];
	for(int i=0;i<=N;i++) phi[i] = i;
	for(int i=2;i<=N;i++){
		if(phi[i] != i) continue;
		for(int j=i;j<=N;j+=i){
			phi[j] -= phi[j]/i;
		}
	}
}

#some important properties of phi
phi(p) = p-1  ,where p is a prime number
phi(a*b) = phi(a)*phi(b)  ,where a and b are co-prime
phi(a*b) = phi(a)*phi(b)*(gcd(a,b)/phi(gcd(a,b)))  ,for any number
phi(p^k) = p^k - p^(k-1)  ,where p is a prime number, '^' indicates power
Sum of values of totient functions of all divisors of n is equal to n.
4. Big MOD
int bigmod(int x, int n, int mod) {
    int ans = 1;
    while(n) {
        if((n & 1)) ans = (ans * x) % mod;
        n >>= 1;
        x = (x * x) % mod;
    }
    return ans;
}
5. Chinese reminder theorem
using LL = long long;
using PLL = pair <LL,LL>;
// given a, b will find solutions for, ax + by = 1
tuple <LL,LL,LL> EGCD(LL a, LL b){
    if(b == 0) return {1, 0, a};
    else{
        auto [x,y,g] = EGCD(b, a%b);
        return {y, x - a/b*y,g};
    }
}
// given modulo equations, will apply CRT
PLL CRT(vector <PLL> &v){
    LL V = 0, M = 1;
    for(auto &[v, m]:v){ //value % mod
        auto [x, y, g] = EGCD(M, m);
        if((v - V) % g != 0)
            return {-1, 0};
        V += x * (v - V) / g % (m / g) * M, M *= m / g;
        V = (V % M + M) % M;
    }
    return make_pair(V, M);
}
6.combinatorics
/*  Given n boxes, each box has cnt[i] different (distinct) items, 
    you can take only 1 object from each box. how many different combinations
    of choices are there  */
ll call(ll box, ll take, vector <ll> &cnt){
    vector < vector <int>> DP(box+1, vector <int> (take+2));
    dp[0][0] = 1, dp[0][1] = cnt[0];
    for(int s = 0; s <= take; s++){
        for(int idx = 0; idx < box; idx++){
            dp[idx+1][s] = ( dp[idx+1][s] + dp[idx][s]);
            dp[idx+1][s+1] = (dp[idx+1][s+1] + dp[idx][s] * cnt[idx+1][s]);
        }
    }
    return dp[box-1][take];
}
7.nCr
namespace com{
    int fact[N], inv[N], inv_fact[N];
    void init(){
        fact[0] = inv_fact[0] = 1;
        for(int i = 1; i < N; i++){
            inv[i] = i == 1 ? 1 : inv[i - mod%i] * (mod/i + 1) % mod;
            fact[i] = fact[i-1] * i % mod;
            inv_fact[i] = inv_fact[i-1] * inv[i] % mod;
        }
    }
    int C(int n,int r){
        return (r < 0 or r > n) ? 0 : fact[n] * inv_fact[r] % mod * inv_fact[n-r] % mod;
    }
    int fac(int n){
        return fact[n];
    }
}
using namespace com;
8. nod & sod
namespace sieve{
  const int N = 1e7;
  vector <int> primes;
  int spf[N+5], phi[N+5], NOD[N+5], cnt[N+5], POW[N+5]; 
  bool prime[N+5];
  int SOD[N+5];
  void init(){
    fill(prime+2, prime+N+1, 1);
    SOD[1] = NOD[1] = phi[1] = spf[1] = 1;
    for(LL i=2;i<=N;i++){
      if(prime[i]) {
        primes.push_back(i), spf[i] = i;
        phi[i] = i-1;
        NOD[i] = 2, cnt[i] = 1;
        SOD[i] = i+1, POW[i] = i;
      }
      for(auto p:primes){
        if(p*i>N or p > spf[i]) break;
        prime[p*i] = false, spf[p*i] = p;
        if(i%p == 0){
          phi[p*i]=p*phi[i];
          NOD[p*i]=NOD[i]/(cnt[i]+1)*(cnt[i]+2), cnt[p*i]=cnt[i]+1;
          SOD[p*i]=SOD[i]/SOD[POW[i]]*(SOD[POW[i]]+p*POW[i]),POW[p*i]=p*POW[i];
          break;
        } else {
          phi[p*i]=phi[p]*phi[i];
          NOD[p*i]=NOD[p]*NOD[i], cnt[p*i]=1;
          SOD[p*i]=SOD[p]*SOD[i], POW[p*i]=p;
        }
      }
    }
  }
  // O(lg n factorization for small numbers upto sieve)
  map <ULL,int> fast_factorize(ULL n){
      map <ULL,int> ans;
      for(;n>1;n/=spf[n])
          ans[spf[n]]++;
      return ans;
  }
  // factorization for big numbers
  // using pollard rho might be better
  map <ULL,int> factorize(ULL n){
      int cnt = 0;
      map <ULL,int> ans;
      for(auto p:primes){
          if(p*p>n) break;
          for(;n%p==0;n/=p)
              ans[p]++;
      }
      if(n!=1) ans[n]++;
      return ans;
  }
  // only for large numbers
  int number_of_div(ULL n){
      if(n < 1) return 0;
      auto A = factorize(n);
      int ans = 1;
      for(auto [p,cnt]:A)
          ans *= cnt+1;
      return ans;
  }
  ULL sum_of_div(ULL n){
      if(n < 1) return 0;
      ULL ans = 1, ppow;
      for(ULL p:primes){
          if(p*p > n) break;
          for(ppow=p; n%p==0; n/=p,ppow*=p);
          ans *=(ppow-1)/(p-1);
      }
      return n == 1 ? ans: ans*(1+n);
  }
  ULL PHI(ULL n){
      ULL ans = n;
      for(auto [p,cnt]:factorize(n))
          ans = ans/p*(p-1); 
      return ans;
  }
}
9. divisor 
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

10. Matrix
int n;
struct Matrix{
  vector<vector<LL>> Mat = vector<vector<LL>>(n, vector<LL>(n));
    // memset(Mat,0,sizeof(Mat));
  Matrix operator*(const Matrix &other){
	  Matrix product;
	  for (int i = 0; i < n; i++){
	    for (int j = 0; j < n; j++){
	      for (int k = 0; k < n; k++){
	        LL temp = ((Mat[i][k] % mod)*(other.Mat[k][j]%mod))%mod;
	        product.Mat[i][j] = (product.Mat[i][j] % mod + temp % mod) % mod;
	      }
	    }
	  }
	  return product;
  }
};
Matrix MatExpo(Matrix a, int p){
  Matrix product;
  for (int i = 0; i < n; i++)
    product.Mat[i][i] = 1;
  while (p > 0){
    if (p % 2) product = product * a;
    p /= 2;
    a = a * a;
  }
  return product;
}
11.Bitwise sieve
const int nmax = 1e8+1;
int mark[(nmax>>6)+1];
vector<int> primes;
#define isSet(n,pos) (bool)((n) & (1LL<<(pos)))
#define Set(n,pos) ((n) | (1LL<<(pos)))
void sieve(int n){
	for(int i=3;i*i<=n;i+=2){
		if(isSet(mark[i>>6],(i>>1) & 31)==0){
			for(int j=i*i;j<=n;j+=(i<<1))
				mark[j>>6]=Set(mark[j>>6],(j>>1) & 31);
		}
	}
	primes.push_back(2);
	for(int i=3;i<=n;i+=2){
		if(isSet(mark[i>>6],(i>>1) & 31)==0)
			primes.push_back(i);
	}
}
