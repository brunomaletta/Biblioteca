#include <bits/stdc++.h>
using namespace std;
#define pi acos(-1)
#define eps 1e-9

struct point{
	double x, y;
	point() {x = y = 0;}
	point(double x, double y):x(x), y(y){}
	bool operator < (point b) const{
		if(fabs(x - b.x) > eps)
			return x < b.x;
		return y < b.y;
	}
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
	if(zero(p1.y - p2.y)){
		ret.a = 0;
		ret.b = 1;
		ret.c = -p1.y;
		return ret;
	}

	ret.a = 1.0;
	ret.b = (p2.x - p1.x) / (p1.y - p2.y);
	ret.c = -p1.x - ret.b*p1.y;
 
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

double dot(vec a, vec b){
	return a.x*b.x + a.y*b.y;
}

double norma(vec v){
	return hypot(v.x, v.y);
}

double distPontoReta(point p, point a, point b){
	vec ap = toVec(a, p), ab = toVec(a, b);
	double u = dot(ap, ab) / norma(ab);
	point c = translate(a, scale(ab, u));
	return dist(p, c);
}

double angle (point a, point o, point b){
	vec oa = toVec(o, a), ob = toVec(o, b);
	return acos(dot(oa, ob) / sqrt(norma(oa)*norma(ob)));
}

double cross(vec a, vec b){
	return a.x*b.y - a.y*b.x;
}

int lado(point p, point q, point r){
	//retorna 1 se r estiver do lado esquerdo da reta pq
	double a = cross(toVec(p, q), toVec(p, r));
	if(a < 0)
		return 1;
	return 0;
}

int colinear(point p, point q, point r){
	return zero(cross(toVec(p, q), toVec(p, r)));
}

double perimetro(vector<point> &v){
	double ret = 0;
	for(int i = 0; i < v.size() - 1; i++)
		ret += dist(v[i], v[i+1]);
	return ret;
}

double area(vector<point> &v){
	double ret = 0;
	for(int i = 0; i < v.size() - 1; i++)
		ret += v[i].x*v[i+1].y - v[i].y*v[i+1].x;
	if(ret < 0) ret *= -1;
	return ret;
}

int convexo(vector<point> &v){
	int n = v.size();
	if(n <= 3)
		return 1;
	int primeiro = lado(v[0], v[1], v[2]);
	for(int i = 1; i < n - 1; i++)
		if(lado(v[i], v[i+1], v[i+2]) != primeiro)
			return 0;

	return 1;
}

int dentro(vector<point> &v, point p){
	double soma = 0;
	for(int i = 0; i < v.size() - 1; i++){
		if(lado(p, v[i], v[i+1]))
			soma += angle(v[i], p, v[i+1]);
		else
			soma-= angle(v[i], p, v[i+1]);
	}

	return zero(soma - 2*pi);
}

vector<point> convexHull(vector<point> &v){
	sort(v.begin(), v.end());

	vector<point> u;
	vector<point> l;

	int k = 0, n = v.size();
	for(int i = 0; i < n; i++){
		while(k >= 2 && lado(l[k-1], l[k-2], v[i]) != 1)
			l.erase(l.begin() + --k);

		l.push_back(v[i]);
		k++;
	}

	k = 0;
	for(int i = n-1; i >= 0; i--){
		while(k >= 2 && lado(u[k-1], u[k-2], v[i]) != 1)
			u.erase(u.begin() + --k);

		u.push_back(v[i]);
		k++;
	}

	l.erase(l.begin() + l.size() - 1);
	u.erase(u.begin() + u.size() - 1);

	for(int i = 0; i < u.size(); i++)
		l.push_back(u[i]);

	return l;
}

int main(int argc, char const *argv[])
{
	printf("Falta testar tudo\n");

	return 0;
}