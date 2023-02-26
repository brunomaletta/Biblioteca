// Area Maxima de Histograma
//
// Assume que todas as barras tem largura 1,
// e altura dada no vetor v
//
// O(n)

ll area(vector<int> v) {
	ll ret = 0;
	stack<int> s;
	// valores iniciais pra dar tudo certo
	v.insert(v.begin(), -1);
	v.insert(v.end(), -1);
	s.push(0);

	for(int i = 0; i < (int) v.size(); i++) {
		while (v[s.top()] > v[i]) {
			ll h = v[s.top()]; s.pop();
			ret = max(ret, h * (i - s.top() - 1));
		}
		s.push(i);
	}
  
	return ret;
}
