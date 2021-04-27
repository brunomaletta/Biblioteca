// Aho-corasick 
//
// query retorna o numero de matches sem overlap
//
// insert - O(|s| * log(SIGMA))
// build - O(n * SIGMA), onde n = somatorio dos tamanhos das strings

namespace aho {
	map<char, int> to[MAX];
	int link[MAX], idx, term[MAX], exit[MAX];

	void insert(string& s) {
		int at = 0;
		for (char c : s) {
			auto it = to[at].find(c);
			if (it == to[at].end()) at = to[at][c] = ++idx;
			else at = it->second;
		}
		term[at] = 1;
	}
#warning nao esquece de chamar build() depois de inserir
	void build() {
		queue<int> q;
		q.push(0);
		link[0] = exit[0] = -1;
		while (q.size()) {
			int i = q.front(); q.pop();
			for (auto [c, j] : to[i]) {
				int l = link[i];
				while (l != -1 and !to[l].count(c)) l = link[l];
				link[j] = l == -1 ? 0 : to[l][c];
				exit[j] = term[link[j]] ? link[j] : exit[link[j]];
				q.push(j);
			}
		}
	}
	int query(string& s) {
		int at = 0, ans = 0;
		for (char c : s){
			while (at and !to[at].count(c)) at = link[at];
			at = to[at][c];
			if (term[at] or exit[at]+1) ans++, at = 0;
		}
		return ans;
	}
}
