template <typename T>
vector<int> getLPSarray(T& b) {
  int m = b.size();
  vector<int> phi(m);
  for (int i = 1, j = 0; i < m; i++) {
    while (j && b[i] != b[j]) j = phi[j - 1];
    if (b[i] == b[j]) j++;
    phi[i] = j;
  } return phi;
}
template <typename T>
int KMP_match(T& a, T& b) {
  int n = a.size(), m = b.size();
  vector<int> lps = getLPSarray(b);
  int i = 0, j = 0, cnt = 0;
  while (n - i >= m - j) {
    if (a[i] == b[j]) i++, j++;
    if (j == m) cnt++, j = lps[j - 1];
    else if (i < n && a[i] != b[j]) {
      if (j) j = lps[j - 1];
      else i++;
  } }
  return cnt;
}
