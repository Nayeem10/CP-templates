#include<bits/stdc++.h>
using namespace std;

template<typename T>
class KMP {
public:
    vector<int> getLPSarray(T &b){
        int m = b.size(), len = 0;
        vector<int> lps(m);
        for(int i = 1; i < m; i++){
            while(len && b[i] != b[len]) len = lps[len - 1];
            if(b[i] == b[len]) len++;
            lps[i]=len;
        }
        return lps;
    }

    int match(T &a, T &b){
        int n = a.size(), m = b.size();
        vector<int> lps = getLPSarray(b);
        int i = 0, j = 0, cnt = 0;
        while(n - i >= m - j){
            if(a[i] == b[j]){
                i++, j++;
            }
            if(j == m){
                cnt++, j = lps[j-1];
            }else if(i < n && a[i] != b[j]){
                if(j) j = lps[j-1];
                else i++;
            }
        }
        return cnt;
    }
};
