template <typename T>
class BIT {
    int N;
    vector<T> bit;
public:
    BIT(int n) : N(n + 5), bit(N + 1, T{}) {}
    void update(int id, T val) {
        id++;
        for (; id <= N; id += id & -id)
            bit[id] += val;
    }
    T prefix_sum(int id) const {
        id++;
        T sum = T{};
        for (; id > 0; id -= id & -id)
            sum += bit[id];
        return sum;
    }
    T query(int l, int r) const {
        if (l > r) return T{};
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};