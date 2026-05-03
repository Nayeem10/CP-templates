1. Monotonic Stack
void monotonic_stack(){
    int l[n], r[n];
    stack<int> ms;
    for(int i = 0; i < n; i++){
        l[i] = 1;
        while(!ms.empty() && a[ms.top()] <= a[i]){
            l[i] += l[ms.top()];
            ms.pop();
        }
        ms.push(i);
    }
    while(!ms.empty()) ms.pop();
    for(int i = n-1; i >= 0; i--){
        r[i] = 1;
        while(!ms.empty() && a[ms.top()] < a[i]){
            r[i] += r[ms.top()];
            ms.pop();
        }
        ms.push(i);
    }
}