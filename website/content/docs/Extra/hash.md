---
weight: 10
title: "hash.sh"
draft: false
toc: true
date: "2026-02-27T17:02:42-0300"
publishdate: "2026-02-27T17:02:42-0300"
description: ""
---

## Sobre
Link original: [hash.sh](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/hash.sh)

## Código
```cpp
# Para usar (hash das linhas [l1, l2]):
# bash hash.sh arquivo.cpp l1 l2
sed -n $2','$3' p' $1 | sed '/^#w/d' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
```
