#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <set>
#include <algorithm> 
#include <numeric>

using namespace std;

int main() {
  int t = 1;
  // cin >> t;
  while (t--) {
    int n, m, q;
    cin >> n >> m >> q;
    vector <int> a(n);
    for (int &x : a) scanf("%d", &x), --x;
    vector <int> to(n);
    for (int i = 0; i < n; ++i) to[a[i]] = i;
    vector <int> b(m);
    for (int &x : b) scanf("%d", &x), --x, x = to[x];
    vector <set <int>> where(n);
    for (int i = 0; i < m; ++i) where[b[i]].emplace(i);
    set <pair <int, int>> distinct;
    for (int i = 0; i < n; ++i) if (!where[i].empty()) distinct.emplace(*where[i].begin(), i);
    int adjacent = 0;
    for (auto it = distinct.begin(); next(it) != distinct.end(); it = next(it)) {
      if (it -> second + 1 == next(it) -> second) ++adjacent;
    }
    auto check = [&] () {
      if (distinct.begin() -> second == 0 and adjacent + 1 == (int) distinct.size()) puts("YA");
      else puts("TIDAK");
    };
    auto remove = [&] (int i) {
      int x = b[i];
      if (*where[x].begin() != i) {
        where[x].erase(i);
        return;
      }
      where[x].erase(where[x].begin());
      auto it = distinct.find(make_pair(i, x));
      if (it != distinct.begin() and prev(it) -> second + 1 == it -> second) --adjacent;
      if (next(it) != distinct.end() and it -> second + 1 == next(it) -> second) --adjacent;
      if (it != distinct.begin() and next(it) != distinct.end() and prev(it) -> second + 1 == next(it) -> second) ++adjacent;
      distinct.erase(it);
      if (!where[x].empty()) {
        auto it = distinct.emplace(*where[x].begin(), x).first;
        if (it != distinct.begin() and prev(it) -> second + 1 == it -> second) ++adjacent;
        if (next(it) != distinct.end() and it -> second + 1 == next(it) -> second) ++adjacent;
        if (it != distinct.begin() and next(it) != distinct.end() and prev(it) -> second + 1 == next(it) -> second) --adjacent;
      }
    };
    auto insert = [&] (int i) {
      int x = b[i];
      if (!where[x].empty() and i > *where[x].begin()) {
        where[x].emplace(i);
        return;
      }
      if (!where[x].empty()) {
        auto it = distinct.find(make_pair(*where[x].begin(), x));
        if (it != distinct.begin() and prev(it) -> second + 1 == it -> second) --adjacent;
        if (next(it) != distinct.end() and it -> second + 1 == next(it) -> second) --adjacent;
        if (it != distinct.begin() and next(it) != distinct.end() and prev(it) -> second + 1 == next(it) -> second) ++adjacent;
        distinct.erase(it);
      }
      auto it = distinct.emplace(i, x).first;
      if (it != distinct.begin() and prev(it) -> second + 1 == it -> second) ++adjacent;
      if (next(it) != distinct.end() and it -> second + 1 == next(it) -> second) ++adjacent;
      if (it != distinct.begin() and next(it) != distinct.end() and prev(it) -> second + 1 == next(it) -> second) --adjacent;
      where[x].emplace(i);
    };
    check();
    while (q--) {
      int x, y;
      scanf("%d %d", &x, &y), --x, --y;
      remove(x), b[x] = to[y], insert(x), check();
    }
  }    
  return 0;
}

