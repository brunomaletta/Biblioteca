// MergeSort Tree - Bit
//
// MergeSort Tree usando Bit, apesar da complexidade teorica ser pior
// se sai bem melhor na pratica.
//
// query(l, r, k) retorna o numero de elementos menores que k 
// no intervalo [l, r]
//
// Usa O(n log(n)) de memoria
//
// Complexidades:
// construir - O(n log(n)) 
// query - O(log^2(n)) 
// 8d0749 


template<typename T> struct ms_bit {
    int n;
    vector<vector<T>> bit;
  
    ms_bit(vector<T>& v) : n(v.size()), bit(n+1) {
        for (int i = 0; i < n; i++)
            for (int j = i+1; j <= n; j += j&-j)
                bit[j].push_back(v[i]);
        for (int i = 1; i <= n; i++)
            sort(bit[i].begin(), bit[i].end());
    }

    int p_query(int i, T k) {
        int ret = 0;
        for (i++; i; i -= i&-i)
            ret += lower_bound(bit[i].begin(), bit[i].end(), k) - bit[i].begin();
        return ret;
    }
    int query(int l, int r, T k) {
        return p_query(r, k) - p_query(l-1, k);
    }
};
