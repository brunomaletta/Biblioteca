// Mininum Enclosing Circle
//
// O(n) com alta probabilidade

const long double EPS = 1e-12;

struct pt {
	long double x, y;
	pt() {}
	pt(long double x, long double y) : x(x), y(y) {}
	pt(const pt& p) : x(p.x), y(p.y) {}
	pt operator + (const pt& p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt& p) const { return pt(x-p.x, y-p.y); }
	pt operator * (long double c) const { return pt(x*c, y*c ); }
	pt operator / (long double c) const { return pt(x/c, y/c ); }
};

long double dot(pt p, pt q) { return p.x*q.x+p.y*q.y; }
long double dist2(pt p, pt q) { return dot(p-q, p-q); }
long double cross(pt p, pt q) { return p.x*q.y-p.y*q.x; }

pt rotate90(pt p) { return pt(p.y, -p.x); }

pt interline(pt a, pt b, pt c, pt d) {
	b = b-a; d = c-d; c = c-a;
	return a+b*cross(c, d)/cross(b, d);	
}

pt center(pt a, pt b, pt c) {
	b = (a+b)/2;
	c = (a+c)/2;
	return interline(b, b+rotate90(a-b), c, c+rotate90(a-c));	
}

struct circle {
	pt cen;
	long double r;
	circle() {}
	circle(pt cen, long double r) : cen(cen), r(r) {}
};

bool inside(circle& c, pt& p) {
	return c.r*c.r+1e-9 > dist2(p, c.cen);	
}

pt bestof3(pt a, pt b, pt c) {
	if (dot(b-a, c-a) < 1e-9) return (b+c)/2;
	if (dot(a-b, c-b) < 1e-9) return (a+c)/2;
	if (dot(a-c, b-c) < 1e-9) return (a+b)/2;
	return center(a, b, c);	
}

circle minCirc(vector<pt> v) {
	int n = v.size();
	random_shuffle(v.begin(), v.end());
	pt p = pt(0, 0);
	circle ret = circle(p, 0);
	for (int i = 0; i < n; i++) if (!inside(ret, v[i]))	{
		ret = circle(v[i], 0);
		for (int j = 0; j < i; j++) if (!inside(ret, v[j])) {
			ret = circle((v[i]+v[j])/2, sqrt(dist2(v[i], v[j]))/2);
			for (int k = 0; k < j; k++) if (!inside(ret, v[k])) {
				p = bestof3(v[i], v[j], v[k]);
				ret = circle(p, sqrt(dist2(p, v[i])));	
			}
		}	
	}
	return ret;
}
