---
weight: 10
title: "debug.cpp"
draft: false
toc: true
date: "2026-02-27T17:02:42-0300"
publishdate: "2026-02-27T17:02:42-0300"
description: ""
---

## Sobre
Link original: [debug.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/debug.cpp)

## Código
```cpp
void debug_out(string s, int line) { cerr << endl; }
template<typename H, typename... T>
void debug_out(string s, int line, H h, T... t) {
    if (s[0] != ',') cerr << "Line(" << line << ") ";
    do { cerr << s[0]; s = s.substr(1);
    } while (s.size() and s[0] != ',');
    cerr << " = " << h;
    debug_out(s, line, t...);
}
#ifdef DEBUG
#define debug(...) debug_out(#__VA_ARGS__, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif
```
