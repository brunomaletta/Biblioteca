---
weight: 10
title: "Aho-corasick"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 query retorna o somatorio do numero de matches de

 todas as stringuinhas na stringona



 insert - O(|s| log(SIGMA))

 build - O(N), onde N = somatorio dos tamanhos das strings

 query - O(|s|)



Link original: [ahocorasick.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Strings/ahocorasick.cpp)

## Código
```cpp
namespace aho {
	map<char, int> to[MAX];
	int link[MAX], idx, term[MAX], exit[MAX], sobe[MAX];

	void insert(string& s) {
		int at = 0;
		for (char c : s) {
			auto it = to[at].find(c);
			if (it == to[at].end()) at = to[at][c] = ++idx;
			else at = it->second;
		}
		term[at]++, sobe[at]++;
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
				if (exit[j]+1) sobe[j] += sobe[exit[j]];
				q.push(j);
			}
		}
	}
	int query(string& s) {
		int at = 0, ans = 0;
		for (char c : s){
			while (at != -1 and !to[at].count(c)) at = link[at];
			at = at == -1 ? 0 : to[at][c];
			ans += sobe[at];
		}
		return ans;
	}
}
```
