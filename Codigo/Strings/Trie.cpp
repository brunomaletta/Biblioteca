// Trie
//
// trie T() constrói uma trie para o alfabeto das letras minúsculas
// trie T(tamanho do alfabeto, menor caracter) também pode ser usado
// 
// T.insert(s) - O(|s|*sigma)
// T.erase(s) - O(|s|)
// T.find(s) retorna a posição, 0 se não achar - O(|s|)
// T.count_pref(s) número de strings que possuem s como prefixo - O(|s|)
//
// Não funciona para string vazia

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
		for(auto c : s) {
			int &nxt = to[x][c-norm];
			if(!nxt) {
				nxt = to.size();
				to.push_back(vector<int>(sigma));
				end.push_back(0), pref.push_back(0);
			}
			x = nxt, pref[x]++;
		}
		end[x]++;
	}
	void erase(string s) {
		int x = 0;
		for(char c : s) {
			int &nxt = to[x][c-norm];
			x = nxt, pref[x]--;
			if(!pref[x]) nxt = 0;
		}
		end[x]--;
	}
	int find(string s) {
		int x = 0;
		for(auto c : s) {
			x = to[x][c-norm];
			if(!x) return 0;
		}
		return x;
	}
	int count_pref(string s) {
		return pref[find(s)];
	}
};
