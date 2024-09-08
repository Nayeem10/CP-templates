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
void generate_hash(const string &s){
  LL n = s.size(), p = 31, m = 1e9 + 9;
  vector<LL> p_pow(n), h(n + 1, 0);
  p_pow[0] = 1;
  for(LL i = 1; i < n; i++) p_pow[i] = (p_pow[i - 1] * p) % m;
  // generate
  for(int i = 0; i < n; i++) h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
}
LL get_substring_hash(LL l, LL r) {
  LL cur_h = (h[r] + m - h[l - 1]) % m;
  cur_h = (cur_h * p_pow[n - l - 1]) % m;
  return cur_h;
}