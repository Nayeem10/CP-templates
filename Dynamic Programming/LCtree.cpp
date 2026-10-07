template<typename DT>
struct Line{
	DT m, c;
	DT operator()(DT x) const { return m * x + c; }
};

template<typename DT, typename COMP = greater<DT>>
struct node{
	CMP comp; // comp(a, b) --> a COMP b
	Line<DT> line;
	node *left = nullptr, *right = nullptr;
	node(Line<DT> line) : line(line) {}

	void add_segment(LL l, LL r, LL L, LL R, Line<DT> nw){
		LL m = l + 1 == r ? l : (l + r) / 2;
		if(L >= l and R <= r){
			bool ism = comp(nw(m), line(m));
			bool isl = comp(nw(l), line(l));
			if(ism) swap(line, nw);
			if(l == r) return;
			if(ism ^ isl){
				if(left == nullptr) left = new node(nw);
				else left->add_segment(l, m, L, R, nw);
			}else{
				if(right == nullptr) right = new node(nw);
				else right->add_segment(m + 1, r, L, R, nw);
			}
			return;
		}
		if(max(l, L) <= min(m, R)){
			if(left == nullptr) left = new node(line(0, INF - 2 * INF * comp(0, 1)));
			left->add_segment(l, m, L, R, line);
		}else{
			if(right == nullptr) right = new node(line(0, INF - 2 * INF * comp(0, 1)));
			right->add_segment(m + 1, r, L, R, line);
		}
	}
	DT query(LL l, LL r, LL L, LL R, LL x){
		if (l > r || r < L || l > R) return -INF;

	    DT ans = line(x);
	    if (l == r) return ans;

	    LL m = (l + r) >> 1;

	    if (x <= m && left) ans = min(ans, left->query_segment(x, l, m, L, R));
	    if (x > m && right) ans = min(ans, right->query_segment(x, m + 1, r, L, R));

	    return ans;
	}
}

struct LiChaoTree {
  LL L, R;
  node* root;
  LiChaoTree(LL L, LL R) : L(L), R(R) { root = new node({0, inf}); }
  void add_segment(Line line, LL l, LL r) {
    root->add_segment(line, L, R, l, r);
  }
  double query(LL x) { return root->query_segment(x, L, R, L, R); }
};