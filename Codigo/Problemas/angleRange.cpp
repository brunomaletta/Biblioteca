// Angle Range Intersection
//
// Computa intersecao de angulos
// Os angulos (arcos) precisam ter comprimeiro < pi
// (caso contrario a intersecao eh estranha)
//
// Tudo O(1)

struct angle_range {
	static constexpr ld ALL = 1e9, NIL = -1e9;
	ld l, r;
	angle_range() : l(ALL), r(ALL) {}
	angle_range(ld l_, ld r_) : l(l_), r(r_) { fix(l), fix(r); }

	void fix(ld& theta) {
		if (theta == ALL or theta == NIL) return;
		if (theta > 2*pi) theta -= 2*pi;
		if (theta < 0) theta += 2*pi;
	}
	bool empty() { return l == NIL; }
	bool contains(ld q) {
		fix(q);
		if (l == ALL) return true;
		if (l == NIL) return false;
		if (l < r) return l < q and q < r;
		return q > l or q < r;
	}
	friend angle_range operator &(angle_range p, angle_range q) {
		if (p.l == ALL or q.l == NIL) return q;
		if (q.l == ALL or p.l == NIL) return p;
		if (p.l > p.r and q.l > q.r) return {max(p.l, q.l) , min(p.r, q.r)};
		if (q.l > q.r) swap(p.l, q.l), swap(p.r, q.r);
		if (p.l > p.r) {
			if (q.r > p.l) return {max(q.l, p.l) , q.r};
			else if (q.l < p.r) return {q.l, min(q.r, p.r)};
			return {NIL, NIL};
		}
		if (max(p.l, q.l) > min(p.r, q.r)) return {NIL, NIL};
		return {max(p.l, q.l), min(p.r, q.r)};
	}
};
