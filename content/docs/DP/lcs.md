---
weight: 10
title: "Longest Common Subsequence"
draft: false
toc: true
date: "2024-05-09T18:39:19-0300"
publishdate: "2024-05-09T18:39:19-0300"
description: ""
---

## Sobre
 Computa a LCS entre dois arrays usando

 o algoritmo de Hirschberg para recuperar



 O(n*m), O(n+m) de memoria



Link original: [lcs.cpp](https://github.com/brunomaletta/Biblioteca/tree/master/Codigo/DP/lcs.cpp)

## Código
```cpp
int lcs_s[MAX], lcs_t[MAX];
int dp[2][MAX];

// dp[0][j] = max lcs(s[li...ri], t[lj, lj+j])
void dp_top(int li, int ri, int lj, int rj) {
	memset(dp[0], 0, (rj-lj+1)*sizeof(dp[0][0]));
	for (int i = li; i <= ri; i++) {
		for (int j = rj; j >= lj; j--)
			dp[0][j - lj] = max(dp[0][j - lj],
			(lcs_s[i] == lcs_t[j]) + (j > lj ? dp[0][j-1 - lj] : 0));
		for (int j = lj+1; j <= rj; j++)
			dp[0][j - lj] = max(dp[0][j - lj], dp[0][j-1 -lj]);
	}
}

// dp[1][j] = max lcs(s[li...ri], t[lj+j, rj])
void dp_bottom(int li, int ri, int lj, int rj) {
	memset(dp[1], 0, (rj-lj+1)*sizeof(dp[1][0]));
	for (int i = ri; i >= li; i--) {
		for (int j = lj; j <= rj; j++)
			dp[1][j - lj] = max(dp[1][j - lj],
			(lcs_s[i] == lcs_t[j]) +  (j < rj ? dp[1][j+1 - lj] : 0));
		for (int j = rj-1; j >= lj; j--)
			dp[1][j - lj] = max(dp[1][j - lj], dp[1][j+1 - lj]);
	}
}

void solve(vector<int>& ans, int li, int ri, int lj, int rj) {
	if (li == ri){
		for (int j = lj; j <= rj; j++)
			if (lcs_s[li] == lcs_t[j]){
				ans.push_back(lcs_t[j]);
				break;
			}
		return;
	}
	if (lj == rj){
		for (int i = li; i <= ri; i++){
			if (lcs_s[i] == lcs_t[lj]){
				ans.push_back(lcs_s[i]);
				break;
			}
		}
		return;
	}
	int mi = (li+ri)/2;
	dp_top(li, mi, lj, rj), dp_bottom(mi+1, ri, lj, rj);

	int j_ = 0, mx = -1;

	for (int j = lj-1; j <= rj; j++) {
		int val = 0;
		if (j >= lj) val += dp[0][j - lj];
		if (j < rj) val += dp[1][j+1 - lj];

		if (val >= mx) mx = val, j_ = j;
	}
	if (mx == -1) return;
	solve(ans, li, mi, lj, j_), solve(ans, mi+1, ri, j_+1, rj);
}

vector<int> lcs(const vector<int>& s, const vector<int>& t) {
	for (int i = 0; i < s.size(); i++) lcs_s[i] = s[i];
	for (int i = 0; i < t.size(); i++) lcs_t[i] = t[i];
	vector<int> ans;
	solve(ans, 0, s.size()-1, 0, t.size()-1);
	return ans;
}
```
