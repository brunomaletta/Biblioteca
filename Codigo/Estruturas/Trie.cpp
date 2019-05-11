// Trie
//
// N deve ser maior ou igual ao numero de nos da trie
// fim indica se alguma palavra acaba nesse no
//
// Complexidade:
// Inserir e conferir string S -> O(|S|)

// usar static trie T
// T.insert(s) para inserir
// T.find(s) para ver se ta
// T.prefix(s) printa as strings
// que tem s como prefixo

struct trie{
	map<char, int> t[MAX+5];
	int p;
	trie(){
		p = 1;
	}
	void insert(string s){
		s += '$';
		int i = 0;
		for (char c : s){
			auto it = t[i].find(c);
			if (it == t[i].end())
				i = t[i][c] = p++;
			else
				i = it->second;
		}
	}
	bool find(string s){
		s += '$';
		int i = 0;
		for (char c : s){
			auto it = t[i].find(c);
			if (it == t[i].end()) return false;
			i = it->second;
		}
		return true;
	}
	void prefix(string &l, int i){
		if (t[i].find('$') != t[i].end())
			cout << "  " << l << endl;	
		for (auto p : t[i]){
			l += p.first;
			prefix(l, p.second, k);
			l.pop_back();
		}
	}
	void prefix(string s){
		int i = 0;
		for (char c : s){
			auto it = t[i].find(c);
			if (it == t[i].end()) return;
			i = it->second;
		}
		int k = 0;
		prefix(s, i, k);
	}
};
