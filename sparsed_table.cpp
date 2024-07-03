#include<bits/stdc++.h>
using namespace std;

#define ln '\n'

//#define log_2(n) (31 - __builtin_clz(n))
#define log_2(n) 63-__builtin_clzll(n)
 
const int N = (1 << 20) + 5 ; //1048576 + 5

int logs[N];

void computeLogs(){
    logs[1] = 0;
    for(int i = 2; i < (1 << 20); i++){
        logs[i] = logs[i / 2]+1;
    }
} 

PLL fun(const PLL a,const PLL b){
    return a.first>b.first?a:b; 
}
 
PLL sparseTable[N][(LL)log_2(N) + 5];
void build(LL n, vector<PLL> &v){
  for(LL i = 0; i < n; i++) sparseTable[i][0] = v[i];
  for(LL j = 1; (1 << j) <= n; j++) {
    for(LL i = 0; (i + (1 << j) - 1) < n; i++) 
      sparseTable[i][j] = fun(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
  }
}
PLL query(LL L, LL R){
  LL j = logs[R - L + 1];
  return fun(sparseTable[L][j], sparseTable[R - (1 << j) + 1][j]);
}

int main(){
    int n; cin>>n;
    cout<<lg(n)<<ln;
}