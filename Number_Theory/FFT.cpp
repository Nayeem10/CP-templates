// passes O(3e7) in around 1 sec
// for better precision use long double, sinl, cosl
using CD = complex<double>; 
const double PI = acos(-1.0L);

void precalculate(int n, vector<int> &perm, vector<CD> wp[2]) {
    assert((n & (n - 1)) == 0);  // n must be a power of 2
    perm.assign(n, 0);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < k; i++) {
            perm[i] <<= 1;
            perm[i + k] = 1 + perm[i];
        }
    }
    wp[0].assign(n, CD());
    wp[1].assign(n, CD());
    for (int i = 0; i < n; i++) {
        wp[0][i] = CD(cos(2 * PI * i / n), sin(2 * PI * i / n));
        wp[1][i] = CD(cos(2 * PI * i / n), -sin(2 * PI * i / n));
    }
}

void fft(vector<CD> &v, bool invert = false) {
    int n = v.size();
    static vector<int> perm;
    static vector<CD> wp[2];

    if ((int) perm.size() != n) precalculate(n, perm, wp);

    for (int i = 0; i < n; i++)
        if (i < perm[i]) swap(v[i], v[perm[i]]);

    for (int len = 2; len <= n; len *= 2) {
        for (int i = 0, d = n / len; i < n; i += len) {
            for (int j = 0, idx = 0; j < len / 2; j++, idx += d) {
                CD x = v[i + j];
                CD y = wp[invert][idx] * v[i + j + len / 2];
                v[i + j] = x + y;
                v[i + j + len / 2] = x - y;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < n; i++) v[i] /= n;
    }
}

void pairfft(vector<CD> &a, vector<CD> &b, bool invert = false) {
  int N = a.size();
  vector<CD> p(N);
  for (int i = 0; i < N; i++) p[i] = a[i] + b[i] * CD(0, 1);
  fft(p, invert);
  p.push_back(p[0]);
  for (int i = 0; i < N; i++) {
    if (invert) {
      a[i] = CD(p[i].real(), 0);
      b[i] = CD(p[i].imag(), 0);
    } else {
      a[i] = (p[i] + conj(p[N - i])) * CD(0.5, 0);
      b[i] = (p[i] - conj(p[N - i])) * CD(0, -0.5);
    }
  }
}
vector<LL> multiply(const vector<LL> &a, const vector<LL> &b) {
  int n = 1;
  while (n < (int) a.size() + (int) b.size()) n <<= 1;
  vector<CD> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  fa.resize(n);
  fb.resize(n);
  //        fft(fa); fft(fb);
  pairfft(fa, fb);
  for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
  fft(fa, true);
  vector<LL> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = (LL) llround(fa[i].real());
    return ans;
}
const LL M = 1e15 + 3, B = sqrt(M) + 1;
vector<LL> anyMod(const vector<LL> &a, const vector<LL> &b) {
  int n = 1;
  while (n < (int) a.size() + (int) b.size()) n <<= 1;
  vector<CD> al(n), ar(n), bl(n), br(n);
  for (int i = 0; i < (int) a.size(); i++) al[i] = a[i] % M / B, ar[i] = a[i] % M % B;
  for (int i = 0; i < (int) b.size(); i++) bl[i] = b[i] % M / B, br[i] = b[i] % M % B;
  pairfft(al, ar);
  pairfft(bl, br);
  //        fft(al); fft(ar); fft(bl); fft(br);
  for (int i = 0; i < n; i++) {
    CD ll = (al[i] * bl[i]), lr = (al[i] * br[i]);
    CD rl = (ar[i] * bl[i]), rr = (ar[i] * br[i]);
    al[i] = ll;
    ar[i] = lr;
    bl[i] = rl;
    br[i] = rr;
  }
  pairfft(al, ar, true);
  pairfft(bl, br, true);
  //        fft(al, true); fft(ar, true); fft(bl, true); fft(br, true);
  vector<LL> ans(n);
  for (int i = 0; i < n; i++) {
    LL right = round(br[i].real()), left = round(al[i].real());
    ;
    LL mid = round(round(bl[i].real()) + round(ar[i].real()));
    ans[i] = ((left % M) * B * B + (mid % M) * B + right) % M;
  }
  return ans;
}
