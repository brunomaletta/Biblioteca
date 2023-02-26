// Geometria

typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

struct pt { // ponto
	ld x, y;
	pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		if (!eq(y, p.y)) return y < p.y;
		return 0;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y);
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ld c) const { return pt(x*c  , y*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  ); }
	ld operator * (const pt p) const { return x*p.x + y*p.y; }
	ld operator ^ (const pt p) const { return x*p.y - y*p.x; }
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

ld dist(pt p, pt q) { // distancia
	return hypot(p.y - q.y, p.x - q.x);
}

ld dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}

ld norm(pt v) { // norma do vetor
	return dist(pt(0, 0), v);
}

ld angle(pt v) { // angulo do vetor com o eixo x
	ld ang = atan2(v.y, v.x);
	if (ang < 0) ang += 2*pi;
	return ang;
}

ld sarea(pt p, pt q, pt r) { // area com sinal
	return ((q-p)^(r-q))/2;
}

bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return eq(sarea(p, q, r), 0);
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea(p, q, r) > eps;
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

bool isinseg(pt p, line r) { // se p pertence ao seg de r
	pt a = r.p - p, b = r.q - p;
	return eq((a ^ b), 0) and (a * b) < eps;
}

ld get_t(pt v, line r) { // retorna t tal que t*v pertence a reta r
	return (r.p^r.q) / ((r.p-r.q)^v);
}

pt proj(pt p, line r) { // projecao do ponto p na reta r
	if (r.p == r.q) return r.p;
	r.q = r.q - r.p; p = p - r.p;
	pt proj = r.q * ((p*r.q) / (r.q*r.q));
	return proj + r.p;
}

pt inter(line r, line s) { // r inter s
	if (eq((r.p - r.q) ^ (s.p - s.q), 0)) return pt(DINF, DINF);
	r.q = r.q - r.p, s.p = s.p - r.p, s.q = s.q - r.p;
	return r.q * get_t(r.q, s) + r.p;
}

