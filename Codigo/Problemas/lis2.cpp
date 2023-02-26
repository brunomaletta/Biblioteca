// LIS - tamanho
//
// Calcula o tamanho da LIS
//
// O(n log(n))

template<typename T> int lis(vector<T> &v){
	vector<T> ans;
	for (T t : v){
		// Para non-decreasing use upper_bound()
		auto it = lower_bound(ans.begin(), ans.end(), t);
		if (it == ans.end()) ans.push_back(t);
		else *it = t;
	}
	return ans.size();
}
