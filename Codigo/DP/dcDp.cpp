// Divide and Conquer DP
//
// Particiona o array em k subarrays
// minimizando o somatorio das queries
//
// O(k n log n), assumindo quer query(l, r) eh O(1)

ll dp[MAX][2];

void solve(int k, int l, int r, int lk, int rk) {
	if (l > r) return;
	int m = (l+r)/2, p = -1;
	auto& ans = dp[m][k&1] = LINF;
	for (int i = max(m, lk); i <= rk; i++) {
		ll at = dp[i+1][~k&1] + query(m, i);
		if (at < ans) ans = at, p = i;
	}
	solve(k, l, m-1, lk, p), solve(k, m+1, r, p, rk);
}

ll DC(int n, int k) {
	dp[n][0] = dp[n][1] = 0;
	for (int i = 0; i < n; i++) dp[i][0] = LINF;
	for (int i = 1; i <= k; i++) solve(i, 0, n-i, 0, n-i);
	return dp[0][k&1];
}
