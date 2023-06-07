// Crivo de Eratosthenes

// "O" crivo
//
// Encontra maior divisor primo
// Um numero eh primo sse divi[x] == x
// fact fatora um numero <= lim
// A fatoracao sai ordenada
//
// crivo - O(n log(log(n)))
// fact - O(log(n))

int divi[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) divi[i] = 1;

	for (int i = 2; i <= lim; i++) if (divi[i] == 1)
		for (int j = i; j <= lim; j += i) divi[j] = i;
}

#warning A funcao fact ira adicionar o 1 no vetor se voce tentar fatorar especificamente o numero 1
void fact(vector<int>& v, int n) {
	if (n != divi[n]) fact(v, n/divi[n]);
	v.push_back(divi[n]);
}

// Crivo linear
//
// Mesma coisa que o de cima, mas tambem
// calcula a lista de primos
//
// O(n)

int divi[MAX];
vector<int> primes;

void crivo(int lim) {
	divi[1] = 1;
	for (int i = 2; i <= lim; i++) {
		if (divi[i] == 0) divi[i] = i, primes.push_back(i);
		for (int j : primes) {
			if (j > divi[i] or i*j > lim) break;
			divi[i*j] = j;
		}
	}
}

// Crivo de divisores
//
// Encontra numero de divisores
// ou soma dos divisores
//
// O(n log(n))

int divi[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) divi[i] = 1;

	for (int i = 2; i <= lim; i++)
		for (int j = i; j <= lim; j += i) {
			// para numero de divisores
			divi[j]++;
			// para soma dos divisores
			divi[j] += i;
		}
}

// Crivo de totiente
//
// Encontra o valor da funcao
// totiente de Euler
//
// O(n log(log(n)))

int tot[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) {
		tot[i] += i;
		for (int j = 2*i; j <= lim; j += i)
			tot[j] -= tot[i];
	}
}

// Crivo de funcao de mobius
//
// O(n log(log(n)))

char meb[MAX];

void crivo(int lim) {
	for (int i = 2; i <= lim; i++) meb[i] = 2;
	meb[1] = 1;
	for (int i = 2; i <= lim; i++) if (meb[i] == 2)
		for (int j = i; j <= lim; j += i) if (meb[j]) {
			if (meb[j] == 2) meb[j] = 1;
			meb[j] *= j/i%i ? -1 : 0;
		}
}

// Crivo linear de funcao multiplicativa
//
// Computa f(i) para todo 1 <= i <= n, sendo f
// uma funcao multiplicativa (se gcd(a,b) = 1,
// entao f(a*b) = f(a)*f(b))
// f_prime tem que computar f de um primo, e
// add_prime tem que computar f(p^(k+1)) dado f(p^k) e p
// Se quiser computar f(p^k) dado p e k, usar os comentarios
//
// O(n)

vector<int> primes;
int f[MAX], pot[MAX];
//int expo[MAX];

void sieve(int lim) {
	// Funcoes para soma dos divisores:
	auto f_prime = [](int p) { return p+1; };
	auto add_prime = [](int fpak, int p) { return fpak*p+1; };
	//auto f_pak = [](int p, int k) {};

	f[1] = 1;
	for (int i = 2; i <= lim; i++) {
		if (!pot[i]) {
			primes.push_back(i);
			f[i] = f_prime(i), pot[i] = i;
			//expo[i] = 1;
		}
		for (int p : primes) {
			if (i*p > lim) break;
			if (i%p == 0) {
				f[i*p] = f[i / pot[i]] * add_prime(f[pot[i]], p);
				// se for descomentar, tirar a linha de cima tambem
				//f[i*p] = f[i / pot[i]] * f_pak(p, expo[i]+1);
				//expo[i*p] = expo[i]+1;
				pot[i*p] = pot[i] * p;
				break;
			} else {
				f[i*p] = f[i] * f[p];
				pot[i*p] = p;
				//expo[i*p] = 1;
			}
		}
	}
}
