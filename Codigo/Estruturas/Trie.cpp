#include <bits/stdc++.h>
using namespace std;
#define N 1048576

int trie[N][26];
int fim[N];
int nx = 1;

void insere(string &s, int p, int l, int at){
	if(p != l){
		int c = s[p] - 'a';
		if(!trie[at][c])
			trie[at][c] = nx++;
		insere(s, p+1, l, trie[at][c]);
	}
	else
		fim[at] = 1;
}

int check(string &s, int p, int l, int at){
	if(p != l){
		int c = s[p] - 'a';
		if(trie[at][c])
			return check(s, p+1, l, trie[at][c]);
		else
			return 0;
	}
	return fim[at];
}

int main(int argc, char const *argv[])
{
	string s; int a;
	while(cin >> a >> s){
		if(a == 1)
			insere(s, 0, s.size(), 0);
		else
			printf("%i\n", check(s, 0, s.size(), 0));
	}
	
	return 0;
}