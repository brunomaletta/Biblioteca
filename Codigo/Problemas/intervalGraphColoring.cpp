// Coloracao de Grafo de Intervalo
//
// Colore os intervalos com o numero minimo
// de cores de tal forma que dois intervalos
// que se interceptam tem cores diferentes
// As cores vao de 1 ate n
//
// O(n log(n))

vector<int> coloring(vector<pair<int, int>>& v) {
	int n = v.size();
	vector<pair<int, pair<int, int>>> ev;
	for (int i = 0; i < n; i++) {
		ev.push_back({v[i].first, {1, i}});
		ev.push_back({v[i].second, {0, i}});
	}
	sort(ev.begin(), ev.end());
	vector<int> ans(n), avl(n);
	for (int i = 0; i < n; i++) avl.push_back(n-i);
	for (auto i : ev) {
		if (i.second.first == 1) {
			ans[i.second.second] = avl.back();
			avl.pop_back();
		} else avl.push_back(ans[i.second.second]);
	}
	return ans;
}
