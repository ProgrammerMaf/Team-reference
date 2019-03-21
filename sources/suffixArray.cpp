const int MAXLEN = 2e6;
const int ALF = 200;
struct suffix {
	char str[MAXLEN];
	int cnt[MAXLEN];
	int p[MAXLEN], pn[MAXLEN];
	int *cl, *cln;
	int b1[MAXLEN], b2[MAXLEN];
	int lcp[MAXLEN];
	int len;

	void init(char *s, int _len) {
		cl = b1;
		cln = b2;
		len = _len;
		for (int i = 0; i < _len; ++i)
		{
			str[i] = s[i];
		}
	}

	void build() {
		for (int i = 0; i < len; ++i)
		{
			++cnt[str[i]];
		}
		for (int i = 1; i < ALF; ++i)
		{
			cnt[i] += cnt[i - 1];
		}
		for (int i = 0; i < len; ++i)
		{
			p[--cnt[str[i]]] = i;
		}
		int classes = 1;
		cl[p[0]] = 0;
		for (int i = 1; i < len; ++i)
		{
			if (str[p[i]] != str[p[i - 1]])
			{
				++classes;
			}
			cl[p[i]] = classes - 1;
		}
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < len; ++i)
		{
			++cnt[cl[i]];
		}
		for (int i = 1; i < classes; ++i)
		{
			cnt[i] += cnt[i - 1];
		}
		for (int l = 1; l <= len; l *= 2)
		{
			for (int i = 0; i < len; ++i)
			{
				pn[i] = p[i] - l;
				if (pn[i] < 0) pn[i] += len;
			}
			for (int i = len - 1; i >= 0; --i)
			{
				p[--cnt[cl[pn[i]]]] = pn[i];
			}
			classes = 1;
			cln[p[0]] = 0;
			for (int i = 1; i < len ; ++i)
			{
				int a = p[i], b = p[i - 1];
				int aa = a + l, bb = b + l;
				if (aa >= len) aa -= len;
				if (bb >= len) bb -= len;
				if (cl[a] != cl[b] || cl[aa] != cl[bb])
				{
					cnt[classes - 1] = i;
					++classes;
				}
				cln[a] = classes - 1;
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
		int lc = 0;
		for (int i = 0; i < len - 1; ++i)
		{
			int pos = pn[i];
			if (pos + 1 < len && i + lc < len && p[pos + 1] + lc < len)
				while (str[i + lc] == str[p[pos + 1] + lc])
					++lc;
			lcp[pos] = lc;
			if (lc) --lc;
		}
	}
};