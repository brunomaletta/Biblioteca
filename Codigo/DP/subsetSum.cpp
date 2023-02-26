// Subset sum
//
// Retorna max(x <= t tal que existe subset de w que soma x)
//
// O(n * max(w))
// O(max(w)) de memoria

int subset_sum(vector<int> w, int t) {
	int pref = 0, k = 0;
	while (k < w.size() and pref + w[k] <= t) pref += w[k++];
	if (k == w.size()) return pref;
	int W = *max_element(w.begin(), w.end());
	vector<int> last, dp(2*W, -1);
	dp[W - (t-pref)] = k;
	for (int i = k; i < w.size(); i++) {
		last = dp;
		for (int x = 0; x < W; x++) dp[x+w[i]] = max(dp[x+w[i]], last[x]);
		for (int x = 2*W - 1; x > W; x--)
			for (int j = max(0, last[x]); j < dp[x]; j++)
				dp[x-w[j]] = max(dp[x-w[j]], j);
	}
	int ans = t;
	while (dp[W - (t-ans)] < 0) ans--;
	return ans;
}
