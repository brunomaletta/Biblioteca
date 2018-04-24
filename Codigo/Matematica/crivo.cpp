vector<int> crivo(int n){
    //retorna todos os primos ate n
    vector<int> h(n+1, 1);
    for(int i = 2; i <= sqrt(n); i++)
        for(int j = i*i; h[i] && j <= n; j+=i)
            h[j] = 0;
            
    vector<int> v;
    for(int i = 2; i <= n; i++)
        if(h[i])
            v.push_back(i);
    return v;
}