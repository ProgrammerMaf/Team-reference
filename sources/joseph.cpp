int survive = 0;
for (int i = 2; i <= n; i++)
	survive = (survive + k) % i;
printf("%d\n", survive + 1);
