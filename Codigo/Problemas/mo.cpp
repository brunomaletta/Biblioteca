// Mo algorithm - distinct values
//
// O(n sqrt(n) + q)

void add(int pos){
	occ[a[pos]]++;
	counter += (occ[a[pos]] == 1);
}

void remove(int pos){
	occ[a[pos]]--;
	counter -= (occ[a[pos]] == 0);
}

vector<pii> query(q);
vector<pair<pii, int>> s(q);
for (int i = 0; i < q; i++){
	int l, r;
	scanf("%d%d", &l, &r);
	l--; r--;
	query[i] = pii(l, r);
	s[i] = {{l/SQ, r}, i};
}
sort(s.begin(), s.end()); //sort queries
for (int i = 0; i < q; i++){
	int iq = s[i].second;
	pii q = query[iq];
	while (L < q.first){
		remove(L);
		L++;
	}	
	while (L > q.first){
		L--;
		add(L);
	}
	while (R < q.second){
		R++;
		add(R);
	}
	while (R > q.second){
		remove(R);
		R--;
	}
	ans[iq] = counter;
}

