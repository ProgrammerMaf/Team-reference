const int MAXLEN = 10000;
int getPref(char * s, int* p, int pos, char c)
{
	if (pos == 0) return 0;
	int j = p[pos-1];
	while (j > 0 && c != s[j])
		j = p[j-1];
	if (c == s[j]) ++j;
	return j;
}
int p[MAXLEN];
void buildPref(char *s)
{
	for (int i = 0; s[i]; ++i)
	{
		p[i] = getPref(s, p, i, s[i]);
	}
}
