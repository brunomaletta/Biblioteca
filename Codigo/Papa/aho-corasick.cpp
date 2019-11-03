const int N=100010;
const int M=26;
//N= tamanho da trie, M tamanho do alfabeto
int to[N][M], Link[N], fim[N];
int idx = 1;
void add_str(string &s)
{
	int v = 0;
	for (int i = 0; i < s.size(); i++) {
		if (!to[v][s[i]]) to[v][s[i]] = idx++;
		v = to[v][s[i]];
	}
	fim[v] = 1;
}

void process()
{
	queue<int> fila;
	fila.push(0);
	while (!fila.empty()) {
		int cur = fila.front();
		fila.pop();
		int l = Link[cur];
		fim[cur] |= fim[l];
		for (int i = 0; i < M; i++) {
			if (to[cur][i]) {
				if (cur != 0) {
					Link[to[cur][i]] = to[l][i];
				}
				else
					Link[to[cur][i]] = 0;
				fila.push(to[cur][i]);
			}
			else {
				to[cur][i] = to[l][i];
			}
		}
	}
}

int resolve(string &s)
{
	int v = 0, r = 0;
	for (int i = 0; i < s.size(); i++) {
		v = to[v][s[i]];
		if (fim[v]) r++, v = 0;
	}
	return r;
}
