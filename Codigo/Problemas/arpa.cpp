// Arpa's Trick
//
// Responde RMQ em O((n+q)log(n)) offline
// Adicionar as queries usando arpa::add(a, b)
// A resposta vai ta em ans[], na ordem que foram colocadas
// 11a509

int n, v[MAX], ans[MAX];

namespace arpa {
	int p[MAX], cnt;
	stack<int> s;
	vector<pair<int, int>> l[MAX];

	int find(int k) { return p[k] == k ? k : p[k] = find(p[k]); }
	void add(int a, int b) { l[b].push_back({a, cnt++}); }
	void solve() {
		for (int i = 0; (p[i]=i) < n; s.push(i++)) {
			while (s.size() and v[s.top()] >= v[i]) p[s.top()] = i, s.pop();
			for (auto q : l[i]) ans[q.second] = v[find(q.first)];
		}
	}
}
