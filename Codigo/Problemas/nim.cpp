// Jogo de Nim
//
// Calcula movimento otimo do jogo classico de Nim
// Assume que o estado atual eh perdedor
// Funcao move retorna um par com a pilha (0 indexed)
// e quanto deve ser tirado dela
// XOR deve estar armazenado em x
// Para mudar um valor, faca insere(novo_valor),
// atualize o XOR e mude o valor em v
//
// MAX2 = teto do log do maior elemento
// possivel nas pilhas
//
// O(log(n)) amortizado
 
int v[MAX], n, x;
stack<int> pi[MAX2];
 
void insere(int p) {
    for (int i = 0; i < MAX2; i++) if (v[p] & (1 << i)) pi[i].push(p);
}
 
pair<int, int> move() {
    int bit = 0; while (x >> bit) bit++; bit--;
   
    // tira os caras invalidos
    while ((v[pi[bit].top()] & (1 << bit)) == 0) pi[bit].pop();
 
    int cara = pi[bit].top();
    int tirei = v[cara] - (x^v[cara]);
    v[cara] -= tirei;
 
    insere(cara);
 
    return mp(cara, tirei);
}

// Acha o movimento otimo baseado
// em v apenas
//
// O(n)

pair<int, int> move() {
	int x = 0;
	for (int i = 0; i < n; i++) x ^= v[i];

	for (int i = 0; i < n; i++) if ((v[i]^x) < v[i])
		return mp(i, v[i] - (v[i]^x));
}
