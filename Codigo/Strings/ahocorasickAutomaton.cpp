// Aho-corasick - Automato
//
// query retorna o numero de matches sem overlap
//
// insert - O(|s|)
// build - O(n * SIGMA), onde n = somatorio dos tamanhos das strings
// 2d8557

namespace aho {
	const vector<pair<char, char>> vt = {
		{'a', 'z'},
		{'A', 'Z'},
		{'0', '9'}
	};//example of alphabet

	void fix(char &c){
		int acc = 0;
		for (auto p : vt){
			if (p.first <= c && c <= p.second){
				c = c - p.first + acc;
				return;
			}
			acc += p.second - p.first + 1;
		}
	}
	void unfix(char &c){
		int acc = 0;
		for (auto p : vt){
			int next_acc = acc + p.second - p.first;
			if (acc <= c && c <= next_acc){
				c = p.first + c - acc;
				return;
			}
			acc = next_acc + 1;
		}
	}
	void fix(string &s){ for (char &c : s) fix(c); }
	void unfix(string &s){ for (char &c : s) unfix(c); }


	const int SIGMA = 70;//fix(vt.back().second) + 1;
	const int MAXN = 1e5+10;

	int to[MAXN][SIGMA];
	int link[MAXN], end[MAXN];
	int idx;
	void init(){
#warning dont forget to init before inserting strings
		memset(to, 0, sizeof to);
		idx = 1;
	}
	void insert(string &s){
		fix(s);
		int v =  0;
		for (char c : s){
			int &w = to[v][c];
			if (!w) w = idx++;
			v = w;
		}
		end[v] = 1;
	}
	void build(){
#warning dont forget to build after inserting strings
		queue<int> q;
		q.push(0);
		while (!q.empty()){
			int cur = q.front(); q.pop();
			int l = link[cur];
			end[cur] |= end[l];
			for (int i = 0; i < SIGMA; i++){
				int &w = to[cur][i];
				if (w){	
					link[w] = ((cur != 0) ? to[l][i] : 0);
					q.push(w);
				}
				else w = to[l][i];
			}
		}
	}
	int query(string &s){
		fix(s);
		int v = 0;
		int counter = 0;
		for (char c : s){
			v = to[v][c];
			if (end[v]) {
				counter++;
				v = 0;
			}
		}
		return counter;
	}
}
