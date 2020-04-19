//binomial
//
//

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int MAX = 3e5+10;

double logfact[MAX];
void calc(){
	logfact[0] = 0;
	for (int i = 1; i < MAX; i++)
		logfact[i] = logfact[i-1] + log(i);
}

double binom(int n, int k, double p){
	return exp(logfact[n] - logfact[k] - logfact[n-k] + k * log(p) + (n-k) * log(1 - p));
}

int main(){//if you want to sample from a bin(n, p)
	calc();
	int n; double p;
	cin >> n >> p;
	binomial_distribution<int> distribution(n, p);
	int IT = 1e5;
	vector<int> freq(n+1, 0);
	for (int i = 0; i < IT; i++){
		int v = distribution(rng);
		//P(v == k) = (n choose k)p^k (1-p)^(n-k) = binom(n, k, p)
		freq[v]++;
	}
	cout << fixed << setprecision(5);
	for (int i = 0; i <= n; i++)
		cout << double(freq[i])/IT << " ~= " << binom(n, i, p) << endl;	
}

