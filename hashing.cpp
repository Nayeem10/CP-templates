#define LL long long 
#define PLL pair<long long,long long>

namespace Hashing {           // everything is in long long
    #define ff first
    #define ss second
 
    const PLL M = {1e9+7, 1e9+9};        
    const PLL base = {1259,367};                                
 
    PLL operator+ (const PLL& a, LL x)     {return {a.ff + x, a.ss + x};}
    PLL operator- (const PLL& a, LL x)     {return {a.ff - x, a.ss - x};}
    PLL operator* (const PLL& a, LL x)     {return {a.ff * x, a.ss * x};}
    PLL operator+ (const PLL& a, PLL x)    {return {a.ff + x.ff, a.ss + x.ss};}
    PLL operator- (const PLL& a, PLL x)    {return {a.ff - x.ff, a.ss - x.ss};}
    PLL operator* (const PLL& a, PLL x)    {return {a.ff * x.ff, a.ss * x.ss};}
    PLL operator% (const PLL& a, PLL m)    {return {a.ff % m.ff, a.ss % m.ss};}
    ostream& operator<<(ostream& os, PLL hash) {
        return os<<"("<<hash.ff<<", "<<hash.ss<<")";
    }
    PLL pb[N];     
    void hashPre() {
        pb[0] = {1,1};
        for (int i=1; i<N; i++)     pb[i] = (pb[i-1] * base)%M;
    }
    
    PLL Hash (string s) {
        PLL ans = {0,0};
        for (int i=0; i<s.size(); i++)  ans=(ans*base + s[i])%M;
        return ans;
    }
 
    ///Calculates hashes of all prefixes of s including empty prefix
    vector<PLL> hashList(string s) {
        int n = s.size();
        vector<PLL> ans(n+1);
        ans[0] = {0,0};
        for (int i=1; i<=n; i++)    ans[i] = (ans[i-1] * base + s[i-1])%M;
        return ans;
    }
 
    ///Calculates hash of substring s[l..r] (1 indexed)
    PLL substringHash(const vector<PLL> &hashlist, int l, int r) {
        return (hashlist[r]+(M-hashlist[l-1])*pb[r-l+1])%M;
    }
 
}
using namespace Hashing;