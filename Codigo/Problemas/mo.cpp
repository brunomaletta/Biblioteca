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

