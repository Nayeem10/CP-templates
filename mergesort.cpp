#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;

#define loop(n) for(int i=0; i<n; i++)
#define pool(n) for(int i=n-1; i>=0; i--)
#define yes cout << "YES" << endl ;
#define no  cout << "NO" << endl ;
#define ln '\n'
#define faster {ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);}
#define ordered_set tree<int, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update> 

const ll mod=998244353;
const int N=2e5+100;

inline void debugMode() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // ONLINE_JUDGE
}

void merge(int l,int r,int arr[]){
    int mid=(l+r)/2;
    int n1=mid-l+1, n2=r-mid;
    int L[n1],R[n2];

    for(int i=0;i<n1;i++) L[i]=arr[i+l];
    for(int i=0;i<n2;i++) R[i]=arr[i+mid+1];
    
    int i=l,j=0,k=0;
    while(j<n1 && k<n2){
        if(L[j]<=R[k]){
            arr[i]=L[j];  
            j++;
        }else{
            arr[i]=R[k];
            k++;
        }
        i++;
    } 
    while(j<n1){
        arr[i]=L[j];
        j++; i++;
    }
    while(k<n2){
        arr[i]=R[k];
        k++; i++;
    }
}

void mergecall(int l,int r,int arr[]){
    if(l==r)return;
    int mid=(l+r)/2;
    mergecall(l,mid,arr);
    mergecall(mid+1,r,arr);
    merge(l,r,arr);
}

void solve(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    mergecall(0,n-1,arr);
    for(int i=0;i<n;i++)cout<<arr[i]<<" ";    
}
    
int main(){
    faster
    debugMode();
    int t=1;
    cin>>t;
    for(int cs=1;cs<=t;cs++){
        //cout<<"Case "<<cs<<": ";
        solve();
    }
    return 0;
}