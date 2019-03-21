#include <cstdio>
#include <vector>
using namespace std;



const int MAXVERT = 300;
const int QSIZE = 1<<9;
const int QMOD = QSIZE - 1;


struct edge
{
	int to, F, cost;
	int finit;
	edge(){}
	edge(int _to, int _F, int _cost)
	{
		to = _to;
		F = _F;
		finit = F;
		cost = _cost;
	}
};
struct minCost
{
	vector<edge> G[MAXVERT];
	vector<int> R[MAXVERT];
	int Q[QSIZE];
	int prv[MAXVERT];
	int E[MAXVERT];
	bool inQueue[MAXVERT];
	int dist[MAXVERT];
	int cost;
	int flow;
	int N;
	minCost()
	{
		init();
	}
	void init()
	{
		cost = 0;
		flow = 0;
		N = 0;
		for (int i = 0; i < MAXVERT; ++i)
		{
			G[i].clear();
			R[i].clear();
		}
	}
	void addEdge(int from, int to, int capacity, int cost)
	{
		R[from].push_back(G[to].size());
		R[to].push_back(G[from].size());
		G[from].push_back(edge(to, capacity, cost));
		G[to].push_back(edge(from, 0, -cost));
	}
	bool findFlow(int s, int t, bool mnCost)
	{
		int l = 0, r = 1;
		int inf = 0x7f7f7f7f;
		memset(dist, 0x7f, sizeof(dist));
		memset(inQueue, false, sizeof(inQueue));
		dist[s] = 0;
		Q[0] = s;
		inQueue[s] = true;
		while (l < r)
		{
			int v = Q[l&QMOD];
			++l;
			inQueue[v] = false;
			for (int i = 0; i < G[v].size(); ++i)
			{
				if (G[v][i].F <= 0) continue;
				int nxt = G[v][i].to;
				int c = G[v][i].cost;
				if (dist[nxt] > dist[v] + c)
				{
					dist[nxt] = dist[v] + c;
					prv[nxt] = v;
					E[nxt] = i;
					if (!inQueue[nxt])
					{
						inQueue[nxt] = true;
						Q[r&QMOD] = nxt;
						++r;
					}
				}
			}
		}
		if (dist[t] == inf) return false;
		if (mnCost && dist[t] > 0) return false;
		cost += dist[t];
		++flow;
		int cur = t;
		while (cur != s)
		{
			int a = prv[cur];
			int b = cur;
			int e = E[cur];
			int re = R[a][e];
			--G[a][e].F;
			++G[b][re].F;
			cur = a;
		}
		return true;
	}
	void findMaxFlow(int s, int t)
	{
		while(findFlow(s, t, false));
	}
	void findMinCost(int s, int t)
	{
		while(findFlow(s, t, true));
	}
};