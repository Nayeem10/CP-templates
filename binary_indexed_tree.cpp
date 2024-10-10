class BIT{
    int *bin, N;
public:
    BIT(int N): N(N){
        bin = new int[N + 1];
        memset(bin, 0, sizeof(bin));
    }
    void update(int id, int val){
        for(; id <= N; id += id & -id)
            bin[id] += val;
    }
    int helper(int id){
        int sum = 0;
        for(; id > 0; id -= id & -id)
            sum += bin[id];
        return sum;
    }
    int query(int l, int r){
        return helper(r) - helper(l - 1);
    }
    ~BIT(){
        delete[] bin;
    }
};