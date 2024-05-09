---
weight: 10
title: "RMQ <O(n), O(1)> - min queue"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 O(n) pra buildar, query O(1)

 Se tiver varios minimos, retorna

 o de menor indice



Link original: [rmq.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/rmq.cpp)

## Código
```cpp
template<typename T> struct rmq {
	vector<T> v;
	int n; static const int b = 30;
	vector<int> mask, t;

	int op(int x, int y) { return v[x] <= v[y] ? x : y; }
	int msb(int x) { return __builtin_clz(1)-__builtin_clz(x); }
	int small(int r, int sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
	rmq() {}
	rmq(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n) {
		for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
			at = (at<<1)&((1<<b)-1);
			while (at and op(i-msb(at&-at), i) == i) at ^= at&-at;
		}
		for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
		for (int j = 1; (1<<j) <= n/b; j++) for (int i = 0; i+(1<<j) <= n/b; i++)
			t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
	}
	int index_query(int l, int r) {
		if (r-l+1 <= b) return small(r, r-l+1);
		int x = l/b+1, y = r/b-1;
		if (x > y) return op(small(l+b-1), small(r));
		int j = msb(y-x+1);
		int ans = op(small(l+b-1), op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
		return op(ans, small(r));
	}
	T query(int l, int r) { return v[index_query(l, r)]; }
};
```
