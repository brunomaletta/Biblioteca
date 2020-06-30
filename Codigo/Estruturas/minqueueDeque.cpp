// Min queue - deque
//
// Tudo O(1) amortizado

template<class T> struct minqueue {
	deque<pair<T, int> > q;

	void push(T x) {
		int ct = 1;
		while (q.size() and x < q.front().f)
			ct += q.front().s, q.pop_front();
		q.push_front({x, ct});
	}
	void pop() {
		if (q.back().s > 1) q.back().s--;
		else q.pop_back();
	}
	T min() { return q.back().f; }
};
