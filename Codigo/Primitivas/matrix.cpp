// Primitivas de matriz

ll mod(ll v){ return (v + MOD) % MOD; }
ll sum(ll l, ll r){ return mod(l+r); }
ll mult(ll l, ll r){ return mod(l*r); }
ll inverse(ll l){ return inv(l, MOD); }
bool equal(ll l, ll r){ return mod(l-r) == 0; }

template<typename T> struct matrix {
	vector<vector<T>> in;
	int row, col;

	void print(){//
		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++)
				cout << in[i][j] << " ";
			cout << endl;
		}
	}

	matrix(int row, int col, int op = 0):row(row), col(col), in(row, vector<T>(col, 0)){
		if (op) for (int i = 0; i < row; i++) in[i][i] = 1;
	}
	matrix(initializer_list<initializer_list<T>> c):
		row(c.size()), col((*c.begin()).size()){
			in = vector<vector<T>>(row, vector<T>(col, 0));
			int i, j;
			i = 0;
			for (auto &it : c){
				j = 0;
				for (auto &jt : it){
					in[i][j] = jt;
					j++;
				}
				i++;
			}
		}
	T &operator()(int i, int j){ return in[i][j]; }
	//in case of a transposed matrix, swap i and j
	matrix<T>& operator*=(T t){
		matrix<T> &l = *this;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				l(i, j) = mult(l(i, j), t); //% MOD) % MOD;
		return l;
	}
	matrix<T> operator+(matrix<T> &r){
		matrix<T> &l = *this;
		matrix<T> m(row, col, 0);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				m(i, j) = sum(l(i, j), r(i, j)); //% MOD) % MOD;
		return m;
	}
	matrix<T> operator*(matrix<T> &r){
		matrix<T> &l = *this;
		int row = l.row;
		int col = r.col;
		int K = l.col;
		matrix<T> m(row, col, 0);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				for (int k = 0; k < K; k++)
					m(i, j) = sum(m(i, j), mult(l(i, k), r(k, j)));
		return m;
	}
	matrix<T> operator^(long long e){
		matrix<T> &m = (*this);
		if (e == 0) return matrix(m.row, m.row, 1);
		if (e == 1) return m;
		if (e == 2) return m*m;
		auto m_ = m^(e/2); m_ = m_*m_;
		if (e%2 == 1) m_ = m_ * m;
		return m_;
	}
	void multiply_r(int i, T k){
		matrix<T> &m = (*this);
		for (int j = 0; j < col; j++)
			m(i, j) = mult(m(i, j), k);
	}
	void multiply_c(int j, T k){
		matrix<T> &m = (*this);
		for (int i = 0; i < row; j++)
			m(i, j) = mult(m(i, j), k);
	}
	void sum_r(int i1, int i2, T k){
		matrix<T> &m = (*this);
		for (int j = 0; j < col; j++)
			m(i1, j) = sum(m(i1, j), mult(k, m(i2, j)));

	}
	bool gaussian(int I, int J){
		matrix<T> &m = (*this);
		T tmp = m(I, J);
		if (equal(tmp, 0)) return false;
		multiply_r(I, inverse(tmp));
		for (int i = 0; i < row; i++)
			if (i != I) sum_r(i, I, mult(-1, m(i, J)));
		multiply_r(I, tmp);
		return true;
	}
	T determinant(){
		matrix<T> m = (*this);
		for (int i = 0; i < row; i++)
			if (!m.gaussian(i, i)) return 0;	

		T ans = 1;
		for (int i = 0; i < row; i++)
			ans = mult(ans, m(i, i));
		return ans;
	}
};
