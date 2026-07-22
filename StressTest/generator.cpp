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
#define all(v) v.begin(), v.end()

vector<int> get(vector<int> a){
    int n = a.size();
    vector<int> lft(n), ryt(n);   
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(st.size() and a[st.top()] > a[i]) st.pop();
        if(st.size()) lft[i] = i - st.top();
        else lft[i] = i + 1;
        st.push(i);
    }
    
    while(st.size()) st.pop();

    for(int i = n - 1; i >= 0; i--){
        while(st.size() and a[st.top()] > a[i]) st.pop();
        if(st.size()) ryt[i] = st.top() - i;
        else ryt[i] = n - i;
        st.push(i);
    }
    vector<int> ret(n);
    for(int i = 0; i < n; i++)
        ret[i] = lft[i] * ryt[i];
    return ret;
}

int main() {
    int n = 10000;
    cout << n << '\n';
    for(int i = 1; i <= n; i++)
        cout << i << ' ';
    cout << '\n';
}
