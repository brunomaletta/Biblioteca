// Invertion Count
//
// O(n log(n))

int n;
int v[MAX];

// bit de soma
void build();
void poe(int p);
int query(int p);

// converte valores do array pra
// numeros de 1 a n
void conv() {
	vector<int> a;
	for (int i = 0; i < n; i++) a.push_back(v[i]);

	sort(a.begin(), a.end());

	for (int i = 0; i < n; i++)
		v[i] = 1 + (lower_bound(a.begin(), a.end(), v[i]) - a.begin());
}

long long inv() {
	conv();
	build();

	long long ret = 0;
	for (int i = n - 1; i >= 0; i--) {
		ret += query(v[i] - 1);
		poe(v[i]);
	}
	return ret;
}
