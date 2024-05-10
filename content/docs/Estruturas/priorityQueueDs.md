---
weight: 10
title: "Priority Queue DS"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Mantem updates aplicados em uma estrutura de dados

 que permita rollback e nao seja amortizada.

 Cada update possui uma prioridade,

 sendo possivel remover o update com maior prioridade.

 Os updates devem ser comutativos, ou seja, o estado 

 da estrutura deve ser o mesmo independente da ordem 

 que eles sejam aplicados.

 

 Complexidades:

 update - O(log(n) + T(n))

 query - T(n)

 pop - O(log(n) * T(n)) amortizado



 onde T(n) eh a complexidade do update



 assumes all priorities are distinct

Link original: [priorityQueueDs.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/priorityQueueDs.cpp)

## Código
```cpp
template<typename DS, typename UPD> struct priority_queue_ds {
	DS D;
	vector<tuple<UPD, int, int>> upd; // {u, p, idx_in_pos}
	set<pair<int, int>> st;
	vector<int> pos;

	priority_queue_ds(int n) : D(n) {}

	void update(UPD u, int p) {
		D.update(u);
		st.emplace(p, pos.size());
		upd.emplace_back(u, p, pos.size());
		pos.push_back(upd.size() - 1);
	}

	int query(int a) { 
		return D.find(a);
	}

	void pop() {
		int k = 1, min_p; // k = number of pops we will do
		vector<tuple<UPD, int, int>> small, big;
		auto it = st.end();
		for (int qt = 0; qt++ < (k+1)/2;) {
			it--;
			min_p = it->first;
			int i = pos[it->second];
			if (qt > 1) big.push_back(upd[i]);
			k = max<int>(k, upd.size() - i);
		}

		for (int i = 0; i < k; i++) {
			D.rollback();
			auto [u, p, idx] = upd.rbegin()[i];
			if (p < min_p) small.emplace_back(u, p, idx);
		}

		st.erase(prev(st.end()));
		upd.erase(upd.end() - k, upd.end());

		small.insert(small.end(), big.rbegin(), big.rend());
		for (auto [u, p, idx] : small) {
			D.update(u);
			upd.emplace_back(u, p, idx);
			pos[idx] = upd.size() - 1;
		}
	}
};
```
