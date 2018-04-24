int phi(int n){
	//p eh um vector com primos 
	int t = 1;

	for(int i = 0; p[i] <= sqrt(n); i++)
		if(n % p[i] == 0){
			t *= p[i] - 1;
			n /= p[i];
			while(n % p[i] == 0){
				n /= p[i];
				t *= p[i];
			}
		}

	if(n > 1) t *= n - 1;

	return t;
}