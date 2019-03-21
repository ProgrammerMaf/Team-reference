void calcZ(int a, int b, int *z)
{
	z[a] = 0;
	int l = a, r = a;
	for (int i = a + 1; i <= b; i++)
	{
		z[i] = 0;
		if (i < r)
			z[i] = min(r - i, z[a + i - l]);
		while (i + z[i] <= b && str[i + z[i]] == str[a + z[i]])
			z[i]++;
		if (i + z[i] > r)
		{
			l = i;
			r = i + z[i];
		}
	}
}

void foundSquares(int l, int centerL, int centerR)
{
	if (centerL <= centerR)
		//PROCESS SQUARES
}

void findSquares(int l, int r)
{
	if (r - l + 1 <= 1)
		return;
	int mid = (l + r) / 2;
	findSquares(l, mid);
	findSquares(mid + 1, r);

	for (int it = 0; it < 2; it++)
	{
		calcZ(mid + 1, r, prefix);
		reverse(str + l, str + mid + 1);
		reverse(str + mid + 1, str + r + 1);
		calcZ(l, r, suffix);
		reverse(str + l, str + mid + 1);
		reverse(str + mid + 1, str + r + 1);
		reverse(suffix + mid + 1, suffix + r + 1);
		for (int i = mid + 1; i <= r; i++)
		{
			int suffBound = i - suffix[i] + 1;
			if (suffBound == mid + 1)
				suffBound += it;
			int prefBound = min(i, mid + 1 + (i == r ? 0 : prefix[i + 1]));

			if (it == 0)
				foundSquares(i - mid, suffBound, prefBound);
			else
				foundSquares(i - mid, l + (r - prefBound) + 1, l + (r - suffBound) + 1);
		}
		reverse(str + l, str + r + 1);
		mid = (l + r - 1) / 2;
	}
	return;
}
