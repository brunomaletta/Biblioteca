//Trie
//
//N deve ser maior ou igual ao numero de nos da trie
//fim indica se alguma palavra acaba nesse no
//
//Complexidade:
//Inserir e conferir string S -> O(|S|)

int trie[N][26];
int fim[N];
int nx = 1;

void insere(string &s, int p, int l, int at){
	//se nao chegou no fim da palavra termina de inserir
	if(p != l){
		int c = s[p] - 'a';
		//se nao existe um no que representa esse prefixo + c
		//cria o no 
		if(!trie[at][c])
			trie[at][c] = nx++;
		insere(s, p+1, l, trie[at][c]);
	}
	else
		fim[at] = 1;
}

int check(string &s, int p, int l, int at){
	//Cansei de comentar, Cabra, se vira
	if(p != l){
		int c = s[p] - 'a';
		if(trie[at][c])
			return check(s, p+1, l, trie[at][c]);
		else
			return 0;
	}
	return fim[at];
}
