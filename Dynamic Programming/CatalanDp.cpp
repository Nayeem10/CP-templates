// comb formula: ((2n)Cn)-((2n)C(n-1)) = (1/(n+1))*((2n)Cn)
void genCatalan(int n) {
  catalan[0] = catalan[1] = 1;
  for (int i = 2; i <= n; i++) {
    catalan[i] = 0;
    for (int j = 0; j < i; j++) {
      catalan[i] += (catalan[j] * catalan[i - j - 1]) % mod;
      if (catalan[i] >= mod) {
        catalan[i] -= mod;
      } } } 
}