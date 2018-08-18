// Invertion Count
//
// O(n log(n))

int n;
int v[MAX];
int bit[MAX];

void build() {
	for (int i = 0; i <= n; i++) bit[i] = 0;
}

void poe(int p) {
	while (p <= n) {
		bit[p]++;
		p += p & -p;
	}
}

int query(int p) {
	int ret = 0;
	while (p) {
		ret += bit[p];
		p -= p & -p;
	}
	return ret;
}

// converte valores do array pra
// numeros de 1 a n
void conv() {
	vector<int> a;
	for (int i = 0; i < n; i++)
		a.push_back(v[i]);

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
