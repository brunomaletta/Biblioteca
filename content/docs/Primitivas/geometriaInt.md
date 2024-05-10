---
weight: 10
title: "Geometria - inteiro"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
Link original: [geometriaInt.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Primitivas/geometriaInt.cpp)

## Código
```cpp
#define sq(x) ((x)*(ll)(x))

struct pt { // ponto
	int x, y;
	pt(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator == (const pt p) const {
		return x == p.x and y == p.y;
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const int c) const { return pt(x*c, y*c); }
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

struct line { // reta
	pt p, q;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
	friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};

// PONTO & VETOR

ll dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}

ll sarea2(pt p, pt q, pt r) { // 2 * area com sinal
	return (q-p)^(r-q);
}

bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return sarea2(p, q, r) == 0;
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea2(p, q, r) > 0;
}

int quad(pt p) { // quadrante de um ponto
	return (p.x<0)^3*(p.y<0);
}

bool compare_angle(pt p, pt q) { // retorna se ang(p) < ang(q)
	if (quad(p) != quad(q)) return quad(p) < quad(q);
	return ccw(q, pt(0, 0), p);
}

pt rotate90(pt p) { // rotaciona 90 graus
	return pt(-p.y, p.x);
}

// RETA

bool isinseg(pt p, line r) { // se p pertence ao seg de r
	pt a = r.p - p, b = r.q - p;
	return (a ^ b) == 0 and (a * b) <= 0;
}

bool interseg(line r, line s) { // se o seg de r intersecta o seg de s
	if (isinseg(r.p, s) or isinseg(r.q, s)
		or isinseg(s.p, r) or isinseg(s.q, r)) return 1;

	return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and
			ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

int segpoints(line r) { // numero de pontos inteiros no segmento
	return 1 + __gcd(abs(r.p.x - r.q.x), abs(r.p.y - r.q.y));
}

double get_t(pt v, line r) { // retorna t tal que t*v pertence a reta r
	return (r.p^r.q) / (double) ((r.p-r.q)^v);
}

// POLIGONO

// quadrado da distancia entre os retangulos a e b (lados paralelos aos eixos)
// assume que ta representado (inferior esquerdo, superior direito)
ll dist2_rect(pair<pt, pt> a, pair<pt, pt> b) {
	int hor = 0, vert = 0;
	if (a.second.x < b.first.x) hor = b.first.x - a.second.x;
	else if (b.second.x < a.first.x) hor = a.first.x - b.second.x;
	if (a.second.y < b.first.y) vert = b.first.y - a.second.y;
	else if (b.second.y < a.first.y) vert = a.first.y - b.second.y;
	return sq(hor) + sq(vert);
}

ll polarea2(vector<pt> v) { // 2 * area do poligono
	ll ret = 0;
	for (int i = 0; i < v.size(); i++)
		ret += sarea2(pt(0, 0), v[i], v[(i + 1) % v.size()]);
	return abs(ret);
}

// se o ponto ta dentro do poligono: retorna 0 se ta fora,
// 1 se ta no interior e 2 se ta na borda
int inpol(vector<pt>& v, pt p) { // O(n)
	int qt = 0;
	for (int i = 0; i < v.size(); i++) {
		if (p == v[i]) return 2;
		int j = (i+1)%v.size();
		if (p.y == v[i].y and p.y == v[j].y) {
			if ((v[i]-p)*(v[j]-p) <= 0) return 2;
			continue;
		}
		bool baixo = v[i].y < p.y;
		if (baixo == (v[j].y < p.y)) continue;
		auto t = (p-v[i])^(v[j]-v[i]);
		if (!t) return 2;
		if (baixo == (t > 0)) qt += baixo ? 1 : -1;
	}
	return qt != 0;
}

vector<pt> convex_hull(vector<pt> v) { // convex hull - O(n log(n))
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	if (v.size() <= 1) return v;
	vector<pt> l, u;
	for (int i = 0; i < v.size(); i++) {
		while (l.size() > 1 and !ccw(l.end()[-2], l.end()[-1], v[i]))
			l.pop_back();
		l.push_back(v[i]);
	}
	for (int i = v.size() - 1; i >= 0; i--) {
		while (u.size() > 1 and !ccw(u.end()[-2], u.end()[-1], v[i]))
			u.pop_back();
		u.push_back(v[i]);
	}
	l.pop_back(); u.pop_back();
	for (pt i : u) l.push_back(i);
	return l;
}

ll interior_points(vector<pt> v) { // pontos inteiros dentro de um poligono simples
	ll b = 0;
	for (int i = 0; i < v.size(); i++)
		b += segpoints(line(v[i], v[(i+1)%v.size()])) - 1;
	return (polarea2(v) - b) / 2 + 1;
}

struct convex_pol {
	vector<pt> pol;

	// nao pode ter ponto colinear no convex hull
	convex_pol() {}
	convex_pol(vector<pt> v) : pol(convex_hull(v)) {}

	// se o ponto ta dentro do hull - O(log(n))
	bool is_inside(pt p) {
		if (pol.size() == 0) return false;
		if (pol.size() == 1) return p == pol[0];
		int l = 1, r = pol.size();
		while (l < r) {
			int m = (l+r)/2;
			if (ccw(p, pol[0], pol[m])) l = m+1;
			else r = m;
		}
		if (l == 1) return isinseg(p, line(pol[0], pol[1]));
		if (l == pol.size()) return false;
		return !ccw(p, pol[l], pol[l-1]);
	}
	// ponto extremo em relacao a cmp(p, q) = p mais extremo q
	// (copiado de https://github.com/gustavoM32/caderno-zika)
	int extreme(const function<bool(pt, pt)>& cmp) {
		int n = pol.size();
		auto extr = [&](int i, bool& cur_dir) {
			cur_dir = cmp(pol[(i+1)%n], pol[i]);
			return !cur_dir and !cmp(pol[(i+n-1)%n], pol[i]);
		};
		bool last_dir, cur_dir;
		if (extr(0, last_dir)) return 0;
		int l = 0, r = n;
		while (l+1 < r) {
			int m = (l+r)/2;
			if (extr(m, cur_dir)) return m;
			bool rel_dir = cmp(pol[m], pol[l]);
			if ((!last_dir and cur_dir) or
					(last_dir == cur_dir and rel_dir == cur_dir)) {
				l = m;
				last_dir = cur_dir;
			} else r = m;
		}
		return l;
	}
	int max_dot(pt v) {
		return extreme([&](pt p, pt q) { return p*v > q*v; });
	}
	pair<int, int> tangents(pt p) {
		auto L = [&](pt q, pt r) { return ccw(p, r, q); };
		auto R = [&](pt q, pt r) { return ccw(p, q, r); };
		return {extreme(L), extreme(R)};
	}
};

bool operator <(const line& a, const line& b) { // comparador pra reta
	// assume que as retas tem p < q
	pt v1 = a.q - a.p, v2 = b.q - b.p;
	bool b1 = compare_angle(v1, v2), b2 = compare_angle(v2, v1);
	if (b1 or b2) return b1;
	return ccw(a.p, a.q, b.p); // mesmo angulo
}
bool operator ==(const line& a, const line& b) {
	return !(a < b) and !(b < a);
}

// comparador pro set pra fazer sweep line com segmentos
struct cmp_sweepline {
	bool operator () (const line& a, const line& b) const {
		// assume que os segmentos tem p < q
		if (a.p == b.p) return ccw(a.p, a.q, b.q);
		if (a.p.x != a.q.x and (b.p.x == b.q.x or a.p.x < b.p.x))
			return ccw(a.p, a.q, b.p);
		return ccw(a.p, b.q, b.p);
	}
};

// comparador pro set pra fazer sweep angle com segmentos
pt dir;
struct cmp_sweepangle {
    bool operator () (const line& a, const line& b) const {
        return get_t(dir, a) < get_t(dir, b);
    }
};
```
