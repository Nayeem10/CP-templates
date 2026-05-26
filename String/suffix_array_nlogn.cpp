vector<int> getSuffixArray(string s){
    s.push_back(*min_element(all(s)) - 1);
    vector<int> vals(all(s));
    sort(all(s)); s.erase(unique(all(s)), s.end());
    for(auto &u: vals) u = lower_bound(all(s), u) - s.begin();
    int n = vals.size();
    vector<int> order(n); iota(all(order), 0);
    auto c_sort = [&](int k, int bckt){
        vector<int> norder(n), freq(bckt + 1);
        for(int i = 0; i < n; i++) norder[i] = order[i] >= k ? order[i] - k : order[i] + n - k;
        for(auto &u: norder) freq[vals[u]]++;
        for(int i = 1; i <= bckt; i++) freq[i] += freq[i - 1];
        for(int i = n - 1; i >= 0; i--) order[--freq[vals[norder[i]]]] = norder[i];
    };
    c_sort(0, n - 1);
    for(int k = 1; k < n; k *= 2, vals = nvals){
        c_sort(k, vals[order[n - 1]]);
        vector<int> nvals(n);        
        for(int u = 1; u < n; u++){
            int i = order[u - 1], j = order[u];
            nvals[j] = nvals[i];
            if(vals[i] != vals[j] or vals[(i + k) % n] != vals[(j + k) % n]) nvals[j]++; 
        }
        vals = nvals;
    }
    order.erase(order.begin());
    return order;
}