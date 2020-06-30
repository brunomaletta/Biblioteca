// Suffix Array - O(n)
//
// Rapidao
// Computa o suffix array em 'sa', o rank em 'rnk'
// e o lcp em 'lcp'
// query(i, j) retorna o LCP entre s[i..n-1] e s[j..n-1]
//
// Complexidades (assumindo rmq <O(n), O(1)>):
// O(n) para construir
// query - O(1)

struct SA {
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

	SA(string& s) : n(s.size()), sa(n+3), cnt(n+1), rnk(n), lcp(n-1) {
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
	// quantas vezes 't' ocorre em 's' - O(|t| log n)
	int count_substr(string& t) {
		if (t.size() > n) return 0;
		int L = 0, R = n-1;
		for (int i = 0; i < t.size(); i++) {
			int l = L, r = R+1;
			while (l < r) {
				int m = (l+r)/2;
				if (i+sa[m] >= n or s[i+sa[m]] < t[i]) l = m+1;
				else r = m;
			}
			if (l == R+1 or s[i+sa[l]] > t[i]) return 0;
			L = l;

			l = L, r = R+1;
			while (l < r) {
				int m = (l+r)/2;
				if (i+sa[m] >= n or s[i+sa[m]] <= t[i]) l = m+1;
				else r = m;
			}
			R = l-1;
		}
		return R-L+1;
	}
};
