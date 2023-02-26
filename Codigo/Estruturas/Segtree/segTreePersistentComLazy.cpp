// SegTree Persistente com Lazy
//
// Nao propaga, meio estranho de mexer, mas da
//
// query(a, b, t) retorna a query de [a, b] na versao t
// update(a, b, x, t) faz um update v[a..b]+=x a partir da
// versao de t, criando uma nova versao e retornando seu id
// Por default, faz o update a partir da ultima versao
//
// build - O(n)
// query - O(log(n))
// update - O(log(n))

const int MAX = 1e5+10, UPD = 1e5+10, LOG = 18;
const int MAXS = 2*MAX + 4*UPD*LOG;

namespace perseg {
	int seg[MAXS];
	int rt[UPD], L[MAXS], R[MAXS], cnt, t;
	int n, *v;

	int build(int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		return seg[p] = max(build(L[p], l, m), build(R[p], m+1, r));
	}
	void build(int n2, int *v2) {
		n = n2, v = v2;
		rt[0] = cnt++;
		build(0, 0, n-1);
	}
	int query(int a, int b, int p, int l, int r) {
		if (b < l or r < a) return -INF;
		if (a <= l and r <= b) return lazy[p] + seg[p];
		int m = (l+r)/2;
		int ret = lazy[p] + max(query(a, b, L[p], l, m), query(a, b, R[p], m+1, r));
		return ret;
	}
	int query(int a, int b, int tt) {
		return query(a, b, rt[tt], 0, n-1);
	}
	int update(int a, int b, int x, int lp, int p, int l, int r) {
		tie(seg[p], lazy[p], L[p], R[p]) = {seg[lp], lazy[lp], L[lp], R[lp]};
		if (b < l or r < a) return seg[p] + lazy[p];
		if (a <= l and r <= b) return seg[p] + (lazy[p] += x);

		int m = (l+r)/2;
		seg[p] = max(update(a, b, x, L[lp], L[p] = cnt++, l, m),
					 update(a, b, x, R[lp], R[p] = cnt++, m+1, r));
		lazy[p] = lazy[lp];
		return seg[p] + lazy[p];
	}
	int update(int a, int b, int x, int tt=t) {
		assert(tt <= t);
		update(a, b, x, rt[tt], rt[++t]=cnt++, 0, n-1);
		return t;
	}
};
