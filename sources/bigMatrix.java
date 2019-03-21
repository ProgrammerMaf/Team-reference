	public class matrix
	{
		BigInteger M[][];
		final static int size = 2;
		matrix()
		{
			M = new BigInteger[size][];
			for (int i = 0; i < size; ++i)
			{
				M[i] = new BigInteger[size];
			}
		}
		matrix mult(matrix b)
		{
			matrix result = new matrix();
			matrix a = this;
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					result.M[i][j] = BigInteger.ZERO;
					for (int k = 0; k < size; ++k)
					{
						result.M[i][j] = result.M[i][j].add 
										(
												a.M[i][k].multiply(b.M[k][j])
										);
					}
				}
			}
			return result;
		}
		matrix copy()
		{
			matrix ans = new matrix();
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					ans.M[i][j] = M[i][j];
				}
			}
			return ans;
		}
		matrix qpow(int n)
		{
			matrix a = copy();
			matrix ans = new matrix();
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					if (i == j)
					{
						ans.M[i][j] = BigInteger.ONE;
					}
					else
					{
						ans.M[i][j] = BigInteger.ZERO;
					}
				}
			}
			for (int step = 0; (1 << step) <= n; ++step)
			{
				if ((n & (1 << step)) != 0)
				{
					ans = ans.mult (a);
				}
				a = a.mult(a);
			}
			return ans;
		}
	}