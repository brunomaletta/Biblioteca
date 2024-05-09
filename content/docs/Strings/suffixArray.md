---
weight: 10
title: "Suffix Array - O(n)"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Rapidao

 Computa o suffix array em 'sa', o rank em 'rnk'

 e o lcp em 'lcp'

 query(i, j) retorna o LCP entre s[i..n-1] e s[j..n-1]



 Complexidades

 O(n) para construir

 query - O(1)



Link original: [suffixArray.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Strings/suffixArray.cpp)

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

struct suffix_array {
	string s;
	int n;
	vector<int> sa, cnt, rnk, lcp;
	rmq<int> RMQ;

	bool cmp(int a1, int b1, int a2, int b2, int a3=0, int b3=0) {
		return a1 != b1 ? a1 < b1 : (a2 != b2 ? a2 < b2 : a3 < b3);
	}
	template<typename T> void radix(int* fr, int* to, T* r, int N, int k) {
		cnt = vector<int>(k+1, 0);
		for (int i = 0; i < N; i++) cnt[r[fr[i]]]++;
		for (int i = 1; i <= k; i++) cnt[i] += cnt[i-1];
		for (int i = N-1; i+1; i--) to[--cnt[r[fr[i]]]] = fr[i];
	}
	void rec(vector<int>& v, int k) {
		auto &tmp = rnk, &m0 = lcp;
		int N = v.size()-3, sz = (N+2)/3, sz2 = sz+N/3;
		vector<int> R(sz2+3);
		for (int i = 1, j = 0; j < sz2; i += i%3) R[j++] = i;

		radix(&R[0], &tmp[0], &v[0]+2, sz2, k);
		radix(&tmp[0], &R[0], &v[0]+1, sz2, k);
		radix(&R[0], &tmp[0], &v[0]+0, sz2, k);

		int dif = 0;
		int l0 = -1, l1 = -1, l2 = -1;
		for (int i = 0; i < sz2; i++) {
			if (v[tmp[i]] != l0 or v[tmp[i]+1] != l1 or v[tmp[i]+2] != l2)
				l0 = v[tmp[i]], l1 = v[tmp[i]+1], l2 = v[tmp[i]+2], dif++;
			if (tmp[i]%3 == 1) R[tmp[i]/3] = dif;
			else R[tmp[i]/3+sz] = dif;
		}

		if (dif < sz2) {
			rec(R, dif);
			for (int i = 0; i < sz2; i++) R[sa[i]] = i+1;
		} else for (int i = 0; i < sz2; i++) sa[R[i]-1] = i;

		for (int i = 0, j = 0; j < sz2; i++) if (sa[i] < sz) tmp[j++] = 3*sa[i];
		radix(&tmp[0], &m0[0], &v[0], sz, k);
		for (int i = 0; i < sz2; i++)
			sa[i] = sa[i] < sz ? 3*sa[i]+1 : 3*(sa[i]-sz)+2;

		int at = sz2+sz-1, p = sz-1, p2 = sz2-1;
		while (p >= 0 and p2 >= 0) {
			if ((sa[p2]%3==1 and cmp(v[m0[p]], v[sa[p2]], R[m0[p]/3],
				R[sa[p2]/3+sz])) or (sa[p2]%3==2 and cmp(v[m0[p]], v[sa[p2]],
				v[m0[p]+1], v[sa[p2]+1], R[m0[p]/3+sz], R[sa[p2]/3+1])))
				sa[at--] = sa[p2--];
			else sa[at--] = m0[p--];
		}
		while (p >= 0) sa[at--] = m0[p--];
		if (N%3==1) for (int i = 0; i < N; i++) sa[i] = sa[i+1];
	}

	suffix_array(const string& s_) : s(s_), n(s.size()), sa(n+3),
			cnt(n+1), rnk(n), lcp(n-1) {
		vector<int> v(n+3);
		for (int i = 0; i < n; i++) v[i] = i;
		radix(&v[0], &rnk[0], &s[0], n, 256);
		int dif = 1;
		for (int i = 0; i < n; i++)
			v[rnk[i]] = dif += (i and s[rnk[i]] != s[rnk[i-1]]);
		if (n >= 2) rec(v, dif);
		sa.resize(n);

		for (int i = 0; i < n; i++) rnk[sa[i]] = i;
		for (int i = 0, k = 0; i < n; i++, k -= !!k) {
			if (rnk[i] == n-1) {
				k = 0;
				continue;
			}
			int j = sa[rnk[i]+1];
			while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
			lcp[rnk[i]] = k;
		}
		RMQ = rmq<int>(lcp);
	}

	int query(int i, int j) {
		if (i == j) return n-i;
		i = rnk[i], j = rnk[j];
		return RMQ.query(min(i, j), max(i, j)-1);
	}
	pair<int, int> next(int L, int R, int i, char c) {
		int l = L, r = R+1;
		while (l < r) {
			int m = (l+r)/2;
			if (i+sa[m] >= n or s[i+sa[m]] < c) l = m+1;
			else r = m;
		}
		if (l == R+1 or s[i+sa[l]] > c) return {-1, -1};
		L = l;

		l = L, r = R+1;
		while (l < r) {
			int m = (l+r)/2;
			if (i+sa[m] >= n or s[i+sa[m]] <= c) l = m+1;
			else r = m;
		}
		R = l-1;
		return {L, R};
	}
	// quantas vezes 't' ocorre em 's' - O(|t| log n)
	int count_substr(string& t) {
		int L = 0, R = n-1;
		for (int i = 0; i < t.size(); i++) {
			tie(L, R) = next(L, R, i, t[i]);
			if (L == -1) return 0;
		}
		return R-L+1;
	}

	// exemplo de f que resolve o problema
	// https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/D
	ll f(ll k) { return k*(k+1)/2; }

	ll dfs(int L, int R, int p) { // dfs na suffix tree chamado em pre ordem
		int ext = L != R ? RMQ.query(L, R-1) : n - sa[L];

		// Tem 'ext - p' substrings diferentes que ocorrem 'R-L+1' vezes
		// O LCP de todas elas eh 'ext'
		ll ans = (ext-p)*f(R-L+1);

		// L eh terminal, e folha sse L == R
		if (sa[L]+ext == n) L++;

		// se for um SA de varias strings separadas como s#t$u&, usar no lugar do if de cima
		//	(separadores < 'a', diferentes e inclusive no final)
		// while (L <= R && (sa[L]+ext == n || s[sa[L]+ext] < 'a')) {
		//   L++;
		// }

		while (L <= R) {
			int idx = L != R ? RMQ.index_query(L, R-1) : -1;
			if (idx == -1 or lcp[idx] != ext) idx = R;

			ans += dfs(L, idx, ext);
			L = idx+1;
		}
		return ans;
	}

	// sum over substrings: computa, para toda substring t distinta de s,
	// \sum f(# ocorrencias de t em s) - O (n)
	ll sos() { return dfs(0, n-1, 0); }
};
```
