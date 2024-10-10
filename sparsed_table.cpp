class SparseTable {
private:
    vector<vector<int>> table;
    vector<int> log;
    int n;

public:
    SparseTable(const vector<int>& arr) {
        n = arr.size();
        log.resize(n + 1);
        buildLog();
        table = vector<vector<int>>(n, vector<int>(log[n] + 1));

        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }
        
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int merge(int a, int b){
        return max(a, b);
    }
    void buildLog() {
        log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }
    }
    int Query(int L, int R) {
        int j = log[R - L + 1];
        return merge(table[L][j], table[R - (1 << j) + 1][j]);
    }
    int query(int L, int R) {
        int sum = 0;
        for (int j = log[R - L + 1]; L <= R; j = log[R - L + 1]) {
            sum = merge(sum, table[L][j]);
            L += (1 << j);
        }
        return sum;
    }
};