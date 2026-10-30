void gen_drng(int n) {
  drng[2] = 1;
  for (int i = 3; i <= n; i++) 
    drng[i] = ((i - 1ll) * ((drng[i - 2] + drng[i - 1]) % mod)) % mod;
}