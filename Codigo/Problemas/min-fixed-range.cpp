// Min fixed range
//
// https://codeforces.com/contest/1195/problem/E
//
// O(n)
// ans[i] = min_{0 <= j < k} v[i+j]

vector<int> min_k(vector<int> &v, int k){
	int n = v.size();
	deque<int> d;
	auto put = [&](int i){
		while (!d.empty() && v[d.back()] > v[i])
			d.pop_back();
		d.push_back(i);
	};
	for (int i = 0; i < k-1; i++)
		put(i);
	vector<int> ans(n-k+1);
	for (int i = 0; i < n-k+1; i++){
		put(i+k-1);
		while (i > d.front()) d.pop_front();
		ans[i] = v[d.front()];
	}
	return ans;
}
