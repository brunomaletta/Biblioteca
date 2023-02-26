// Convolucao de GCD / LCM
//
// O(n log(n))

// multiple_transform(a)[i] = \sum_d a[d * i]
template<typename T> void multiple_transform(vector<T>& v, bool inv = false) {
	vector<int> I(v.size()-1);
	iota(I.begin(), I.end(), 1);
	if (inv) reverse(I.begin(), I.end());
	for (int i : I) for (int j = 2; i*j < v.size(); j++)
		v[i] += (inv ? -1 : 1) * v[i*j];
}

// gcd_convolution(a, b)[k] = \sum_{gcd(i, j) = k} a_i * b_j
template<typename T> vector<T> gcd_convolution(vector<T> a, vector<T> b) {
	multiple_transform(a), multiple_transform(b);
	for (int i = 0; i < a.size(); i++) a[i] *= b[i];
	multiple_transform(a, true);
	return a;
}

// divisor_transform(a)[i] = \sum_{d|i} a[i/d]
template<typename T> void divisor_transform(vector<T>& v, bool inv = false) {
	vector<int> I(v.size()-1);
	iota(I.begin(), I.end(), 1);
	if (!inv) reverse(I.begin(), I.end());
	for (int i : I) for (int j = 2; i*j < v.size(); j++)
		v[i*j] += (inv ? -1 : 1) * v[i];
}

// lcm_convolution(a, b)[k] = \sum_{lcm(i, j) = k} a_i * b_j
template<typename T> vector<T> lcm_convolution(vector<T> a, vector<T> b) {
	divisor_transform(a), divisor_transform(b);
	for (int i = 0; i < a.size(); i++) a[i] *= b[i];
	divisor_transform(a, true);
	return a;
}
