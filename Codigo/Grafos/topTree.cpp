// Top Tree
//
// lct<T> t(n, w) armazena uma floresta enraizada dinamica com 'n'
// vertices indexados de 0 a n-1 com peso w[i] do tipo T.
// Varias operacoes podem ser realizadas.
//
// Complexidades:
// Construcao - O(n) espaco e tempo
// Todas as outras operacoes - O(log(n)) amortizado, \Theta(n) pior caso
// O(n) memoria em qualquer momento
//
// 1. Consultas estruturais
// - find_root(v): raiz do vertice v (seguindo arestas pai)
// - lca(v, u): ancestral comum mais baixo entre v e u, ou -1 se nao existir
// - connected(v, u): se v e u estao no mesmo componente conexo
// - parent(v, k): k-esimo pai de v (seguindo k arestas), ou -1 se nao existir
// - depth(v): numero de arestas entre v e sua raiz
// - dist(v, u): distancia entre v e u na arvore nao direcionada
// - subtree_size(v): numero de vertices na sub-arvore de v
// - adjacent(v, u): se existe uma aresta {v, u}
//
// 2. Atualizacoes estruturais
// - evert(v): rotaciona para que v seja a raiz de seu componente
// - link(v, u): adiciona aresta v -> u (pai de v eh u)
//   . Pre-condicao: nao deve criar ciclo!
//   . Se v nao eh raiz, eh feito evert(v)
// - cut(v): remove aresta de v para seu pai
// - cut(v, u): remove aresta {v, u}
//   . Pre-condicao: aresta {v, u} deve existir!
//
// 3. Operacoes em vertices
// - t[v]: retorna w[v]
//   . Pode ser usado para atualizar: t[v]++
//
// Para as seguintes operacoes que agregam w:
//
// Defina uma tag lazy associativa e comutativa para combinar atualizacoes em 'struct lazy'
// - Defina o que eh a tag lazy (int)
// - Defina o elemento neutro (0)
// - Defina como combinar tags lazy em 'operator+=' (+=)
// - Defina como aplicar a tag lazy em um valor em 'apply_lazy(val, lz)' (+=)
//
// Defina um agregado associativo em 'struct data':
// - Defina o que serah mantido (soma/minimo/tamanho/...)
//   . Manter tamanho eh obrigatorio!
// - Defina o elemento neutro (0/INF/...)
// - Defina como agregar em 'operator+=' (+=/min=/...)
// - Defina como aplicar tag lazy no agregado em 'apply_lazy(lz)'
// - Se a operacao nao for comutativa:
//   . Defina como reverter um intervalo em reverse()
//
// 4. Operacoes em caminhos
// - path_query(v): retorna o agregado de w de v ate sua raiz
//   . Nessa ordem, para operacoes nao comutativas!
// - path_query(v, u): retorna o agregado de w de v ateh u (nao direcionado)
//   . Nessa ordem, para operacoes nao comutativas!
// - path_update(v, u, val): aplica lazy(val) em w de v ate u (nao direcionado)
//
// 5. Operacoes em sub-arvores
// - subtree_query(v, exclude_v): retorna o agregado de w na sub-arvore de v
//   . Se exclude_v, exclui v do agregado
//   . Ordem nao eh definida para operacoes nao comutativas!
// - subtree_update(v, val, exclude_v): aplica lazy(val) em w na sub-arvore de v
//   . Se exclude_v, exclui v da atualizacao
//
// Para a proxima operacao que combina agregados de filhos:
//
// Defina uma combinacao associativa e comutativa de filhos em 'data_child'
// - Defina o elemento neutro
// - Defina o valor de um filho, dado seu agregado (tamanho/tamanho^2/soma/...)
// - Defina como combinar valores de filhos (+=/min=/...)
//
// 6. Combinacao de dados dos filhos
// - combine_children(v): retorna a combinacao dos filhos de v
//   . Se voce definir data_child() = 1 e combinar com +=,
//     returna numero de filhos

