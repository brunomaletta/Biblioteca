// Merge Sort Rafael
//
// Melhor do Brasil, segundo o autor
//
// O(n log(n))

long long merge_sort(int l, int r, vector<int> &t){
	if (l >= r) return 0;
	int m = (l+r)/2;
	auto ans = merge_sort(l, m, t) + merge_sort(m+1, r, t);
	static vector<int> aux; if (aux.size() != t.size()) aux.resize(t.size());
	for (int i = l; i <= r; i++) aux[i] = t[i];

	int i_l = l, i_r = m+1, i = l;
	auto move_l = [&](){
		t[i++] = aux[i_l++];
	};
	auto move_r = [&](){
		t[i++] = aux[i_r++];
	};

	while (i <= r){
		if (i_l > m) move_r();
		else if (i_r > r) move_l();
		else{
			if (aux[i_l] <= aux[i_r]) move_l();
			else{
				move_r();
				ans += m - i_l + 1;
			}

		}
	}
	return ans;
}
