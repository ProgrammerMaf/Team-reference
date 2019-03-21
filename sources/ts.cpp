int p[100500];
bool use[100500];
int tin[100500];
int up[100500];
vector <int> v[100500], w[100500];
bool ts[100500];
int cnt[100500];

int get(int i);
void Union(int i, int j);

int T;

void dfs(int u, int num)
{
	use[u] = true;
	tin[u] = T++;
	up[u] = tin[u];
	int ch = 0;
	for (int i = 0; i < (int)v[u].size(); ++i)
		if (!use[v[u][i]])
		{
			ch++;
			dfs(v[u][i], w[u][i]);
			up[u] = min(up[u], up[v[u][i]]);
			if (up[v[u][i]] == tin[u])
			{
				ts[u] = true;
			}
			else
			{
				Union(w[u][i], num);
			}
		}
		else if (tin[v[u][i]] < tin[u])
		{
			up[u] = min(up[u], tin[v[u][i]]);
			Union(w[u][i], num);
		}
	if (u == 0)
	{
		if (ch > 1)
			ts[u] = true;
		else
			ts[u] = false;
	}
}
