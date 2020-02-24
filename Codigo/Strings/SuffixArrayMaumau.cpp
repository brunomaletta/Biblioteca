// Suffix Array Linear
//
// Complexidades:
// karkkainen, rnk, kasai - O(n)
// RMQ::build and RMQ::query - usualy O(n) & O(logn)

const int MAX = 1000010;
const int MAXSZ = MAX;

bool k_cmp(int a1, int b1, int a2, int b2, int a3 = 0, int b3 = 0) {
	return a1 != b1 ? a1 < b1 : (a2 != b2 ? a2 < b2 : a3 < b3);
}

int bucket[MAXSZ+1], tmp[MAXSZ];
template<class T> void k_radix(T keys, int *in, int *out,
		int off, int n, int k) {
	memset(bucket, 0, sizeof(int) * (k+1));

	for(int j = 0; j < n; j++)
		bucket[keys[in[j]+off]]++;
	for(int j = 0, sum = 0; j <= k; j++)
		sum += bucket[j], bucket[j] = sum - bucket[j];
	for(int j = 0; j < n; j++)
		out[bucket[keys[in[j]+off]]++] = in[j];
}

int m0[MAXSZ/3+1];
vector<int> k_rec(const vector<int>& v, int k) {
	int n = v.size()-3, sz = (n+2)/3, sz2 = sz + n/3;
	if(n < 2) return vector<int>(n);

	vector<int> sub(sz2+3);
	for(int i = 1, j = 0; j < sz2; i += i%3, j++)
		sub[j] = i;

	k_radix(v.begin(), &sub[0], tmp, 2, sz2, k);
	k_radix(v.begin(), tmp, &sub[0], 1, sz2, k);
	k_radix(v.begin(), &sub[0], tmp, 0, sz2, k);

	int last[3] = {-1, -1, -1}, unique = 0;
	for(int i = 0; i < sz2; i++) {
		bool diff = false;
		for(int j = 0; j < 3; last[j] = v[tmp[i]+j], j++)
			diff |= last[j] != v[tmp[i]+j];
		unique += diff;

		if(tmp[i]%3 == 1) sub[tmp[i]/3] = unique;
		else sub[tmp[i]/3 + sz] = unique;
	}

	vector<int> rec;
	if(unique < sz2) {
		rec = k_rec(sub, unique);
		rec.resize(sz2+sz);
		for(int i = 0; i < sz2; i++) sub[rec[i]] = i+1;
	} else {
		rec.resize(sz2+sz);
		for(int i = 0; i < sz2; i++) rec[sub[i]-1] = i;
	}

	for(int i = 0, j = 0; j < sz; i++)
		if(rec[i] < sz)
			tmp[j++] = 3*rec[i];
	k_radix(v.begin(), tmp, m0, 0, sz, k);
	for(int i = 0; i < sz2; i++)
		rec[i] = rec[i] < sz ? 3*rec[i] + 1 : 3*(rec[i] - sz) + 2;

	int prec = sz2-1, p0 = sz-1, pret = sz2+sz-1;
	while(prec >= 0 && p0 >= 0)
		if(rec[prec]%3 == 1 && k_cmp(v[m0[p0]], v[rec[prec]],
					sub[m0[p0]/3], sub[rec[prec]/3+sz]) ||
				rec[prec]%3 == 2 && k_cmp(v[m0[p0]], v[rec[prec]],
					v[m0[p0]+1], v[rec[prec]+1],
					sub[m0[p0]/3+sz], sub[rec[prec]/3+1]))
			rec[pret--] = rec[prec--];
		else
			rec[pret--] = m0[p0--];
	if(p0 >= 0) memcpy(&rec[0], m0, sizeof(int) * (p0+1));

	if(n%3==1) rec.erase(rec.begin());
	return rec;
}

vector<int> karkkainen(const string& s) {
	int n = s.size(), cnt = 1;
	vector<int> v(n + 3);

	for(int i = 0; i < n; i++) v[i] = i;
	k_radix(s.begin(), &v[0], tmp, 0, n, 256);
	for(int i = 0; i < n; cnt += (i+1 < n && s[tmp[i+1]] != s[tmp[i]]), i++)
		v[tmp[i]] = cnt;

	return k_rec(v, cnt);
}

vector<int> rnk(string s, vector<int> sa){
	int n = s.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++) ra[sa[i]] = i;
	return ra;
}

vector<int> kasai(const string& s, const vector<int>& sa) {
	int n = sa.size();
	vector<int> prm(n), ans(n-1);
	for(int i = 0; i < n; i++) prm[sa[i]] = i;

	for(int h = 0, i = 0; i < n; i++)
		if(prm[i]) {
			int j = sa[prm[i]-1], ij = max(i, j);
			while(ij + h < n && s[i+h] == s[j+h]) h++;
			ans[prm[i]-1] = h;
			if(h) h--;
		}
	return ans;
}

main(){
	n = s.size();
	auto sa = karkkainen(s);
	auto rk = rnk(s, sa)	;
	auto lcp_v = kasai(s, sa);
	RMQ::build(n-1, lcp_v);

	auto lcp = [&](int l, int r){
		#warning must build SA, LCP and RMQ structure
		if (l == r) return n - l;

		l = rk[l], r = rk[r];
		if (l > r) swap(l, r);
		return sqrtTree::query(l, r-1);
	};
}
