// Mo algorithm - DQUERY path on trees
//
// https://codeforces.com/blog/entry/43230
// https://www.spoj.com/problems/COT2/
//
// (s*2*n*f + q*(2*n/s)*f) optimize over s, insert/erase = O(f)
// for s = sqrt(n), O((n+q)*sqrt(n)*f)

vector<int> g[MAX];
namespace LCA { ... }

const int MAX = 40010;
const int SQ = 316;

int w[MAX];
int st[MAX], en[MAX], hst[2*MAX];

int v[2*MAX];

int ans, freq[MAX], freqv[MAX];

void dfs(int i, int p, int &t){
	v[t] = i;
	st[i] = t++;
	for (int j : g[i]){
		if (j == p) continue;
		dfs(j, i, t);
	}

	v[t] = i;
	en[i] = t++;
}

void update(int o){//only change this function
	if (freqv[o] == 1){//insert w[o]
		ans += (freq[w[o]] == 0);
		freq[w[o]]++;
	}
	if (freqv[o] != 1){//erase w[o]
		ans -= (freq[w[o]] == 1);
		freq[w[o]]--;
	}
}

void insert(int p){
	int o = v[p];
	freqv[o]++;
	update(o);
}

void erase(int p){
	int o = v[p];
	freqv[o]--;
	update(o);
}

vector<tuple<int, int, int>> make_queries(vector<pair<int, int>> &q_){
	vector<tuple<int, int, int>> q;
	for (auto &it : q_){
		int l, r;
		tie(l, r) = it;
		if (st[r] < st[l]) swap(l, r);
		int p = LCA::lca(l, r);
		int init = (p == l) ? st[l] : en[l];
		q.push_back({init, st[r], st[p]});
	}
	return q;
}

vector<int> MO(vector<pair<int, int>> &q_){
	LCA::build(0);//any LCA alg works
	int t = 0;
	dfs(0, -1, t);
	auto q = make_queries(q_);
	ans = 0;
	memset(freq, 0, sizeof freq);
	memset(freqv, 0, sizeof freqv);
	
	int m = q.size();
	vector<int> ord(m), ret(m);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](int l, int r){
		int sl = get<0>(q[l])/SQ;
		int sr = get<0>(q[r])/SQ;
		if (sl != sr) return sl < sr;
		return get<1>(q[l]) < get<1>(q[r]);
	});

	int l = 0, r = 0;
	insert(0);

	for (int i : ord){
		int ql, qr, qp;
		tie(ql, qr, qp) = q[i];
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);

		if (qp < l || qp > r){
			//lca out of range
			insert(qp);
			ret[i] = ans;
			erase(qp);
		}
		else ret[i] = ans;
	}
	return ret;
}
