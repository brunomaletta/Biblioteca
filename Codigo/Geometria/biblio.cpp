#include <bits/stdc++.h>

using namespace std;

#define sc(a) scanf("%d", &a)
#define sc2(a,b) scanf("%d %d", &a, &b)
#define pri(x) printf("%d\n", x)
#define prie(x) printf("%d ", x)
#define sz(x) (int)((x).size())
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define sq(x) ((x)*(x))
#define BUFF ios::sync_with_stdio(false)

typedef long long int ll;
typedef double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

struct pt { // ponto
	ld x, y;
	pt() {}
	pt(ld x, ld y) : x(x), y(y) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		return y < p.y;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y);
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ld c) const { return pt(x*c  , y*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  ); }
};

struct line { // reta
	pt p, q;
	line() {}
	line(pt p, pt q) : p(p), q(q) {}
};

// PONTO & VETOR

ld dist(pt p, pt q) { // distancia
	return sqrt(sq(p.x - q.x) + sq(p.y - q.y));
}

ld dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}

ld norm(pt v) { // norma do vetor
	return dist(pt(0, 0), v);
}

pt normalize(pt v) { // vetor normalizado
	if (!norm(v)) return v;
	v = v / norm(v);
	return v;
}

ld dot(pt u, pt v) { // produto escalar
	return u.x * v.x + u.y * v.y;
}

ld cross(pt u, pt v) { // norma do produto vetorial
	return u.x * v.y - u.y * v.x;
}

ld sarea(pt p, pt q, pt r) { // area com sinal
	return cross(q - p, r - q) / 2;
}

bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return eq(sarea(p, q, r), 0);
}

int paral(pt u, pt v) { // se u e v sao paralelos
	u = normalize(u);
	v = normalize(v);
	if (eq(u.x, v.x) and eq(u.y, v.y)) return 1;
	if (eq(u.x, -v.x) and eq(u.y, -v.y)) return -1;
	return 0;
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea(p, q, r) > 0;
}

pt rotate(pt p, ld th) { // rotaciona o ponto th radianos
	return pt(p.x * cos(th) - p.y * sin(th),
		    p.x * sin(th) + p.y * cos(th));
}

pt rotate90(pt p) { // rotaciona 90 graus
	return pt(-p.y, p.x);
}

// RETA

bool isvert(line r) { // se r eh vertical
	return eq(r.p.x, r.q.x);
}

ld getm(line r) { // coef. ang. de r
	if (isvert(r)) return DINF;
	return (r.p.y - r.q.y) / (r.p.x - r.q.x);
}

ld getn(line r) { // coef. lin. de r
	if (isvert(r)) return DINF;
	return r.p.y - getm(r) * r.p.x;
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
	if (p == r.p or p == r.q) return 1;
	return paral(p - r.p, p - r.q) == -1;
}

pt proj(pt p, line r) { // projecao do ponto p na reta r
	if (r.p == r.q) return r.p;
	r.q = r.q - r.p; p = p - r.p;
	pt proj = r.q * (dot(p, r.q) / dot(r.q, r.q));
	return proj + r.p;
}

pt inter(line r, line s) { // r inter s
	if (paraline(r, s)) return pt(DINF, DINF);

	if (isvert(r)) return pt(r.p.x, getm(s) * r.p.x + getn(s));
	if (isvert(s)) return pt(s.p.x, getm(r) * s.p.x + getn(r));

	ld x = (getn(s) - getn(r)) / (getm(r) - getm(s));
	return pt(x, getm(r) * x + getn(r));
}

bool interseg(line r, line s) { // se o seg de r intercepta o seg de s
	if (paraline(r, s)) {
		return isinseg(r.p, s) or isinseg(r.q, s)
		    or isinseg(s.p, r) or isinseg(s.q, r);
	}

	pt i = inter(r, s);
	return isinseg(i, r) and isinseg(i, s);
}

ld disttoline(pt p, line r) { // distancia do ponto a reta
	return dist(p, proj(p, r));
}

ld disttoseg(pt p, line r) { // distancia do ponto ao seg
	if (isinseg(proj(p, r), r))
		return disttoline(p, r);
	return min(dist(p, r.p), dist(p, r.q));
}

ld distseg(line a, line b) { // distancia entre seg
	if (interseg(a, b)) return 0;
	
	ld ret = DINF;
	ret = min(ret, disttoseg(a.p, b));
	ret = min(ret, disttoseg(a.q, b));
	ret = min(ret, disttoseg(b.p, a));
	ret = min(ret, disttoseg(b.q, a));

	return ret;
}

// POLIGONO

ld polper(vector<pt> v) { // perimetro do poligono
	ld ret = 0;
	for (int i = 0; i < sz(v); i++)
		ret += dist(v[i], v[(i + 1) % sz(v)]);
	return ret;
}

ld polarea(vector<pt> v) { // area do poligono
	ld ret = 0;
	for (int i = 0; i < sz(v); i++)
		ret += sarea(pt(0, 0), v[i], v[(i + 1) % sz(v)]);
	return abs(ret);
}

bool onpol(pt p, vector<pt> v) { // se um ponto esta na fronteira do poligono
	for (int i = 0; i < sz(v); i++)
		if (isinseg(p, line(v[i], v[(i + 1) % sz(v)]))) return 1;
	return 0;
}

bool inpol(pt p, vector<pt> v) { // se um ponto pertence ao poligono
	if (onpol(p, v)) return 1;
	int c = 0;
	line r = line(p, pt(DINF, pi * DINF));
	for (int i = 0; i < sz(v); i++) {
		line s = line(v[i], v[(i + 1) % sz(v)]);
		if (interseg(r, s)) c++;
	}
	return c & 1;
}

bool interpol(vector<pt> v1, vector<pt> v2) { // se dois poligonos se interceptam
	for (int i = 0; i < sz(v1); i++) if (inpol(v1[i], v2)) return 1;
	for (int i = 0; i < sz(v2); i++) if (inpol(v2[i], v1)) return 1;
	return 0;
}

ld distpol(vector<pt> v1, vector<pt> v2) { // distancia entre poligonos
	if (interpol(v1, v2)) return 0;

	ld ret = DINF;

	for (int i = 0; i < sz(v1); i++) for (int j = 0; j < sz(v2); j++)
		ret = min(ret, distseg(line(v1[i], v1[(i + 1) % sz(v1)]),
					     line(v2[j], v2[(j + 1) % sz(v2)])));
	return ret;
}

vector<pt> convexhull(vector<pt> v) { // convex hull
	vector<pt> l, u;

	sort(v.begin(), v.end());

	for (int i = 0; i < sz(v); i++) {
		while (sz(l) > 1 and !ccw(v[i], l[sz(l) - 1], l[sz(l) - 2]))
			l.pop_back();
		l.pb(v[i]);
	}
	for (int i = sz(v) - 1; i >= 0; i--) {
		while (sz(u) > 1 and !ccw(v[i], u[sz(u) - 1], u[sz(u) - 2]))
			u.pop_back();
		u.pb(v[i]);
	}

	l.pop_back(); u.pop_back();

	for (int i = 0; i < sz(u); i++) l.pb(u[i]);

	return l;
}

// CIRCULO

pt getcenter(pt a, pt b, pt c) { // centro da circunferencia dado 3 pontos
	b = (a + b) / 2;
	c = (a + c) / 2;
	return inter(line(b, b + rotate90(a - b)),
			 line(c, c + rotate90(a - c)));
}
