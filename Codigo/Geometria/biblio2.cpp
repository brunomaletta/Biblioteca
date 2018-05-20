#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)((x).size())
#define sq(x) ((x)*(x))

typedef long double ld;

const ld DINF = 1.0/0.0;
const ld pi = acos(-1.0);
const ld eps = 1e-8;

ld absf(ld x) {
	return x >= 0 ? x : -x;
}

bool eq(ld a, ld b) {
	if (a == DINF and b == DINF) return 1;
	if (a == DINF or b == DINF) return 0;
	return absf(a - b) <= eps;
}

typedef struct { // ponto
	ld x, y;
} pt;

typedef struct { // vetor
	ld x, y;
} vec;

typedef struct { // reta
	pt p, q;
} line;

// PONTO

pt npt(ld x, ld y) { // novo ponto
	pt p;
	p.x = x;
	p.y = y;
	return p;
}

bool pteq(pt p, pt q) { // se dois pontos sao iguais
	return eq(p.x, q.x) and eq(p.y, q.y);
}

ld area(pt p, pt q, pt r) { // area de pqr
	return 0.5 * absf(p.x * (q.y - r.y) - p.y * (q.x - r.x)
			+ q.x * r.y - q.y * r.x);
}

bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return eq(area(p, q, r), 0);
}

ld dist(pt p, pt q) { // distancia
	return sqrt(sq(p.x - q.x) + sq(p.y - q.y));
}

// VETOR

vec nvec(pt p, pt q) { // novo vetor dado pontos
	vec v;
	v.x = q.x - p.x;
	v.y = q.y - p.y;
	return v;
}

ld norm(vec v) { // norma do vetor
	return dist(npt(0, 0), npt(v.x, v.y));
}

vec normalize(vec v) { // vetor normalizado
	if (!norm(v)) return v;
	ld n = norm(v);
	v.x /= n;
	v.y /= n;
	return v;
}

ld dot(vec u, vec v) { // produto escalar
	return u.x * v.x + u.y * v.y;
}

ld cross(vec u, vec v) { // norma do produto vetorial
	return u.x * v.y - u.y * v.x;
}

ld sarea(pt p, pt q, pt r) { // area com sinal
	return cross(nvec(p, q), nvec(q, r)) / 2;
}

int paral(vec u, vec v) { // se u e v sao paralelos
	u = normalize(u);
	v = normalize(v);
	if (eq(u.x, v.x) and eq(u.y, v.y)) return 1;
	if (eq(u.x, -v.x) and eq(u.y, -v.y)) return -1;
	return 0;
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return cross(nvec(p, q), nvec(q, r)) > 0;
}

// RETA

line nline(pt p, pt q) { // nova reta dado pontos
	line r;
	r.p = p;
	r.q = q;
	return r;
}

bool isvert(line r) { // se r eh vertical
	return eq(r.p.x, r.q.x);
}

ld getm(line r) { // coef. ang. de r
	if (isvert(r)) return DINF;
	return (r.p.y - r.q.y) / (r.p.x - r.q.x);
}

ld getn(line r) { // coef. lin. de r
	if (isvert(r)) return DINF;
	ld x = r.p.y - getm(r) * r.p.x;
	return x;
}

bool lineeq(line r, line s) { // r == s
	return col(r.p, r.q, s.p) and col(r.p, r.q, s.q);
}

bool paraline(line r, line s) { // se r e s sao paralelas
	if (isvert(r) and isvert(s)) return 1;
	if (isvert(r) or isvert(s)) return 0;
	return eq(getm(r), getm(s));
}

bool isinline(pt p, line r) { // se p pertence a r
	return col(p, r.p, r.q);
}

bool isinseg(pt p, line r) { // se p pertence ao seg de r
	if (pteq(p, r.p) or pteq(p, r.q)) return 1;
	return paral(nvec(r.p, p), nvec(r.q, p)) == -1;
}

pt inter(line r, line s) { // r inter s
	if (paraline(r, s)) return npt(DINF, DINF);

	if (isvert(r)) return npt(r.p.x, getm(s) * r.p.x + getn(s));
	if (isvert(s)) return npt(s.p.x, getm(r) * s.p.x + getn(r));

	ld x = (getn(s) - getn(r)) / (getm(r) - getm(s));
	return npt(x, getm(r) * x + getn(r));
}

bool interseg(line r, line s) { // se o seg de r intercepta o seg de s
	if (paraline(r, s))
		return isinseg(r.p, s) or isinseg(r.q, s);

	pt i = inter(r, s);
	return isinseg(i, r) and isinseg(i, s);
}

ld polarea(vector<pt> v) {
	ld ret = 0;
	for (int i = 0; i < sz(v); i++)
		ret += sarea(npt(0, 0), v[i], v[(i + 1) % sz(v)]);
	return absf(ret);
}

vector<pt> convexhull(vector<pt> v) {
	vector<pt> l, u;

	sort(v.begin(), v.end(), [](pt a, pt b) {
		if (eq(a.x, b.x)) return a.y < b.y;
		else return a.x < b.x;
	});

	for (int i = 0; i < sz(v); i++) {
		while (sz(l) > 1 && !ccw(v[i], l[sz(l) - 1], l[sz(l) - 2]))
			l.pop_back();
		l.pb(v[i]);
	}
	for (int i = sz(v) - 1; i >= 0; i--) {
		while (sz(u) > 1 && !ccw(v[i], u[sz(u) - 1], u[sz(u) - 2]))
			u.pop_back();
		u.pb(v[i]);
	}

	l.pop_back(); u.pop_back();

	for (int i = 0; i < sz(u); i++) l.pb(u[i]);

	return l;
}