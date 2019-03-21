const int A = 26;
const int SZ = (int)2e5 + 10;

struct Node {
	int go[A];
	int link;
	int len;
	Node () {
		memset(go, -1, sizeof(go));
		link = -1;
		len = 0;
	}
	int get(int c) {
		return go[c];
	}
	void set(int c, int to) {
		go[c] = to;
	}
};

//CHECK SIZE. AUTOMATON CONTAINS UP TO 2N + 1 VERTICES
Node tree[SZ];
int term[SZ];
int mv = 1;
int last = 0;

void addChar(int c) {
	int v = mv++, p;
	for (p = last; p != -1 && tree[p].get(c) == -1; p = tree[p].link)
		tree[p].set(c, v);
	tree[v].len = tree[last].len + 1;
	if (p != -1) {
		int q = tree[p].get(c);
		if (tree[p].len + 1 == tree[q].len)
			tree[v].link = q;
		else {
			int clone = mv++;
			tree[clone] = tree[q];
			tree[clone].len = tree[p].len + 1;
			tree[clone].link = tree[q].link;
			tree[q].link = clone;
			tree[v].link = clone;
			for (; p != -1 && tree[p].get(c) == q; p = tree[p].link)
				tree[p].set(c, clone);
		}
	}
	else
		tree[v].link = 0;
	last = v;
}

void markTerm() {
	for (int v = last; v != -1; v = tree[v].link)
		term[v] = 1;
}
