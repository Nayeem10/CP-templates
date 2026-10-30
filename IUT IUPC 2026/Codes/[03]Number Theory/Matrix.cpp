template <typename DT>
struct Matrix {
  vector<vector<DT>> mat;
  Matrix(vector<vector<DT>>& mat) : mat(mat) {}
  Matrix(int n) : mat(n, vector<DT>(n)) {
    for (int i = 0; i < n; i++) {
      mat[i][i] = 1;
  } }
  Matrix(int n, int m) : mat(n, vector<DT>(m)) {}
  Matrix operator*(Matrix& other) {
    auto &a = mat, &b = other.mat;
    assert(a[0].size() == b.size());
    int n = a.size(), m = b[0].size(), s = a[0].size();
    Matrix<DT> ret(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        DT temp = 0;
        for (int k = 0; k < s; k++) {
          temp = (temp + 1LL * a[i][k] * b[k][j] % MOD) % MOD;
        }
        ret.mat[i][j] = temp;
    } }
    return ret;
} };