---
weight: 10
title: "Minimum Enclosing Circle"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 O(n) com alta probabilidade



Link original: [minCirc.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/minCirc.cpp)

## Código
```cpp
const double EPS = 1e-12;
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct pt {
	double x, y;
	pt(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	pt operator + (const pt& p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt& p) const { return pt(x-p.x, y-p.y); }
	pt operator * (double c) const { return pt(x*c, y*c); }
	pt operator / (double c) const { return pt(x/c, y/c); }
};

double dot(pt p, pt q) { return p.x*q.x+p.y*q.y; }
double cross(pt p, pt q) { return p.x*q.y-p.y*q.x; }
double dist(pt p, pt q) { return sqrt(dot(p-q, p-q)); }

pt center(pt p, pt q, pt r) {
	pt a = p-r, b = q-r;
	pt c = pt(dot(a, p+r)/2, dot(b, q+r)/2);
	return pt(cross(c, pt(a.y, b.y)), cross(pt(a.x, b.x), c)) / cross(a, b);
}

struct circle {
	pt cen;
	double r;
	circle(pt cen_, double r_) : cen(cen_), r(r_) {}
	circle(pt a, pt b, pt c) {
		cen = center(a, b, c);
		r = dist(cen, a);
	}
	bool inside(pt p) { return dist(p, cen) < r+EPS; }
};

circle minCirc(vector<pt> v) {
	shuffle(v.begin(), v.end(), rng);
	circle ret = circle(pt(0, 0), 0);
	for (int i = 0; i < v.size(); i++) if (!ret.inside(v[i])) {
		ret = circle(v[i], 0);
		for (int j = 0; j < i; j++) if (!ret.inside(v[j])) {
			ret = circle((v[i]+v[j])/2, dist(v[i], v[j])/2);
			for (int k = 0; k < j; k++) if (!ret.inside(v[k]))
				ret = circle(v[i], v[j], v[k]);
		}
	}
	return ret;
}

```
