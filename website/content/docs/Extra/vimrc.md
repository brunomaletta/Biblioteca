---
weight: 10
title: "vimrc"
draft: false
toc: true
date: "2026-02-27T17:02:42-0300"
publishdate: "2026-02-27T17:02:42-0300"
description: ""
---

## Sobre
Link original: [vimrc](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Extra/vimrc)

## Código
```cpp
"" vimrc

"" {
set ts=4 sw=4 mouse=a nu ai si undofile
function H(l)
	return system("sed '/^#/d' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum", a:l)
endfunction
function P() range
	for i in range(a:firstline, a:lastline)
		let l = getline(i)
		call cursor(i, len(l))
		echo H(getline(search('{}'[1], 'bc', i) ? searchpair('{', '', '}', 'bn') : i, i))[0:2] l
	endfor
endfunction
vmap <C-H> :call P()<CR>
"" }
```
