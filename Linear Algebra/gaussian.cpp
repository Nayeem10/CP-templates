
struct Mint {
    static const LL MOD = 1e9 + 7;
    LL val;

    Mint(LL v = 0) {
        val = v % MOD;
        if (val < 0) val += MOD;
    }

    Mint operator + (const Mint &other) const { return Mint(val + other.val); }
    Mint operator - (const Mint &other) const { return Mint(val - other.val); }
    Mint operator * (const Mint &other) const { return Mint(val * other.val); }

    static Mint power(Mint a, LL p) {
        Mint res = 1;
        while (p) {
            if (p & 1) res = res * a;
            a = a * a;
            p >>= 1;
        }
        return res;
    }

    Mint inv() const { return power(*this, MOD - 2); } // MOD must be prime

    Mint operator / (const Mint &other) const {
        return *this * other.inv();
    }
};

/* ================= GAUSSIAN ELIMINATION ================= */

template<typename T>
struct Gauss {
    int n, m;                  // n = equations, m = variables
    vector<vector<T>> a;       // augmented matrix
    vector<T> solution;        // stores solution if unique
    T determinant = 1;

    Gauss(int n, int m) : n(n), m(m) {
        a.assign(n, vector<T>(m + 1));
    }

    // set coefficient matrix and RHS
    void set_row(int i, vector<T> row) {
        a[i] = row;   // size must be m+1
    }

    // returns:
    // 0 = no solution
    // 1 = unique solution
    // 2 = infinite solutions
    int solve() {
        const double EPS = 1e-12;
        int rank = 0;
        determinant = 1;

        for (int col = 0; col < m && rank < n; col++) {

            // partial pivoting
            int pivot = rank;
            for (int i = rank; i < n; i++) {
                if (abs((double)a[i][col]) > abs((double)a[pivot][col]))
                    pivot = i;
            }

            if (abs((double)a[pivot][col]) < EPS) {
                determinant = 0;
                continue;
            }

            swap(a[pivot], a[rank]);

            if (pivot != rank)
                determinant = determinant * T(-1);

            determinant = determinant * a[rank][col];

            // normalize pivot row
            T inv_pivot = T(1) / a[rank][col];
            for (int j = col; j <= m; j++)
                a[rank][j] = a[rank][j] * inv_pivot;

            // eliminate other rows
            for (int i = 0; i < n; i++) {
                if (i != rank && abs((double)a[i][col]) > EPS) {
                    T factor = a[i][col];
                    for (int j = col; j <= m; j++)
                        a[i][j] = a[i][j] - factor * a[rank][j];
                }
            }

            rank++;
        }

        // check consistency
        for (int i = rank; i < n; i++) {
            if (abs((double)a[i][m]) > EPS)
                return 0;  // no solution
        }

        if (rank < m)
            return 2;      // infinite solutions

        // unique solution
        solution.assign(m, 0);
        for (int i = 0; i < m; i++)
            solution[i] = a[i][m];

        return 1;
    }

    T get_determinant() const {
        return determinant;
    }

    vector<T> get_solution() const {
        return solution;
    }
};