const int SAINF = 1e9;
const int MAXLEN = 2e6;
const int ALF = 300;
const int TREESIZE = 1<<21;
struct IntervalTree
{
	int tree[TREESIZE * 2];
	IntervalTree()
	{
		for (int i = 0; i < TREESIZE * 2; ++i)
		{
			tree[i] = SAINF;
		}
	}
	void set(int pos, int value)
	{
		pos += TREESIZE;
		tree[pos] = value;
		pos /= 2;
		while (pos > 0)
		{
			tree[pos] = min(tree[pos * 2], tree[pos * 2 + 1]);
			pos /= 2;
		}
	}
	int _min(int l, int r)
	{
		if (r < l) swap(l, r);
		--r;
		l += TREESIZE;
		r += TREESIZE;
		int ans = min(tree[l], tree[r]);
		while (l/2 != r/2)
		{
			if ((l&1) == 0) ans = min(ans, tree[l+1]);
			if ((r&1) == 1) ans = min(ans, tree[r-1]);
			l /= 2;
			r /= 2;
		}
		return ans;
	}
};

struct suffixArray
{
	IntervalTree I;
	int len;
	char str[MAXLEN];
	int cnt[MAXLEN];
	int buff1[MAXLEN], buff2[MAXLEN], p[MAXLEN], pn[MAXLEN], lcp[MAXLEN], rpos[MAXLEN];
	int *cl, *cln;
	int classes, nclasses;
	void init(char *s, int _len)
	{
		cl = buff1;
		cln = buff2;
		for (int i = 0; i < _len; ++i)
			str[i] = s[i];
		len = _len;
	}
	
	void build()
	{
		for (int i = 0; i < len; ++i)
		{
			++cnt[str[i]];
			lcp[i] = len;
		}
		for (int i = 0; i < ALF; ++i)
		{
			cnt[i + 1] += cnt[i];
		}
		for (int i = 0; i < len; ++i)
		{
			p[--cnt[str[i]]] = i;
		}
		classes = 1;
		cl[p[0]] = 0;
		for (int i = 1; i < len; ++i)
		{
			if (str[p[i]] != str[p[i - 1]])
			{
				++classes;
				lcp[i - 1] = 0;
				I.set(i - 1, 0);
			}
			cl[p[i]] = classes - 1;
		}
		memset(cnt, 0, classes * sizeof(int));
		for (int i = 0; i < len; ++i)
		{
			++cnt[cl[i]];
		}
		for (int i = 1; i < classes; ++i)
			cnt[i] += cnt[i - 1];
		for (int h = 1; h < len; h *= 2)
		{
			for (int i = 0; i < len; ++i)
			{
				rpos[cl[p[i]]] = i;
				pn[i] = p[i] - h;
				if (pn[i] < 0) pn[i] += len;
			}
			for (int i = len - 1; i >= 0; --i)
			{
				p[--cnt[cl[pn[i]]]] = pn[i];
			}
			classes = 1;
			cln[p[0]] = 0;
			for (int i = 0; i < len - 1; ++i)
			{
				int a = p[i], b = p[i + 1];
				int aa = a + h, bb = b + h;
				if (aa >= len) aa -= len;
				if (bb >= len) bb -= len;
				if (cl[a] != cl[b] || cl[aa] != cl[bb])
				{
					cnt[classes - 1] = i + 1;
					++classes;
				}
				cln[b] = classes - 1;
				if (cl[a] == cl[b] && cl[aa] != cl[bb])
				{
					lcp[i] = h + I._min(rpos[cl[aa]], rpos[cl[bb]]);
					I.set(i, lcp[i]);
				}
			}
			cnt[classes - 1] = len;
			if (classes == len)
				break;
			swap(cl, cln);
		}
		for (int i = 0; i < len; ++i)
		{
			pn[p[i]] = i;
		}
	}
};