bool interseg(line r, line s) { // se o seg de r intersecta o seg de s
	if (isinseg(r.p, s) or isinseg(r.q, s)
		or isinseg(s.p, r) or isinseg(s.q, r)) return 1;

	return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and
			ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

ld disttoline(pt p, line r) { // distancia do ponto a reta
	return 2 * abs(sarea(p, r.p, r.q)) / dist(r.p, r.q);
}

ld disttoseg(pt p, line r) { // distancia do ponto ao seg
	if ((r.q - r.p)*(p - r.p) < 0) return dist(r.p, p);
	if ((r.p - r.q)*(p - r.q) < 0) return dist(r.q, p);
	return disttoline(p, r);
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

// corta poligono com a reta r deixando os pontos p tal que 
// ccw(r.p, r.q, p)
vector<pt> cut_polygon(vector<pt> v, line r) { // O(n)
	vector<pt> ret;
	for (int j = 0; j < v.size(); j++) {
		if (ccw(r.p, r.q, v[j])) ret.push_back(v[j]);
		if (v.size() == 1) continue;
		line s(v[j], v[(j+1)%v.size()]);
		pt p = inter(r, s);
		if (isinseg(p, s)) ret.push_back(p);
	}
	ret.erase(unique(ret.begin(), ret.end()), ret.end());
	if (ret.size() > 1 and ret.back() == ret[0]) ret.pop_back();
	return ret;
}

// distancia entre os retangulos a e b (lados paralelos aos eixos)
// assume que ta representado (inferior esquerdo, superior direito)
ld dist_rect(pair<pt, pt> a, pair<pt, pt> b) {
	ld hor = 0, vert = 0;
	if (a.second.x < b.first.x) hor = b.first.x - a.second.x;
	else if (b.second.x < a.first.x) hor = a.first.x - b.second.x;
	if (a.second.y < b.first.y) vert = b.first.y - a.second.y;
	else if (b.second.y < a.first.y) vert = a.first.y - b.second.y;
	return dist(pt(0, 0), pt(hor, vert));
}

ld polarea(vector<pt> v) { // area do poligono
	ld ret = 0;
	for (int i = 0; i < v.size(); i++)
		ret += sarea(pt(0, 0), v[i], v[(i + 1) % v.size()]);
	return abs(ret);
}

// se o ponto ta dentro do poligono: retorna 0 se ta fora,
// 1 se ta no interior e 2 se ta na borda
int inpol(vector<pt>& v, pt p) { // O(n)
	int qt = 0;
	for (int i = 0; i < v.size(); i++) {
		if (p == v[i]) return 2;
		int j = (i+1)%v.size();
		if (eq(p.y, v[i].y) and eq(p.y, v[j].y)) {
			if ((v[i]-p)*(v[j]-p) < eps) return 2;
			continue;
		}
		bool baixo = v[i].y+eps < p.y;
		if (baixo == (v[j].y+eps < p.y)) continue;
		auto t = (p-v[i])^(v[j]-v[i]);
		if (eq(t, 0)) return 2;
		if (baixo == (t > eps)) qt += baixo ? 1 : -1;
	}
	return qt != 0;
}

bool interpol(vector<pt> v1, vector<pt> v2) { // se dois poligonos se intersectam - O(n*m)
	int n = v1.size(), m = v2.size();
	for (int i = 0; i < n; i++) if (inpol(v2, v1[i])) return 1;
	for (int i = 0; i < n; i++) if (inpol(v1, v2[i])) return 1;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
		if (interseg(line(v1[i], v1[(i+1)%n]), line(v2[j], v2[(j+1)%m]))) return 1;
	return 0;
}

ld distpol(vector<pt> v1, vector<pt> v2) { // distancia entre poligonos
	if (interpol(v1, v2)) return 0;

	ld ret = DINF;

	for (int i = 0; i < v1.size(); i++) for (int j = 0; j < v2.size(); j++)
		ret = min(ret, distseg(line(v1[i], v1[(i + 1) % v1.size()]),
					line(v2[j], v2[(j + 1) % v2.size()])));
	return ret;
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

// CIRCUNFERENCIA

pt getcenter(pt a, pt b, pt c) { // centro da circunf dado 3 pontos
	b = (a + b) / 2;
	c = (a + c) / 2;
	return inter(line(b, b + rotate90(a - b)),
			line(c, c + rotate90(a - c)));
}

vector<pt> circ_line_inter(pt a, pt b, pt c, ld r) { // intersecao da circunf (c, r) e reta ab
	vector<pt> ret;
	b = b-a, a = a-c;
	ld A = b*b;
	ld B = a*b;
	ld C = a*a - r*r;
	ld D = B*B - A*C;
	if (D < -eps) return ret;
	ret.push_back(c+a+b*(-B+sqrt(D+eps))/A);
	if (D > eps) ret.push_back(c+a+b*(-B-sqrt(D))/A);
	return ret;
}

vector<pt> circ_inter(pt a, pt b, ld r, ld R) { // intersecao da circunf (a, r) e (b, R)
	vector<pt> ret;
	ld d = dist(a, b);
	if (d > r+R or d+min(r, R) < max(r, R)) return ret;
	ld x = (d*d-R*R+r*r)/(2*d);
	ld y = sqrt(r*r-x*x);
	pt v = (b-a)/d;
	ret.push_back(a+v*x + rotate90(v)*y);
	if (y > 0) ret.push_back(a+v*x - rotate90(v)*y);
	return ret;
}

bool operator <(const line& a, const line& b) { // comparador pra reta
	// assume que as retas tem p < q
	pt v1 = a.q - a.p, v2 = b.q - b.p;
	if (!eq(angle(v1), angle(v2))) return angle(v1) < angle(v2);
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
		if (!eq(a.p.x, a.q.x) and (eq(b.p.x, b.q.x) or a.p.x+eps < b.p.x))
			return ccw(a.p, a.q, b.p);
		return ccw(a.p, b.q, b.p);
	}
};

// comparador pro set pra fazer sweep angle com segmentos
pt dir;
struct cmp_sweepangle {
	bool operator () (const line& a, const line& b) const {
		return get_t(dir, a) + eps < get_t(dir, b);
	}
};
