#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define PLL pair<long long, long long>
#define LL long long

#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(), v.end()

const LL mod = 1e9 + 7;
const int N = 4e5 + 10;
const int inf = 1e9 + 7;
const LL INF = 1e18;

double dp[101][101][101];

void solve(int tc){
    int r, s, p; cin >> r >> s >> p;
    double ansr = 0, anss = 0, ansp = 0;
    dp[r][s][p] = 1;
    for(int i = r; i >= 0; i--){
        for(int j = s; j >= 0; j--){
            for(int k = p; k >= 0; k--){
                LL tot = i * j + j * k + k * i;
                if(tot == 0){
                    if(j == 0 and k == 0) ansr += dp[i][j][k];
                    if(k == 0 and i == 0) anss += dp[i][j][k];
                    if(i == 0 and j == 0) ansp += dp[i][j][k];
                    continue;
                }
                if(j) dp[i][j - 1][k] += dp[i][j][k] * i * j / tot;
                if(k) dp[i][j][k - 1] += dp[i][j][k] * j * k / tot;
                if(i) dp[i - 1][j][k] += dp[i][j][k] * k * i / tot;                
            }
        }
    }
    cout << fixed << setprecision(9) << ansr << ' ' << anss << ' ' << ansp << '\n';

} 

signed main() {
    faster
    int t = 1;
    // cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve(tc);
    }
    return 0;
}