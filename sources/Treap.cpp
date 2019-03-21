const int FOREST = (int)1e7;

struct Tree
{
	static Tree forest[FOREST];
	static int fl;
	char val;
	int sz;
	bool push;
	Tree *l, *r;
	Tree() : val(0), sz(1), push(false), l(NULL), r(NULL) {}
	static Tree *make(char val = 0)
	{
		Tree *res = &Tree::forest[fl++];
		res->val = val;
		res->sz = 1;
		res->push = false;
		res->l = NULL;
		res->r = NULL;
		return res;
	}
	static Tree *make(Tree const *orig)
	{
		Tree *res = &Tree::forest[fl++];
		res->val = orig->val;
		res->sz = orig->sz;
		res->push = orig->push;
		res->l = orig->l;
		res->r = orig->r;
		return res;
	}
	int get_key() const
	{
		return (push ? r : l) == NULL ? 0 : (push ? r : l)->sz;
	}
	Tree *push_me() const
	{
		Tree *res = Tree::make(this);
		res->push = false;
		if (push)
		{
			if (l != NULL)
			{
				res->l = Tree::make(l);
				res->l->push ^= push;
			}
			if (r != NULL)
			{
				res->r = Tree::make(r);
				res->r->push ^= push;
			}
			swap(res->l, res->r);
		}
		return res;
	}
	Tree *reverse() const
	{
		Tree *res = Tree::make(this);
		res->push ^= 1;
		return res;
	}
	void recalc_sz()
	{
		sz = 1 + (l == NULL ? 0 : l->sz) + (r == NULL ? 0 : r->sz);
	}
};

Tree Tree::forest[FOREST];
int Tree::fl = 0;

pair<Tree*, Tree*> split(Tree *tree, int key)
{
	if (tree == NULL)
		return { NULL, NULL };
	Tree *pushed = tree->push_me();
	if (key > pushed->get_key())
	{
		if (pushed->r == NULL)
			return { pushed, NULL };
		Tree *rl, *rr;
		tie(rl, rr) = split(pushed->r, key - pushed->get_key() - 1);
		pushed->r = rl;
		pushed->recalc_sz();
		return { pushed, rr };
	}
	else
	{
		if (pushed->l == NULL)
			return { NULL, pushed };
		Tree *ll, *lr;
		tie(ll, lr) = split(pushed->l, key);
		pushed->l = lr;
		pushed->recalc_sz();
		return { ll, pushed };
	}
}

Tree *merge(Tree *a, Tree *b)
{
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
	a = a->push_me();
	b = b->push_me();
	if ((int)rng() % (a->sz + b->sz) < a->sz)
	{
		a->r = merge(a->r, b);
		a->recalc_sz();
		return a;
	}
	else
	{
		b->l = merge(a, b->l);
		b->recalc_sz();
		return b;
	}
}
