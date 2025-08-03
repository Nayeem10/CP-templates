#include <bits/stdc++.h>
using namespace std;
using LL = long long;

mt19937 rng(random_device{}());

// Generate a random integer in the range [low, high]
LL randomInt(LL low, LL high) {
    uniform_int_distribution<LL> dist(low, high);
    return dist(rng);
}

// Generates unique (vi, pi) pairs
set<pair<int, int>> generateUniqueSoundPairs(int n, int m) {
    set<pair<int, int>> sounds;
    while ((int)sounds.size() < n) {
        int vi = randomInt(1, m);
        int pi = randomInt(1, m);
        sounds.insert({vi, pi}); // Ensures uniqueness
    }
    return sounds;
}

vector<pair<int, int>> generate_random_tree(int n) {
    vector<int> prufer(n - 2);

    for (int i = 0; i < n - 2; ++i) {
        prufer[i] = randomInt(1, n); // Random number in [1, n]
    }

    vector<int> degree(n + 1, 1);
    for (int x : prufer) {
        degree[x]++;
    }

    // Min-heap for the leaves (nodes with degree 1)
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) pq.push(i);
    }

    vector<pair<int, int>> edges;
    for (int x : prufer) {
        int leaf = pq.top(); pq.pop();
        edges.emplace_back(leaf, x);

        degree[leaf]--;
        degree[x]--;

        if (degree[x] == 1) pq.push(x);
    }

    // Last two remaining nodes
    int u = pq.top(); pq.pop();
    int v = pq.top(); pq.pop();
    edges.emplace_back(u, v);

    return edges;
}


int main() {
    int mxN = 1e5, mxM = 5000, mxQ = 1e5, mxX = 1e9, mxK = 1e9;
    int totalN = 0, totalQ = 0;
    int maxT = 10000;
    vector<string> testcases;

    for (int tc = 0; tc < maxT; ++tc) {
        // Limit remaining room
        int maxN = min(mxN - totalN, 1000);
        int maxQ = min(mxQ - totalQ, 1000);
        if (maxN == 0 || maxQ == 0) break;

        int n = randomInt(1, maxN);
        int m = randomInt(1, mxM);
        int q = randomInt(1, maxQ);

        totalN += n;
        totalQ += q;

        stringstream ss;
        ss << n << ' ' << m << '\n';
        for (int i = 0; i < n; ++i) {
            ss << randomInt(1, mxX) << " \n"[i == n - 1];
        }
        ss << q << '\n';

        while (q--) {
            int t = randomInt(1, 100) % 2 + 1;
            ss << t << ' ';
            if (t == 1) {
                int i = randomInt(1, n), x = randomInt(1, mxX);
                ss << i << ' ' << x << '\n';
            } else {
                int l = randomInt(1, n), r = randomInt(l, n), k = randomInt(1, mxK);
                ss << l << ' ' << r << ' ' << k << '\n';
            }
        }

        testcases.push_back(ss.str());
    }

    cout << testcases.size() << '\n';
    for (auto &tc : testcases) {
        cout << tc;
    }
}
