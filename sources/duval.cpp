#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

const int LEN = (int)1e6 + 10;
int realLen;
int ans;
char str[LEN];

//BLOCK [a..b)
void LyndonBlock(int a, int b) { /* Some stuff */ }

void lyndon(int len)
{
	int start = 0;
	int p = 1;
	for (int i = start; i < len; i++)
	{
		if (str[i] != str[i - p])
		{
			if (str[i] < str[i - p])
			{
				for (int s = start; s + p <= i; s += p)
					LyndonBlock(s, s + p);
				int rem = (i - start) % p;
				start = i - rem;
				p = 1;
				i = start;
			}
			else
				p = i - start + 1;
		}
	}
	//Tail blocks
	for (int s = start; s < len; s += p)
		LyndonBlock(s, min(len, s + p));
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf(" %s", str);
		int len = strlen(str);
		realLen = len;
		memcpy(str + len, str, len);
		len *= 2;
		str[len] = 0;
		ans = 1;
		lyndon(len);
		printf("%d\n", ans);

	}
	return 0;
}
