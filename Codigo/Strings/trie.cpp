// Trie
//
// trie T() constroi uma trie para o alfabeto das letras minusculas
// trie T(tamanho do alfabeto, menor caracter) tambem pode ser usado
// 
// T.insert(s) - O(|s|*sigma)
// T.erase(s) - O(|s|)
// T.find(s) retorna a posicao, -1 se nao achar - O(|s|)
// T.count_pref(s) numero de strings que possuem s como prefixo - O(|s|)

struct trie {
	vector<vector<int>> to;
	vector<int> end, pref;
	int sigma; char norm;
	trie(int sigma_=26, char norm_='a') : sigma(sigma_), norm(norm_) {
		to = {vector<int>(sigma)};
		end = {0}, pref = {0};
	}
	void insert(string s) {
		int x = 0;
		for (auto c : s) {
			int &nxt = to[x][c-norm];
			if (!nxt) {
				nxt = to.size();
				to.push_back(vector<int>(sigma));
				end.push_back(0), pref.push_back(0);
			}
			x = nxt, pref[x]++;
		}
		end[x]++, pref[0]++;
	}
	void erase(string s) {
		int x = 0;
		for (char c : s) {
			int &nxt = to[x][c-norm];
			x = nxt, pref[x]--;
			if (!pref[x]) nxt = 0;
		}
		end[x]--, pref[0]--;
	}
	int find(string s) {
		int x = 0;
		for (auto c : s) {
			x = to[x][c-norm];
			if (!x) return -1;
		}
		return x;
	}
	int count_pref(string s) {
		int id = find(s);
		return id >= 0 ? pref[id] : 0;
	}
};
