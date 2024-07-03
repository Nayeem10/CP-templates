Data Structures

1. Ordered Structures
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 

#define ordered_multiset tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

2. BIT

int a[N],bin[N];
 
void update(int idx, int val, int n){  // ading val to index idx
    while(idx<=n){                     //to replace a value add val-a[idx], a is the main array
        bin[idx]+=val;
        idx += idx&-idx;
    }
}
 
int helper(int idx){
    int sum = 0;
    while(idx>0){
        sum+=bin[idx];
        idx -= idx&-idx;
    }
    return sum;
}

int query(int l,int r){
    return helper(r)-helper(l-1);
}

