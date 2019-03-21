int[] buildLCP(str: string, suf: int[])
	int n = str.length
	int[len] lcp
	int[len] pos
for i = 0 to n - 1
	pos[suf[i]] = i
	int k = 0
	for i = 0 to n - 1
		if k > 0
			k--
		if pos[i] == n - 1
			lcp[n - 1] = -1
			k = 0
		else
			int j = suf[pos[i] + 1]
		while max(i + k, j + k) < n and str[i + k] == str[j + k]
			k++
		lcp[pos[i]] = k
return lcp
// from neerc wiki, not tested, but copied many times