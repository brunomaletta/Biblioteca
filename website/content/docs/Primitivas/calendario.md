---
weight: 10
title: "Calendario"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Congruencia de Zeller



 Os dias da semana correspondem aos restos % 7

 Segunda=0, Terca=1, ..., Domingo=6



Link original: [calendario.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Primitivas/calendario.cpp)

## Código
```cpp
int get_id(int d, int m, int y) {
    if (m < 3) y--, m += 12;
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307;
}

tuple<int, int, int> date(int id) {
    int x = id + 1789995, n = 4 * x / 146097, i, j, d, m, y;
    x -= (146097 * n + 3) / 4;
    i = (4000 * (x + 1)) / 1461001;
    x -= 1461 * i / 4 - 31;
    j = 80 * x / 2447, d = x - 2447 * j / 80;
    x = j / 11;
    m = j + 2 - 12 * x, y = 100 * (n - 49) + i + x;
    return {d, m, y};
}
```
