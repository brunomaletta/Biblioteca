// Min queue - stack
//
// Tudo O(1) amortizado

template<class T> struct minstack {
	stack<pair<T, T>> s;

	void push(T x) {
		if (!s.size()) s.push({x, x});
		else s.emplace(x, std::min(s.top().second, x));
	}
	T top() { return s.top().first;	}
	T pop() {
		T ans = s.top().first;
		s.pop();
		return ans;
	}
	int size() { return s.size(); }
	T min() { return s.top().second; }
};

template<class T> struct minqueue {
	minstack<T> s1, s2;

	void push(T x) { s1.push(x); }
	void move() {
		if (s2.size()) return;
		while (s1.size()) {
			T x = s1.pop();
			s2.push(x);
		}
	}
	T front() { return move(), s2.top(); }
	T pop() { return move(), s2.pop(); }
	int size() { return s1.size()+s2.size(); }
	T min() {
		if (!s1.size()) return s2.min();
		else if (!s2.size()) return s1.min();
		return std::min(s1.min(), s2.min());
	}
};
