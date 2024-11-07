/**
 *    author:  tourist
 *    created: 02.11.2024 07:47:40
**/
#include <bits/stdc++.h>

using namespace std;



int64_t Solve(int64_t n, int i, int k) {
  int64_t ans = 0;
  for (int r = 0; r < n % 4; r++) {
    ans ^= n - n % 4 + r;
  }
  n -= k + 1;
  if (n >= 0) {
    n >>= i;
    n += 1;
    for (int r = 0; r < n % 4; r++) {
      ans ^= (n - n % 4 + r) << i;
    }
    if (n % 2 == 1) {
      ans ^= k;
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  // cin >> tt;
  while (tt--) {
    int64_t l, r;
    int i, k;
    cin >> l >> r >> i >> k;
    cout << (Solve(r + 1, i, k) ^ Solve(l, i, k)) << '\n';
  }
  return 0;
}
