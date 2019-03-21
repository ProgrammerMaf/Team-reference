public static BigInteger two = BigInteger.valueOf(2);
public static TreeMap<BigInteger, Integer> factors;	
public static int IT = 100000;
public static void addFactor(BigInteger x)
{
	if (!factors.containsKey(x))
		factors.put(x, 1);
	else
		factors.put(x, factors.get(x) + 1);
}
public static BigInteger f(BigInteger x, BigInteger c, BigInteger a)
{
	return x.multiply(x).add(c).remainder(a);
}
public static void factorize(BigInteger a)
{
	if (a.isProbablePrime(20))
	{
		addFactor(a);
		return;
	}
	if (a.equals(BigInteger.ONE))
		return;
	BigInteger t = two;
	BigInteger h = two;
	BigInteger c = BigInteger.ONE;
	for (int i = 0; i < IT; i++)
	{
		t = f(t, c, a);
		h = f(f(h, c, a), c, a);
		BigInteger delta = (t.compareTo(h) == 1 ? t.subtract(h) : h.subtract(t));
		BigInteger g = a.gcd(delta);
		if (g.equals(BigInteger.ONE))
			continue;
		if (g.compareTo(a) == -1)
		{
			factorize(g);
			factorize(a.divide(g));
			return;
		}
		t = two;
		h = two;
		c = c.add(BigInteger.ONE);
	}
	addFactor(a);
}
