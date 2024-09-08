#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds; 

typedef pair<int,int> pii;
typedef long long ll;

//#define int long long
#define ln '\n'
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_multiset tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>   
#define all(v) v.begin(),v.end()

const int mod=998244353;
const int N=1e6+10;
int inf = 1e8+1;


void Manacher(){
    vector<int> d1(n);
    // d[i] = number of palindromes taking s[i] as center
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;  if (i + k > r) l = i - k, r = i + k;
    }
 
    vector<int> d2(n);
    // d[i] = number of palindromes taking s[i-1] and s[i] as center
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;   if (i + k > r) l = i - k - 1, r = i + k;
    }
}

signed main(){
    faster
    int t=1;
    //cin>>t;
    for(int cs=1;cs<=t;cs++){
        //cout<<"Case "<<cs<<": ";
        solve();
    }
    return 0;
}
