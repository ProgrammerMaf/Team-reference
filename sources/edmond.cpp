#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
struct guard
{
	vector<int> E;
	int pair;
	int base;
	bool b;
	int p;
	guard()
	{
		pair = -1;
	}
} G[250];
int N;
bool used[250], blossom[250];
int lca(int a, int b)
{
	for (int i = 0; i < N; ++i)
	{
		used[i] = false;
	}
	while(1)
	{
		a = G[a].base;
		used[a] = true;
		if (G[a].pair == -1) break;
		a = G[G[a].pair].p;
	}
	while (1)
	{
		b = G[b].base;
		if (used[b]) return b;
		b = G[G[b].pair].p;
	}
}
void mark_path(int v, int b, int child)
{
	while (G[v].base != b)
	{
		blossom[G[v].base] = true;
		blossom[G[G[v].pair].base] = true;
		G[v].p = child;
		child = G[v].pair;
		v = G[G[v].pair].p;
	}
}
int edmond(int root)
{
	for (int i = 0; i < N; ++i)
	{
		G[i].base = i;
		G[i].p = -1;
		G[i].b = false;
	}
	G[root].b = true;
	queue<int> Q;
	Q.push(root);
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int k = 0; k < (int) G[v].E.size(); ++k)
		{
			int to = G[v].E[k];
			if (G[v].base == G[to].base) continue;
			if (to == root || (G[to].pair != -1 && G[G[to].pair].p != -1) )
			{
				int base = lca(v, to);
				for (int i = 0; i < N; ++i)
				{
					blossom[i] = false;
				}
				mark_path(v, base, to);
				mark_path(to, base, v);
				for (int i = 0; i < N; ++i)
				{
					if (blossom[G[i].base])
					{
						G[i].base = base;
						if (!G[i].b)
						{
							G[i].b = true;
							Q.push(i);
						}
					}
				}
			}
			else if (G[to].p == -1)
			{
				G[to].p = v;
				if (G[to].pair == -1)
				{
					return to;
				}
				to = G[to].pair;
				G[to].b = true;
				Q.push(to);
			}
		}
	}
	return -1;
}
bool find(int root)
{
	int v = edmond(root);
	if (root == -1)
	{
		return false;
	}
	while (v != -1) 
	{
		int pv = G[v].p,  ppv = G[pv].pair;
		G[v].pair = pv,  G[pv].pair = v;
		v = ppv;
	}
	return true;
}
int main()
{
#ifdef _DEBUG
	freopen("test.txt", "r", stdin);
#endif
	int a, b;
	scanf ("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		G[i].pair = -1;
	}
	while (scanf("%d%d", &a, &b) > 0)
	{
		--a;
		--b;
		G[a].E.push_back(b);
		G[b].E.push_back(a);
	}
	int cnt = 0;
	for (int i = 0; i < N; ++i)
	{
		if (G[i].pair == -1)
		{
			find(i);
		}
	}
	for (int i = 0; i < N; ++i)
	{
		if (G[i].pair != -1)
		{
			++cnt;
		}
	}
	printf ("%d\n", cnt);
	for (int i = 0; i < N; ++i)
	{
		if (G[i].pair > i)
		{
			printf ("%d %d\n", i + 1, G[i].pair + 1);
		}
	}
	return 0;
}
