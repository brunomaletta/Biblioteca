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
	pt() {}
	pt(ld x_, ld y_, ld z_) : x(x_), y(y_), z(z_) {}
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

	void rotate_x(ld a) {
		ld ny = y*cos(a) - z*sin(a);
		ld nz = y*sin(a) + z*cos(a);
		y = ny;
		z = nz;
	}
	void rotate_y(ld a) {
		ld nx =  x*cos(a) + z*sin(a);
		ld nz = -x*sin(a) + z*cos(a);
		x = nx;
		z = nz;
	}
	void rotate_z(ld a) {
		ld nx = x*cos(a) - y*sin(a);
		ld ny = x*sin(a) + y*cos(a);
		x = nx;
		y = ny;
	}
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
