//Matrix exponentiation : calculating nth fibonacci in logarithmic time

class Matrix {
public:
    int sz;
    vector<vector<int>> Mat;
    Matrix(int n) {
        sz = n;
        Mat = vector<vector<int>>(n, vector<int>(n));
    }
    Matrix operator*(const Matrix &other) {
        Matrix product(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                for (int k = 0; k < sz; k++) {
                    int tmp = (Mat[i][k] * other.Mat[k][j]) % mod;
                    product.Mat[i][j] = (product.Mat[i][j] + tmp) % mod;
                }
            }
        }
        return product;
    }
};

Matrix mat_pow(Matrix a, int p) {
    int n = a.Mat.size(); 
    Matrix product(n);
    for (int i = 0; i < n; i++)
        product.Mat[i][i] = 1;
    while (p > 0) {
        if (p % 2) product = product * a;
        p /= 2;
        a = a * a;
    }
    return product;
}

void solve(){
    int n; cin>>n;
    Matrix m(2);
    m.Mat[0][0] = 0;
    m.Mat[0][1] = 1;
    m.Mat[1][0] = 1;
    m.Mat[1][1] = 1;
    m = mat_pow(m,n-1);
    cout<<m.Mat[0][0]<<ln;
}  