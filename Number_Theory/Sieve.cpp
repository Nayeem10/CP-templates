int divisor[N + 1];
void sieve(){                        
    for(int i = 1; i <= N; i++) divisor[i] = i;
    for(int i = 2; i <= N; i += 2) divisor[i] = 2;
    for(LL i = 3; i <= N; i += 2){
        if(divisor[i] == i){
            for(LL j = i * i; j <= N; j += i){   
                if(divisor[j] == j) divisor[j] = i;
            }
        }
    }
}
