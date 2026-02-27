---
weight: 10
title: "timer T; T() -> retorna o tempo em ms desde que declarou"
draft: false
toc: true
date: "2026-02-27T16:24:59-0300"
publishdate: "2026-02-27T16:24:59-0300"
description: ""
---

## Sobre
Link original: [timer.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/timer.cpp)

## Código
```cpp
struct timer : high_resolution_clock {
	const time_point start;
	timer(): start(now()) {}
	int operator()() {
		return duration_cast<milliseconds>(now() - start).count();
	}
};
```
