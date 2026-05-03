class SparsedTable {
private:
    vector<vector<int>> table;
    vector<int> log;
    int n;

public:
    SparsedTable(const vector<int>& arr) {
        n = arr.size();
        log.resize(n + 1);
        buildLog();

        table = vector<vector<int>>(log[n] + 1, vector<int>(n));

        for (int i = 0; i < n; i++) {
            table[0][i] = arr[i];
        }

        for (int j = 1; j <= log[n]; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[j][i] = merge(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int merge(int a, int b) {
        return a | b; 
    }

    void buildLog() {
        log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }
    }

    int Query(int L, int R) {
        int j = log[R - L + 1];
        return merge(table[j][L], table[j][R - (1 << j) + 1]);
    }

    int query(int L, int R) {
        int sum = 0;
        for (int j = log[R - L + 1]; L <= R; j = log[R - L + 1]) {
            sum = merge(sum, table[j][L]);
            L += (1 << j);
        }
        return sum;
    }

    void update(int L, int R, int val) {
        int j = log[R - L + 1];
        table[j][L] = min(table[j][L], val);
        table[j][R - (1 << j) + 1] = min(table[j][R - (1 << j) + 1], val);
    }

    void finalize() {
        for (int j = log[n]; j > 0; j--) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[j - 1][i] = min(table[j - 1][i], table[j][i]);
                table[j - 1][i + (1 << (j - 1))] = min(table[j - 1][i + (1 << (j - 1))], table[j][i]);
            }
        }
    }
};
