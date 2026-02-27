---
weight: 10
title: "Parsing de Expressao"
draft: false
toc: true
date: "2024-05-09T18:39:18-0300"
publishdate: "2024-05-09T18:39:18-0300"
description: ""
---

## Sobre
 Operacoes associativas a esquerda por default

 Para mudar isso, colocar em r_assoc

 Operacoes com maior prioridade sao feitas primeiro



Link original: [parsing.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/Problemas/parsing.cpp)

## Código
```cpp
bool blank(char c) {
	return c == ' ';
}

bool is_unary(char c) {
	return c == '+' or c == '-';
}

bool is_op(char c) {
	if (is_unary(c)) return true;
	return c == '*' or c == '/' or c == '+' or c == '-';
}

bool r_assoc(char op) {
	// operator unario - deve ser assoc. a direita
	return op < 0;
}

int priority(char op) {
	// operator unario - deve ter precedencia maior
	if (op < 0) return INF;

	if (op == '*' or op == '/') return 2;
	if (op == '+' or op == '-') return 1;
	return -1;
}

void process_op(stack<int>& st, stack<int>& op) {
	char o = op.top(); op.pop();
	if (o < 0) {
		o *= -1;
		int l = st.top(); st.pop();
		if (o == '+') st.push(l);
		if (o == '-') st.push(-l);
	} else {
		int r = st.top(); st.pop();
		int l = st.top(); st.pop();
		if (o == '*') st.push(l * r);
		if (o == '/') st.push(l / r);
		if (o == '+') st.push(l + r);
		if (o == '-') st.push(l - r);
	}
}

int eval(string& s) {
	stack<int> st, op;
	bool un = true;
	for (int i = 0; i < s.size(); i++) {
		if (blank(s[i])) continue;

		if (s[i] == '(') {
			op.push('(');
			un = true;
		} else if (s[i] == ')') {
			while (op.top() != '(') process_op(st, op);
			op.pop();
			un = false;
		} else if (is_op(s[i])) {
			char o = s[i];
			if (un and is_unary(o)) o *= -1;
			while (op.size() and (
						(!r_assoc(o) and priority(op.top()) >= priority(o)) or
						(r_assoc(o) and priority(op.top()) > priority(o))))
				process_op(st, op);
			op.push(o);
			un = true;
		} else {
			int val = 0;
			while (i < s.size() and isalnum(s[i]))
				val = val * 10 + s[i++] - '0';
			i--;
			st.push(val);
			un = false;
		}
	}

	while (op.size()) process_op(st, op);
	return st.top();
}
```
