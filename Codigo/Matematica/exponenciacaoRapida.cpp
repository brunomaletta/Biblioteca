int pow(int x, int y, int m){
	//x elevado a y mod m
	int a = 1;
	while(y){
		if(y & 1){
			a *= x;
			a = a % m;
		}
		y /= 2;
		x *= x;
		x = x % m;
	}
	return a;
}