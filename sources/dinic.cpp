
const int inf = 0x3f3f3f3f;

struct edge
{
	int ver, cap, flow, op;
	edge(){}
	edge(int v, int c, int o)
	{
		ver = v;
		cap = c;
		flow = 0;
		op = o;
	}
};

const int N = 10500;

int d[N], q[N];
vector <edge> v[N];
int ptr[N];
int n;
int s, t;

void add_edge(int from, int to, int cap)
{
	v[from].push_back(edge(to, cap, v[to].size()));
	v[to].push_back(edge(from, cap, v[from].size() - 1));
}

int T;

bool bfs()
{
	memset(d, 0x3f, sizeof(d));
	int left = 0, right = 1;
	q[0] = s;
	d[s] = 0;
	while (left < right)
	{
		int ver = q[left++];
		for (int i = 0; i < v[ver].size(); ++i)
			if (v[ver][i].cap - v[ver][i].flow >= T && d[v[ver][i].ver] == inf)
			{
				d[v[ver][i].ver] = d[ver] + 1;
				q[right++] = v[ver][i].ver;
			}
	}
	return d[t] != inf;
}

int xmin(int x, int y)
{
	return x < y ? x : y;
}

int dfs(int u, int flow)
{
	if (flow == 0 || u == t)
		return flow;
	int f = 0;
	int i = 0;
	for (i = ptr[u]; i < v[u].size(); ++i)
		if (d[v[u][i].ver] == d[u] + 1 && v[u][i].cap - v[u][i].flow >= T)
		{
			int cflow = dfs(v[u][i].ver, xmin(flow - f, v[u][i].cap - v[u][i].flow));
			if (cflow > 0)
			{
				f += cflow;
				v[u][i].flow += cflow;
				v[v[u][i].ver][v[u][i].op].flow -= cflow;
			}
			if (flow - f == 0)
				break;
		}
	ptr[u] = i;
	return f;
}

void find_flow()
{
	int i;
	for (T = (1 << 30); T > 0; T /= 2)
	{
		while (1)
		{
			if (!bfs())
				break;
			for (i = 0; i < n; ++i)
				ptr[i] = 0;
			dfs(s, inf);
		}
	}
}
