#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds; 

typedef pair<long long,long long> pii;
typedef long long ll;

#define int long long
#define ln '\n'
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>   
#define all(v) v.begin(),v.end()

const int mod=998244353;
const int N=2e6+1;
const int inf = 1e15;

inline void debugMode() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}

inline void runtime(clock_t tStart){
    #ifndef ONLINEJUDGE
    fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}


void sieve(int ss[]){
    for(int i=2;i<=N;i+=2)ss[i]=2;

    for(int i=3;i*i<=N;i+=2){
        if(ss[i]==0){
            for(int j=i*i;j<=N;j+=i){
                if(ss[j])continue;
                ss[j]=i;
            }
        }
    }
}

template<typename T>
class calckmp {
    void computelps(vector<int> &lps,T &b,int m){
        int len=0;
        lps[0]=0;                   //emon array banabo jate na mille ager position er lps er sathe match kora shuru korte hobe
        int i=1;
        while(i<m){
            if(b[i]==b[len]){
                len++; 
                lps[i]=len;
                i++;
            }else{
                if(len)
                    len = lps[len-1];
                else
                    lps[i]=0, i++;     // paterrn er 0th index match na korle main array er iteretor samne niye jabo
            }
        }
    }
    
public:
    int match(T &a,T &b){
        int n=a.size();
        int m=b.size();
        vector<int> lps(m);
        int cnt=0;
        computelps(lps,b,m);
        int i=0, j=0;
        while(n-i >= m-j){
            if(a[i]==b[j]){
                i++, j++;
            }
            if(j==m){
                cnt++;
                j=lps[j-1];
            }else if(i<n && a[i] != b[j]){
                if(j)
                    j=lps[j-1];
                else
                    i++;
            }
        }
        return cnt;
    }
};

void solve(){
    
}

signed main(){
    clock_t tStart = clock();
    faster
    debugMode();
    int t=1;
    cin>>t;
    for(int cs=1;cs<=t;cs++){
        //cout<<"Case "<<cs<<":\n";
        solve();
    }
    runtime(tStart);
    return 0;
}