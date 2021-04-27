// Divide and Conquer DP
//
// Tudo 1-based!!!
// Particiona o array em k subarrays
// maximizando o somatorio das queries
//
// O(k n log n), assumindo quer query(l, r) eh O(1)

ll dp[MAX][2];

void solve(int k, int l, int r, int lk, int rk) {
	if (l > r) return;
	int m = (l+r)/2, p = -1;
	ll& ans = dp[m][k&1] = -LINF;
	// ans = dp[m][~k&1], p = m+1; // para intervalos vazios
	for (int i = lk; i <= min(rk, m); i++) {
		ll at = dp[i-1][~k&1] + query(i, m);
		if (at > ans) ans = at, p = i;
	}
	solve(k, l, m-1, lk, p), solve(k, m+1, r, p, rk);
}

ll DC(int n, int k) {
	dp[0][0] = dp[0][1] = 0;
	// garante que todo mundo pertence a algum intervalo
	for (int i = 1; i <= n; i++) dp[i][0] = -LINF;
	// se puder usar intervalos vazios, usar solve(i, 1, n, 1, n)
	for (int i = 1; i <= k; i++) solve(i, i, n, i, n);
	return dp[n][k&1];
}