template<typename T> struct lct {
	struct lazy {
		T val;

		lazy(T val_ = 0) : val(val_) {}
		lazy& operator +=(const lazy& lz) {
			val += lz.val;
			return *this;
		}
	};
	void apply_lazy(T& val, const lazy& lz) {
		val += lz.val;
	};
	struct data {
		T sum;
		int sz;

		data() : sum(0), sz(0) {}
		data(T val) : sum(val), sz(1) {}

		data& operator +=(const data& d) {
			sum += d.sum;
			sz += d.sz;
			return *this;
		}
		friend data operator +(data a, const data& b) { return a += b; }

		void apply_lazy(const lazy& lz) {
			if (sz == 0) return;
			sum += lz.val * sz;
		}
		void reverse() {}
	};
	struct data_child {
		int cnt;

		data_child() : cnt(0) {}
		data_child(data sub) { // 'sub' representa dado da sub-arvore
			cnt = 1; // para numero de filhos
		}
		data_child& operator +=(const data_child& d) {
			cnt += d.cnt;
			return *this;
		}
		friend data_child operator +(data_child a, const data_child& b) { return a += b; }
	};

	struct node {
		T val;
		int p, ch[4];
		data path, sub, all;
		data_child data_ch;
		lazy lz_path, lz_sub;
		bool rev, fake;

		node() : p(-1), path(), sub(), all(), data_ch(), lz_path(), lz_sub(), rev(0), fake(1) {
			memset(ch, -1, sizeof ch);
		}
		node(T val_) : node() {
			val = val_;
			path = all = data(val);
			data_ch = data_child(all);
			fake = false;
		}
	};

	vector<node> t;
	vector<int> fakes;
	int free_fake;

	lct(int n, vector<T> w = {}) : t(2*n), fakes(n), free_fake(n) {
		if (!w.size()) w = vector<T>(n, T());
		for (int i = 0; i < n; i++) t[i] = node(w[i]);
		iota(fakes.begin(), fakes.end(), n);
	}

	void prop_rev(int v) {
		if (v == -1) return;

		t[v].path.reverse();
		swap(t[v].ch[0], t[v].ch[1]);
		t[v].rev ^= 1;
	}
	void prop_path(int v, const lazy& lz) {
		if (v == -1 or t[v].fake) return;

		apply_lazy(t[v].val, lz);

		t[v].path.apply_lazy(lz);
		t[v].lz_path += lz;
		t[v].all = t[v].path + t[v].sub;
		t[v].data_ch = data_child(t[v].all);
	}
	void prop_sub(int v, const lazy& lz, bool virt) {
		if (v == -1) return;

		t[v].sub.apply_lazy(lz);
		t[v].lz_sub += lz;
		if (!t[v].fake and virt) prop_path(v, lz);
		else t[v].all = t[v].path + t[v].sub;
	}
	void prop(int v) { // lazy nao inclui o vertice
		if (v == -1) return;
		if (t[v].rev) {
			for (int i = 0; i < 2; i++) prop_rev(t[v].ch[i]);
			t[v].rev = false;
		}
		if (t[v].lz_path.val != lazy().val) {
			for (int i = 0; i < 2; i++) prop_path(t[v].ch[i], t[v].lz_path);
			t[v].lz_path = lazy();
		}
		if (t[v].lz_sub.val != lazy().val) {
			for (int i = 0; i < 4; i++) prop_sub(t[v].ch[i], t[v].lz_sub, i > 1);
			t[v].lz_sub = lazy();
		}
	}
	node get_ch(int v, int c) {
		return t[v].ch[c] == -1 ? node() : t[t[v].ch[c]];
	}
	void update(int v) {
		if (!t[v].fake) t[v].path = get_ch(v, 1).path + data(t[v].val) + get_ch(v, 0).path;
		t[v].sub = get_ch(v, 0).sub + get_ch(v, 1).sub + get_ch(v, 2).all + get_ch(v, 3).all;
		t[v].all = t[v].path + t[v].sub;

		if (t[v].fake) t[v].data_ch = get_ch(v, 2).data_ch + get_ch(v, 3).data_ch;
		else t[v].data_ch = data_child(t[v].all);
	}

	int dir(int v) {
		if (t[v].p == -1) return -1;
		for (int i = 0; i < 4; i++) if (t[t[v].p].ch[i] == v) return i;
		return -1;
	}
	bool is_root(int v) {
		if (t[v].p == -1) return true;
		return t[v].fake ? !t[t[v].p].fake : (dir(v)&2);
	}
	void rotate(int v) {
		int p = t[v].p, pp = t[p].p, dir_v = dir(v), dir_p = dir(p);

		attach(p, dir_v, t[v].ch[dir_v^1]);
		attach(v, dir_v^1, p);
		if (dir_p+1) attach(pp, dir_p, v);
		else t[v].p = pp;
	}
	void splay(int v) {
		prop(v);
		while (!is_root(v)) {
			int p = t[v].p, pp = t[p].p;
			if (pp+1) prop(pp);
			prop(p), prop(v);
			if (!is_root(p)) rotate(dir(v) == dir(p) ? p : v);
			rotate(v);
		}
	}
	void attach(int v, int c, int u) {
		t[v].ch[c] = u;
		if (u+1) t[u].p = v;
		update(v);
	}
	void add_virt_ch(int v, int u) {
		if (u == -1) return;
		for (int i = 2; i < 4; i++) if (t[v].ch[i] == -1) {
			attach(v, i, u);
			return;
		}
		int w = fakes[--free_fake];
		attach(w, 2, t[v].ch[2]);
		attach(w, 3, u), attach(v, 2, w);
	}
	void prop_path(int v) {
		if (t[v].fake) prop_path(t[v].p);
		prop(v);
	}
	void rem_virt_ch(int v) {
		int p = t[v].p;
		prop_path(p);
		if (t[p].fake) {
			int pp = t[p].p;
			attach(pp, dir(p), t[p].ch[dir(v)^1]);
			if (t[pp].fake) splay(pp);
			fakes[free_fake++] = p;
		} else attach(p, dir(v), -1);
		t[v].p = -1;
	}
	int real_par(int v) {
		v = t[v].p;
		if (!t[v].fake) return v;
		splay(v);
		return t[v].p;
	}
	int access(int v) { // retorna ultimo vertice acessado
		update(v);
		splay(v);
		add_virt_ch(v, t[v].ch[1]);
		attach(v, 1, -1);
		int w = v;
		while (t[v].p+1) {
			w = real_par(v);
			splay(w);

			rem_virt_ch(v);
			add_virt_ch(w, t[w].ch[1]);
			attach(w, 1, v);

			splay(v);
		}
		return w;
	}

	// consultas estruturais
	int find_root(int v) {
		access(v);
		while (t[v].ch[0]+1) v = t[v].ch[0], prop(v);
		return splay(v), v;
	}
	int lca(int v, int u) {
		int ret = (access(v), access(u));
		if (v != u and t[v].p == -1) return -1;
		return ret;
	}
	bool connected(int v, int u) {
		return lca(v, u) != -1;
	}
	int parent(int v, int k = 1) {
		access(v);
		if (k >= t[v].path.sz) return -1;

		while (true) {
			int sz_r = t[v].ch[1] == -1 ? 0 : t[t[v].ch[1]].path.sz;
			if (k < sz_r) v = t[v].ch[1], prop(v);
			else {
				k -= sz_r;
				if (k == 0) return splay(v), v;
				v = t[v].ch[0], prop(v);
				k--;
			}
		}
	}
	int depth(int v) {
		access(v);
		return t[v].path.sz - 1;
	}
	int dist(int v, int u) {
		return depth(v) + depth(u) - 2*depth(lca(v, u));
	}
	int subtree_size(int v) {
		access(v);
		return get_ch(v, 2).all.sz + get_ch(v, 3).all.sz + 1;
	}
	bool adjacent(int v, int u) {
		return connected(v, u) and dist(v, u) == 1;
	}

	// atualizacoes estruturais
	void evert(int v) { // rotaciona para que v seja a raiz
		access(v);
		prop_rev(v);
	}
	void link(int v, int u) { // adiciona aresta v -> u (pai de v eh u) - nao pode criar ciclo!
		evert(v), access(u);
		add_virt_ch(u, v);
	}
	void cut(int v) { // corta aresta de v para o pai
		access(v);
		if (t[v].ch[0]+1) t[t[v].ch[0]].p = -1;
		t[v].ch[0] = -1;
		update(v);
	}
	void cut(int v, int u) { // aresta {v, u} deve existir!
		cut(depth(v) > depth(u) ? v : u);
	}

	// operacao de vertice
	T& operator[](int v) { // w[v] (pode ser alterado)
		access(v);
		return t[v].val;
	}

	// operacoes de caminho - vertices devem estar no mesmo componente!
	data path_query(int v) { // de v para a raiz
		access(v);
		return t[v].path;
	}
	data path_query(int v, int u) { // de v para u
		int rt = find_root(v);
		evert(u), access(v);
		auto ret = t[v].path;
		evert(rt);
		return ret;
	}
	void path_update(int v, int u, T val) {
		int rt = find_root(v);
		evert(u), access(v);
		prop_path(v, lazy(val));
		evert(rt);
	}

	// operacoes de sub-arvore
	data subtree_query(int v, bool exclude_v = false) {
		access(v);
		data ret = get_ch(v, 2).all + get_ch(v, 3).all;
		if (!exclude_v) ret += data(t[v].val);
		return ret;
	}
	void subtree_update(int v, T val, bool exclude_v = false) {
		access(v);
		prop_sub(t[v].ch[2], lazy(val), true);
		prop_sub(t[v].ch[3], lazy(val), true);
		if (!exclude_v) apply_lazy(t[v].val, lazy(val));
	}

	// combinacao de dados das sub-arvores dos filhos
	data_child combine_children(int v) {
		access(v);
		return get_ch(v, 2).data_ch + get_ch(v, 3).data_ch;
	}
};
