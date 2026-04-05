class mint {
private:
    long long value;
    static int M;

    void normalize() {
        value %= M;
        if (value < 0) value += M;
    }
    static mint powmod(mint x, long long n) {
        if (n < 0) n += M - 1;
        mint res = 1;
        while (n) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }
public:
    mint(long long v = 0) : value(v) { normalize(); }
    static void set_mod(int mod) { M = mod; }
    long long val() const { return value; }

    /* arithmetic operators */
    mint operator+(const mint& o) const { return mint(value + o.value); }
    mint operator-(const mint& o) const { return mint(value - o.value); }
    mint operator*(const mint& o) const { return mint(value * o.value); }
    mint operator/(const mint& o) const { return *this * powmod(o, M - 2); }

    /* compound assignment */
    mint& operator+=(const mint& o) { value += o.value; normalize(); return *this; }
    mint& operator-=(const mint& o) { value -= o.value; normalize(); return *this; }
    mint& operator*=(const mint& o) { value = (value * o.value) % M; return *this; }
    mint& operator/=(const mint& o) { return *this *= powmod(o, M - 2); }

    /* comparison */
    bool operator==(const mint& o) const { return value == o.value; }
    bool operator!=(const mint& o) const { return value != o.value; }

    friend ostream& operator<<(ostream& os, const mint& m) {
        return os << m.value;
    }
    friend istream& operator>>(istream& is, mint& m) {
        is >> m.value; m.normalize(); return is;
    }
};

int mint::M = mod;