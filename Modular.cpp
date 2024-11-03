class mint {
private:
    long long value;
    static int M;
    void normalize() {
        value %= M;
        if (value < 0) value += M;
    }
    long long mpow(long long x, int n) const {
        if (n == -1) n = M - 2;
        long long ans = 1;
        while (n) {
            if (n & 1) ans = (ans * x) % M;
            n >>= 1;
            x = (x * x) % M;
        }
        return ans;
    }
public:
    mint() : value(0) {}
    mint(int value) : value(value) { normalize(); }
 
    mint& operator=(int value) {
        this->value = value;
        normalize();
        return *this;
    }
 
    mint operator+(const mint& other) const { return mint(value + other.value); }
    mint operator+(int other) const { return mint(value + other); }
    mint operator-(const mint& other) const { return mint(value - other.value); }
    mint operator-(int other) const { return mint(value - other); }
    mint operator*(const mint& other) const { return mint(value * other.value % M); }
    mint operator*(int other) const { return mint(value * other % M); }
    mint operator/(const mint& other) const { return *this * mpow(other.value, -1); }
    mint operator/(int other) const { return *this * mpow(other, -1); }
 
    mint& operator+=(const mint& other) { value += other.value; normalize(); return *this; }
    mint& operator+=(int other) { value += other; normalize(); return *this; }
    mint& operator-=(const mint& other) { value -= other.value; normalize(); return *this; }
    mint& operator-=(int other) { value -= other; normalize(); return *this; }
    mint& operator*=(const mint& other) { value = (value * other.value) % M; normalize(); return *this; }
    mint& operator*=(int other) { value = (value * other) % M; normalize(); return *this; }
    mint& operator/=(const mint& other) { value = (value * mpow(other.value, -1)) % M; normalize(); return *this; }
    mint& operator/=(int other) { value = (value * mpow(other, -1)) % M; normalize(); return *this; }
 
    mint pow(int expo) const { return mint(mpow(value, expo)); }
    mint pow(const mint& expo) const { return mint(mpow(value, expo.value)); }
 
    friend ostream& operator<<(ostream& os, const mint& var) { os << var.value; return os; }
    friend istream& operator>>(istream& is, mint& var) { is >> var.value; var.normalize(); return is; }
 
    int get() const { return value; }
};
 
int mint::M = mod;
 
namespace com {
    mint fact[N], inv[N], inv_fact[N];
 
    void init() {
        fact[0] = inv_fact[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1) ? mint(1) : (inv[i - mod % i] * (mod / i + 1));
            fact[i] = fact[i - 1] * i;
            inv_fact[i] = inv_fact[i - 1] * inv[i];
        }
    }
 
    mint C(int n, int r) {
        return (r < 0 || r > n) ? mint(0) : fact[n] * inv_fact[r] * inv_fact[n - r];
    }
 
    mint P(int n, int r) {
        return (r < 0 || r > n) ? mint(0) : fact[n] * inv_fact[n - r];
    }
 
    mint C(mint &n, int r) { return C(n.get(), r); }
    mint P(mint &n, int r) { return P(n.get(), r); }
 
    mint C(int &n, mint &r) { return C(n, r.get()); }
    mint P(int &n, mint &r) { return P(n, r.get()); }
 
    mint C(mint &n, mint &r) { return C(n.get(), r.get()); }
    mint P(mint &n, mint &r) { return P(n.get(), r.get()); }
}
 
using namespace com;