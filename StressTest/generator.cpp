#include <bits/stdc++.h>
using namespace std;
using LL = long long;

mt19937 rng(random_device{}());
LL randomInt(LL low, LL high) {
    uniform_int_distribution<LL> dist(low, high);
    return dist(rng);
}

string generateRandomString(int length) {
    string s = "";
    string alphanum = "abcdefghijklmnopqrstuvwxyz0123456789"; // [0, 25] --> alphabet, [26, 35] --> digit
    for (int i = 0; i < length; ++i) {
        s += alphanum[randomInt(26, 35)];
    }
    return s;
}

vector<int> permutation(int n){
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    return p;
}


int main() {
    LL N = 1e18;
    LL l = randomInt(1, N), r = randomInt(l, N), i = randomInt(0, 30), k = randomInt(0, (1LL << i) - 1);
    cout<<l<<" "<<r<<" "<<i<<" "<<k<<'\n';
    return 0;
}
