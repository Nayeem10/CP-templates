vector<int> getSuffixArray(string s){
    s.push_back(*min_element(all(s)) - 1);
    vector<int> values(all(s));
    sort(all(s)); s.erase(unique(all(s)), s.end());
    for(auto &u: values) u = lower_bound(all(s), u) - s.begin();
    int n = values.size();
    vector<int> order(n); iota(all(order), 0);
    auto c_sort = [&](int k, int bckt){
        vector<int> norder(n), freq(bckt + 1);
        for(int i = 0; i < n; i++) norder[i] = order[i] >= k ? order[i] - k : order[i] + n - k;
        for(auto &u: norder) freq[values[u]]++;
        partial_sum(all(freq), freq.begin());
        for(int i = n - 1; i >= 0; i--) order[--freq[values[norder[i]]]] = norder[i];
    };
    c_sort(0, n - 1);
    for(int k = 1; k < n; k *= 2){
        c_sort(k, values[order[n - 1]]);
        vector<int> nvalues(n);        
        for(int u = 1; u < n; u++){
            int i = order[u - 1], j = order[u];
            nvalues[j] = nvalues[i];
            if(values[i] != values[j] or values[(i + k) % n] != values[(j + k) % n]) nvalues[j]++; 
        }
        values = nvalues;
    }
    order.erase(order.begin());
    return order;
}
vector<int> getLCParray(string &s, vector<int> &sa){
    int n = sa.size(); 
    vector<int> lcp(n), rank(n);
    for(int i = 0; i < n; i++) rank[sa[i]] = i;
    for(int i = 0, k = 0; i < n; lcp[rank[i]] = k, i++, k ? --k : 0){
        if(rank[i] == n - 1) { k = 0; continue; }
        int j = sa[rank[i] + 1];
        while(i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
    }
    return lcp;
}