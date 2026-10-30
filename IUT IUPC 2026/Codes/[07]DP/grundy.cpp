/* single pile game-> greedy or game dp multiple pile game and
 * disjunctive(before playing, choose 1 pile) -> NIM game else-> Grundy(converts
 * n any game piles to n NIM piles) grundy(x)->the smallest nonreachable grundy
 * value there are n pile of games and k type of moves. if XOR(grundy(games)) ==
 * 0: losing state else winning state */
vector<int> moves, dp;
int mex(vector<int>& a) {
  set<int> b(a.begin(), a.end());
  for (int i = 0;; ++i)
    if (!b.count(i)) return i;
}
int grundy(int x) {
  if (dp[x] != -1) return dp[x];
  vector<int> reachable;
  for (auto m : moves) {
    if (x - m < 0) continue;
    int val = grundy(x - m);
    reachable.push_back(val);
  }
  return dp[x] = mex(reachable);
}