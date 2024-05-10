---
weight: 10
title: "SegTree 2D Iterativa"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Consultas 0-based

 Um valor inicial em (x, y) deve ser colocado em seg[x+n][y+n]

 Query: soma do retangulo ((x1, y1), (x2, y2))

 Update: muda o valor da posicao (x, y) para val

 Nao pergunte como que essa coisa funciona



 Para query com distancia de manhattan <= d, faca

 nx = x+y, ny = x-y

 Update em (nx, ny), query em ((nx-d, ny-d), (nx+d, ny+d))



 Se for de min/max, pode tirar os if's da 'query', e fazer

 sempre as 4 operacoes. Fica mais rapido



 Complexidades:

 build - O(n^2)

 query - O(log^2(n))

 update - O(log^2(n))



Link original: [segTree2D.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Estruturas/Segtree/segTree2D.cpp)

## Código
```cpp
int seg[2*MAX][2*MAX], n;

void build() {
	for (int x = 2*n; x; x--) for (int y = 2*n; y; y--) {
		if (x < n) seg[x][y] = seg[2*x][y] + seg[2*x+1][y];
		if (y < n) seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}

int query(int x1, int y1, int x2, int y2) {
	int ret = 0, y3 = y1 + n, y4 = y2 + n;
	for (x1 += n, x2 += n; x1 <= x2; ++x1 /= 2, --x2 /= 2)
		for (y1 = y3, y2 = y4; y1 <= y2; ++y1 /= 2, --y2 /= 2) {
			if (x1%2 == 1 and y1%2 == 1) ret += seg[x1][y1];
			if (x1%2 == 1 and y2%2 == 0) ret += seg[x1][y2];
			if (x2%2 == 0 and y1%2 == 1) ret += seg[x2][y1];
			if (x2%2 == 0 and y2%2 == 0) ret += seg[x2][y2];
		}
	
	return ret;
}

void update(int x, int y, int val) {
	int y2 = y += n;
	for (x += n; x; x /= 2, y = y2) {
		if (x >= n) seg[x][y] = val;
		else seg[x][y] = seg[2*x][y] + seg[2*x+1][y];
		
		while (y /= 2) seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}
```
