#include <bits/stdc++.h>
using namespace std;
#define pi acos(-1)
#define eps 0.0000001

struct point{
	double x, y;
};
struct line{
	double a, b, c;
};
struct vec{
	double x, y;
};

int zero(double a){
	if(a < eps && -a < eps)
		return 1;
	return 0;
}

double dist(point p1, point p2){
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

point rotate(point p , double a){
	double rad = a*pi/180.0;
	point ret;
	ret.x = p.x*cos(rad) - p.y*sin(rad);
	ret.y = p.x*sin(rad) - p.x*cos(rad);
}

line coef(point p1, point p2){
	line ret;
	if(zero(p1.x - p2.x)){
		ret.a = 1;
		ret.b = 0;
		ret.c = -p1.x;
		return ret;
	}

	ret.a = (double) (p1.y - p2.y) / (p2.x - p1.x);
	ret.b = 1;
	ret.c = -(double) (ret.a * p1.x) - p1.x;

	return ret;
}

int paralelo(line l1, line l2){
	if(zero(l1.a - l2.a) && zero(l1.b - l2.b))
		return 1;
	return 0;
}

point intersecao(line l1, line l2){
	point p;
	p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
	if(zero(l1.b))
		p.y = -(l1.a*p.x + l1.c);
	else
		p.y = -(l2.a*p.x + l2.c);
	return p;
}

vec toVec(point p1, point p2){
	vec ret;
	ret.x = p2.x - p1.x;
	ret.y = p2.y - p1.y;
	return ret;
}

vec scale(vec v, double s){
	v.x *= s;
	v.y *= s;
	return v;
}

point translate(point p, vec v){
	point ret;
	ret.x = p.x + v.x;
	ret.y = p.y + v.y;
	return ret;
}

double escalar(vec a, vec b){
	return a.x*b.x + a.y*b.y;
}

double norma(vec v){
	return hypot(v.x, v.y);
}

double distPontoReta(point p, point a, point b){
	vec ap = toVec(a, p), ab = toVec(a, b);
	double u = escalar(ap, ab) / norma(ab);
	point c = translate(a, scale(ab, u));
	return dist(p, c);
}

int main(int argc, char const *argv[])
{
	printf("Falta testar tudo\n");

	return 0;
}