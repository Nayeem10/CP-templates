1. KMP
template<typename T>
class calckmp {
  void computelps(vector<int> &lps,T &b,int m){
    int len=0,i=1;
    lps[0]=0;                   
    while(i<m){
      if(b[i]==b[len]){
          len++; lps[i]=len; i++;
      }else{
        if(len) len = lps[len-1];
        else lps[i]=0, i++;     
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
      if(a[i]==b[j]) i++, j++;
      if(j==m){
        cnt++;
        j=lps[j-1];
      }else if(i<n && a[i] != b[j]){
        if(j) j=lps[j-1];
        else i++;
      }
    }
    return cnt;
  }
};
2. Trie
struct node {
    bool endmark;
    node* next[26 + 1];
    node()
    {
        endmark = false;
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
    }
} * root;
void insert(char* str, int len){
    node* curr = root;
    for (int i = 0; i < len; i++) {
        int id = str[i] - 'a';
        if (curr->next[id] == NULL)
            curr->next[id] = new node();
        curr = curr->next[id];
    }
    curr->endmark = true;
}
bool search(char* str, int len){
  node* curr = root;
  for (int i = 0; i < len; i++) {
    int id = str[i] - 'a';
    if (curr->next[id] == NULL) return false;
    curr = curr->next[id];
  }
  return curr->endmark;
}
void del(node* cur){
  for (int i = 0; i < 26; i++)
    if (cur->next[i]) del(cur->next[i]);
  delete (cur);
}
3. Manacher
vector<int> manacher(string str){
  int i, j, k, l=str.size(), n=l<<1;
  vector<int> pal(n);
  for(i=0,j=0,k=0; i<n; j=max(0,j-k),i+=k){
    while(j<=i && (i+j+1)<n && str[(i-j)>>1] == str(i+j+1)>>1]) j++;
    for(k=1, pal[i]=j; k<=i && k<=pal[i] && (pal[i]-k) != pal[i-k]; k++){
      pal[i+k] = min(pal[i-k],pal[i]-k);
    }
  }
  pal.pop_back();
  return pal;
}
4. Hashing

struct custom_double_hash {
    static uint32_t splitmix32(uint32_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static uint32_t splitmix32_second(uint32_t x) {
        x += 0x85ebca6b;
        x = (x ^ (x >> 13)) * 0xc2b2ae35;
        x = (x ^ (x >> 16)) * 0x27d4eb2f165667c5;
        return x ^ (x >> 15);
    }

    size_t operator()(uint32_t x) const {
        static const uint32_t FIXED_RANDOM_1 = chrono::steady_clock::now().time_since_epoch().count();
        static const uint32_t FIXED_RANDOM_2 = chrono::steady_clock::now().time_since_epoch().count() + 0x517cc1b727220a95;
        
        uint32_t hash1 = splitmix32(x + FIXED_RANDOM_1);
        uint32_t hash2 = splitmix32_second(x + FIXED_RANDOM_2);
        
        return hash1 ^ hash2;
    }
} rng;