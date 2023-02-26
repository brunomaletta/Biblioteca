// Min queue - deque
//
// Tudo O(1) amortizado

template<class T> struct minqueue {
	deque<pair<T, int>> q;

	void push(T x) {
		int ct = 1;
		while (q.size() and x < q.front().first)
			ct += q.front().second, q.pop_front();
		q.emplace_front(x, ct);
	}
	void pop() {
		if (q.back().second > 1) q.back().second--;
		else q.pop_back();
	}
	T min() { return q.back().first; }
};
