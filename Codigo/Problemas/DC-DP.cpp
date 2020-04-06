// Divide and Conquer DP
//
// Particiona o array em k subarrays
// maximizando o somatorio das queries
//
// O(k n log n), assumindo quer query(l, r) eh O(1)

typedef long long ll;

ll dp[MAX][2];

void solve(int k, int l, int r, int lk, int rk) {
	if (l > r) return;
	int m = (l+r)/2, p = -1;
	ll& ans = dp[m][k&1] = -LINF;
	for (int i = lk; i <= min(rk, m); i++) {
		ll at = dp[i-1][~k&1] + query(i, m);
		if (at > ans) ans = at, p = i;
	}
	solve(k, l, m-1, lk, p), solve(k, m+1, r, p, rk);
}

ll DC(int n, int k) {
	dp[0][0] = dp[0][1] = 0;
	for (int i = 1; i <= n; i++) dp[i][0] = -LINF;
	for (int i = 1; i <= k; i++) solve(i, i, n, i, n);
	return dp[n][k&1];
}
