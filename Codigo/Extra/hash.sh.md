---
weight: 10
title: "hash.sh"
draft: false
toc: true
date: "2026-02-27T16:29:55-0300"
publishdate: "2026-02-27T16:29:55-0300"
description: ""
---

## Sobre
Link original: [hash.sh](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/hash.sh)

## Código
```cpp
sed -n $2','$3' p' $1 | sed '/^#w/d' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
```
