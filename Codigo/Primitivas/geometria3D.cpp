// Primitivas Geometricas 3D

typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

struct pt { // ponto
	ld x, y, z;
	pt(ld x_ = 0, ld y_ = 0, ld z_ = 0) : x(x_), y(y_), z(z_) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		if (!eq(y, p.y)) return y < p.y;
		if (!eq(z, p.z)) return z < p.z;
		return 0;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y) and eq(z, p.z);
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y, z+p.z); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y, z-p.z); }
	pt operator * (const ld c) const { return pt(x*c  , y*c  , z*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  , z/c  ); }
	ld operator * (const pt p) const { return x*p.x + y*p.y + z*p.z; }
	pt operator ^ (const pt p) const { return pt(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x); }
};

// converte de coordenadas polares para cartesianas
// (angulos devem estar em radianos)
pt convert(ld rho, ld th, ld phi) {
	return pt(sin(phi) * cos(th), sin(phi) * sin(th), cos(phi)) * rho;
}

// distancia
ld dist(pt a, pt b) {
	return sqrt(sq(a.x-b.x) + sq(a.y-b.y) + sq(a.z-b.z));
}

// rotaciona p ao redor do eixo u por um angulo a
pt rotate(pt p, pt u, ld a) {
	u = u / dist(u, pt());
	return u * (u * p) + (u ^ p ^ u) * cos(a) + (u ^ p) * sin(a);
}
