const int MAXVERT = 1000;
struct matching
{
	int PairL[MAXVERT];
	int PairR[MAXVERT];
	vector<int> G[MAXVERT];
	int szL, szR;
	matching(){}

	int used[MAXVERT*2];
	int _tm;

	void init(int _szL, int _szR)
	{
	    szL = _szL;
	    szR = _szR;
	    for (int i = 0; i < szL; ++i)
	    	G[i].clear();
		memset(PairL, 0xff, sizeof(PairL));
		memset(PairR, 0xff, sizeof(PairR));
		_tm = 0;
		memset(used, 0, sizeof(used));
	}
	void addEdge(int from, int to) 	// from - лева€ дол€, to - права€. 
									// ¬ершины нумеруютс€: 0..(szL-1) - лева€, szL..(szL+szR-1) - права€								
	{
		G[from].push_back(to - szL);
	}
	
	bool dfs(int frm)
	{
		if (used[frm] == _tm)
		{
			return false;
		}
		used[frm] = _tm;
		for (int i = 0; i < G[frm].size(); ++i)
		{
			int nxt = G[frm][i];
			used[nxt + szL] = _tm;
			if (PairR[nxt] == -1 || dfs(PairR[nxt]))
			{
				PairR[nxt] = frm;
				return true;
			}
		}
		return false;
	}
	
	int buildMatching()
	{
		int ans = 0;
		for (int i = 0; i < szL; ++i)
		{
			++_tm;
			if (dfs(i))
				++ans;
		}
		for (int i = 0; i < szR; ++i)
		{
			if (PairR[i] != -1)
			{
				int v = PairR[i];
				PairL[v] = i + szL;
			}
		}
		return ans;
	}
	int getPair(int v)
	{
		if (v < szL) return PairL[v];
		else return PairR[v - szL];
	}
	vector<int> getIndep()
	{
		++_tm;
		for (int i = 0; i < szL; ++i)
		{
			if (PairL[i] == -1)
			{
				dfs(i);
			}
		}
		vector<int> ans;
		for (int i = 0; i < szL; ++i)
		{
			if (used[i] != _tm)
			{
				ans.push_back(i);
			}
		}
		for (int i = szL; i < szL + szR; ++i)
		{
			if (used[i] == _tm)
			{
				ans.push_back(i);
			}
		}
		return ans;
	}
};