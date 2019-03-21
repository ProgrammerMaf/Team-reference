char s[1001000];
vector <pair <int, int> > ::iterator it;
struct x
{
	vector <pair <int, int> > P;
	int end;
	int back;
	int exist (char c)
	{
		vector <pair <int, int> > ::iterator i;
		for (i = P.begin(); i != P.end(); ++i)
		{
			if (i->first == c)
			{
				return i->second;
			}
		}
		return -1;
	}
	void add (char c, int n)
	{
		P.push_back(make_pair(c, n));
	}
	x()
	{
		end = -1;
	}
} A[100100];
int cnt = 1;
int main()
{
	int k;
	scanf ("%d", &k);
	gets(s);
	for (int i = 0; i < k; ++i)
	{
		__int64 c;
		gets (s);
		int n = 0;
		int l;
		for (l = 0; s[l]; ++l)
		{
			int t = A[n].exist(s[l]);
			if (t == -1)
			{
				A[n].add (s[l], cnt);
				n = cnt++;
			}
			else
			{
				n = t;
			}
		}
		A[n].end = l;
	}
	A[0].back = 0;
	queue <int> Q;
	for (int i = 0; i < 256; ++i)
	{
		int t = A[0].exist (i);
		if (t >= 0)
		{
			A[t].back = 0;
			if (t != 0)
				Q.push (t);
		}
	}
	while (!Q.empty())
	{
		int t = Q.front();
		Q.pop();
		for (it = A[t].P.begin(); it != A[t].P.end(); ++it)
		{
			Q.push (it -> second);
			int x = A[t].back;
			while (x != 0 && A[x].exist(it->first) == -1) x = A[x].back;
			int a = A[x].exist(it->first);
			if (a != -1)
			{
				A[it->second].back = a;
			}
			else
			{
				A[it->second].back = 0;
			}
			if (A[it->second].end < A[A[it->second].back].end)
			{
				A[it->second].end = A[A[it->second].back].end;
			}
		}
	}
}
