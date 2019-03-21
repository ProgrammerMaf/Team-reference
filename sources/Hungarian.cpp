#include <stdio.h>
#include <queue>
using namespace std;
int Ans[300][300], M[300][300], T[300];
int pairY[300];
int BX[300], BY[300];
int prevX[300], prevY[300];
int time = 0;
int N;
int A[300], B[300];
bool find (int v)
{
	++time;
	queue<int> Q;
	BX[v] = time;
	Q.push (v);
	int last = -1;
	while (!Q.empty() && last == -1)
	{
		int t = Q.front();
		Q.pop();
		for (int i = 0; i < N && last == -1; ++i)
		{
			if (BY[i] == time)
			{
				continue;
			}
			if (M[t][i] == 0)
			{
				if (pairY[i] == -1)
				{
					pairY[i] = t;
					last = t;
				}
				else
				{
					Q.push(pairY[i]);
					BX[pairY[i]] = time;
					BY[i] = time;
					prevX[pairY[i]] = i;
					prevY[i] = t;
				}
			}
		}
	}
	if (last != -1)
	{
		while (last != v)
		{
			pairY[prevX[last]] = prevY[prevX[last]];
			last = prevY[prevX[last]];
		}
		return true;
	}
	int mn = 1e9;
	for (int i = 0; i < N; ++i)
	{
		if (BX[i] != time)
		{
			continue;
		}
		for (int j = 0; j < N; ++j)
		{
			if (BY[j] != time && M[i][j] < mn)
			{
				mn = M[i][j];
			}
		}
	}
	for (int i = 0; i < N; ++i)
	{
		if (BX[i] != time)
		{
			continue;
		}
		for (int j = 0; j < N; ++j)
		{
			if (BY[j] != time)
			{
				M[i][j] -= mn;
			}
		}
		A[i] += mn;
	}
	for (int i = 0; i < N; ++i)
	{
		if (BX[i] == time)
		{
			continue;
		}
		for (int j = 0; j < N; ++j)
		{
			if (BY[j] == time)
			{
				M[i][j] += mn;
			}
		}
	}
	for (int j = 0; j < N; ++j)
	{
		if (BY[j] == time)
			B[j] -= mn;
	}
	return false;
}
int main()
{
#ifdef _DEBUG
	freopen("test.txt", "r", stdin);
#endif
	scanf ("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		pairY[i] = -1;
		int sum = 0;
		for (int j = 0; j < N; ++j)
		{
			scanf ("%d", &T[j]);
			sum += T[j];
		}
		int mn = sum;
		for (int j = 0; j < N; ++j)
		{
			Ans[i][j] = M[i][j] = -T[j];
			if (M[i][j] < mn)
			{
				mn = M[i][j];
			}
		}
		for (int j = 0; j < N; ++j)
		{
			M[i][j] -= mn;
		}
		A[i] += mn;
	}
	for (int i = 0; i < N; ++i)
	{
		int mn = 1e9;
		for (int j = 0; j < N; ++j)
		{
			if (M[j][i] < mn)
			{
				mn = M[j][i];
			}
		}
		for (int j = 0; j < N; ++j)
		{
			M[j][i] -= mn;
		}
		B[i] += mn;
	}
	for (int i = 0; i < N; ++i)
	{
		while (!find (i));
	}

	int mx = 0;
	for (int i = 0; i < N; ++i)
	{
		mx = max(B[i], mx);
	}
	for (int i = 0; i < N; ++i)
	{
		printf("%d ", -A[i]-mx);
	}
	puts("");
	for (int i = 0; i < N; ++i)
	{
		printf("%d ", -B[i]+mx);
	}	
	return 0;
}