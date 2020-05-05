// Mo algorithm - distinct values
// 
// O(s*n*f + q*(n/s)*f) optimize over s, insert/erase = O(f)
// for s = sqrt(n), O((n+q)*sqrt(n)*f)

const int MAX = 3e4+10;
const int SQ = sqrt(MAX);
int v[MAX];

int ans, freq[MAX];

void insert(int p){
	int o = v[p];
	freq[o]++;
	ans += (freq[o] == 1);
}
void erase(int p){
	int o = v[p];
	ans -= (freq[o] == 1);
	freq[o]--;
}

vector<int> MO(vector<ii> &q){
	ans = 0;
	memset(freq, 0, sizeof freq);
	int m = q.size();
	vector<int> ord(m), ret(m);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](int l, int r){
		int sl = q[l].first/SQ;
		int sr = q[r].first/SQ;
		if (sl != sr) return sl < sr;
		bool b = q[l].second < q[r].second;
		if (sl&1) b = !b;
		return b;
	});
	int l = 0, r = 0;
	insert(0);
	
	for (int i : ord){
		int ql, qr;
		tie(ql, qr) = q[i];
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);
		ret[i] = ans;
	}
	return ret;
}
