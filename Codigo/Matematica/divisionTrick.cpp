// Division Trick
//
// Gera o conjunto n/i, pra todo i, em O(sqrt(n))
// copiei do github do tfg50

for(int l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
	// n / i has the same value for l <= i <= r
}
