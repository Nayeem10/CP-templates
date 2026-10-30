// Some Primes : 1000000007, 1000000009, 1000000861, 1000099999(< 2 ^ 30)1088888881, 1111211111, 1500000001, 1481481481(< 2 ^ 31)
namespace Hashing {
#define ff first 
#define ss second
const PLL M = {1e9 + 7, 1e9 + 9};
const LL base = 1259; const int N = 1e6 + 7;
PLL operator+(const PLL& a, LL x) { return {a.ff + x, a.ss + x}; }
PLL operator-(const PLL& a, LL x) { return {a.ff - x, a.ss - x}; }
PLL operator*(const PLL& a, LL x) { return {a.ff * x, a.ss * x}; }
PLL operator+(const PLL& a, PLL x) { return {a.ff + x.ff, a.ss + x.ss}; }
PLL operator-(const PLL& a, PLL x) { return {a.ff - x.ff, a.ss - x.ss}; }
PLL operator*(const PLL& a, PLL x) { return {a.ff * x.ff, a.ss * x.ss}; }
PLL operator%(const PLL& a, PLL m) { return {a.ff % m.ff, a.ss % m.ss}; }
ostream& operator<<(ostream& os, PLL hash) {
  return os << "(" << hash.ff << ", " << hash.ss << ")"; 
}
PLL pb[N]; 
void hashPre() { pb[0] = {1, 1}; for (int i = 1; i < N; i++) pb[i] = (pb[i - 1] * base) % M; }
vector<PLL> hashList(string s) {
  int n = s.size(); vector<PLL> ans(n + 1); ans[0] = {0, 0};
  for (int i = 1; i <= n; i++) ans[i] = (ans[i - 1] * base + s[i - 1]) % M;
  return ans;
}
PLL substringHash(const vector<PLL>& hashlist, int l, int r) {
  return (hashlist[r] + (M - hashlist[l - 1]) * pb[r - l + 1]) % M;
}
PLL Hash(string s) { PLL ans = {0, 0}; for (int i = 0; i < s.size(); i++) ans = (ans * base + s[i]) % M; return ans; }
PLL append(PLL cur, char c) { return (cur * base + c) % M; }
PLL prepend(PLL cur, int k, char c) { return (pb[k] * c + cur) % M; } ///replaces the i-th (0-indexed) character from right from a to b;
PLL replace(PLL cur, int i, char a, char b) { return (cur + pb[i] * (M + b - a)) % M; } ///Erases c from front of the string with size len
PLL pop_front(PLL hash, int len, char c) { return (hash + pb[len - 1] * (M - c)) % M; } ///concatenates two strings where length of the right is k
PLL concat(PLL left, PLL right, int k) { return (left * pb[k] + right) % M; }
PLL inverse(PLL a) {
  if (M.ss == 1) return bigmod(a, M.ff - 2);
  return bigmod(a, (M.ff - 1) * (M.ss - 1) - 1);
} ///Erases c from the back of the string
PLL invb = inverse({base, base});
PLL pop_back(PLL hash, char c) { return ((hash - c + M) * invb) % M; } ///Calculates hash of string with size len repeated cnt times 
///This is O(log n). For O(1), pre-calculate inverses
PLL repeat(PLL hash, int len, LL cnt) {
  PLL mul = ((pb[len * cnt] - 1 + M) * inverse(pb[len] - 1 + M)) % M;
  PLL ans = (hash * mul);
  if (pb[len].ff == 1) ans.ff = hash.ff * cnt;
  if (pb[len].ss == 1) ans.ss = hash.ss * cnt;
  return ans % M;
} } 