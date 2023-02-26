// Deteccao de ciclo - Tortoise and Hare
//
// Linear no tanto que tem que andar pra ciclar,
// O(1) de memoria
// Retorna um par com o tanto que tem que andar
// do f0 ate o inicio do ciclo e o tam do ciclo

pair<ll, ll> find_cycle() {
	ll tort = f(f0);
	ll hare = f(f(f0));
	ll t = 0;
	while (tort != hare) {
		tort = f(tort);
		hare = f(f(hare));
		t++;
	}
	ll st = 0;
	tort = f0;
	while (tort != hare) {
		tort = f(tort);
		hare = f(hare);
		st++;
	}

	ll len = 1;
	hare = f(tort);
	while (tort != hare) {
		hare = f(hare);
		len++;
	}
	return {st, len};
}
