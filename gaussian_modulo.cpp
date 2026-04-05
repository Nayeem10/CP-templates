#include <bits/stdc++.h>
using namespace std;

/* ================= MODULAR INTEGER ================= */

template<int MOD>
struct Mint {
    long long val;

    Mint(long long v = 0) {
        val = v % MOD;
        if (val < 0) val += MOD;
    }

    Mint operator + (const Mint &other) const {
        return Mint(val + other.val);
    }

    Mint operator - (const Mint &other) const {
        return Mint(val - other.val);
    }

    Mint operator * (const Mint &other) const {
        return Mint(val * other.val);
    }

    static Mint power(Mint a, long long p) {
        Mint res = 1;
        while (p) {
            if (p & 1) res = res * a;
            a = a * a;
            p >>= 1;
        }
        return res;
    }

    Mint inv() const {   // MOD must be prime
        return power(*this, MOD - 2);
    }

    Mint operator / (const Mint &other) const {
        return *this * other.inv();
    }
};

/* ================= MODULAR GAUSSIAN ELIMINATION ================= */

template<typename T>
struct Gauss {
    int n, m;                   // n equations, m variables
    vector<vector<T>> a;        // augmented matrix
    vector<T> solution;
    T determinant = 1;

    Gauss(int n, int m) : n(n), m(m) {
        a.assign(n, vector<T>(m + 1));
    }

    void set_row(int i, const vector<T>& row) {
        a[i] = row;             // size must be m+1
    }

    // returns:
    // 0 = no solution
    // 1 = unique solution
    // 2 = infinite solutions
    int solve() {
        int rank = 0;
        determinant = 1;

        for (int col = 0; col < m && rank < n; col++) {

            int pivot = -1;
            for (int i = rank; i < n; i++) {
                if (a[i][col].val != 0) {
                    pivot = i;
                    break;
                }
            }

            if (pivot == -1) {
                determinant = 0;
                continue;
            }

            swap(a[pivot], a[rank]);
            if (pivot != rank)
                determinant = determinant * T(-1);

            determinant = determinant * a[rank][col];

            T inv_pivot = T(1) / a[rank][col];

            // normalize pivot row
            for (int j = col; j <= m; j++)
                a[rank][j] = a[rank][j] * inv_pivot;

            // eliminate other rows
            for (int i = 0; i < n; i++) {
                if (i != rank && a[i][col].val != 0) {
                    T factor = a[i][col];
                    for (int j = col; j <= m; j++)
                        a[i][j] = a[i][j] - factor * a[rank][j];
                }
            }

            rank++;
        }

        // check consistency
        for (int i = rank; i < n; i++) {
            if (a[i][m].val != 0)
                return 0; // no solution
        }

        if (rank < m)
            return 2; // infinite solutions

        // unique solution
        solution.assign(m, 0);
        for (int i = 0; i < m; i++)
            solution[i] = a[i][m];

        return 1;
    }

    vector<T> get_solution() const {
        return solution;
    }

    T get_determinant() const {
        return determinant;
    }
};