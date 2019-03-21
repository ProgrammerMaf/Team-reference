struct point
{
	ll x, y;
	void scan()
	{
		scanf("%lld%lld", &x, &y);
	}
	point(){}
	point(ll _x, ll _y)
	{
		x = _x;
		y = _y;
	}
	point operator - (const point &other) const
	{
		return point(x - other.x, y - other.y);
	}
	point operator + (const point &other) const
	{
		return point(x + other.x, y + other.y);
	}
	double dist() const
	{
		return sqrt(x*x*1. + y*y);
	}
	ll operator % (const point &other) const
	{
		return x*other.y - y*other.x;
	}
	ll operator * (const point &other) const
	{
		return x*x + y*y;
	}
	bool operator == (const point &other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator < (const point & other) const
	{
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};
ll llabs(ll x)
{
	if (x >= 0) return x;
	return -x;
}
int sign(double x)
{
	if (llabs(x) == 0) return 0;
	if (x > 0) return 1;
	return -1;
}
int sign(point A, point B, point C)
{
	return sign((B - A) % (C - A));
}
vector<point> getConvex(vector<point> & p) // res[0] == res.back();
{
	sort(p.begin(), p.end());
	point A = p[0];
	point B = p.back();
	vector<point> up, down;
	up.push_back(A);
	down.push_back(A);
	for (int i = 1; i < p.size(); ++i)
	{
		if (i == p.size() - 1 || sign(A, p[i], B) > 0)
		{
			while (up.size() > 1 && sign(up[up.size() - 2], p[i], up[up.size() - 1]) >= 0)
				up.pop_back();
			up.push_back(p[i]);
		}
		if (i == p.size() - 1 || sign(A, p[i], B) < 0)
		{
			while (down.size() > 1 && sign(down[down.size() - 2], p[i], down[down.size() - 1]) <= 0)
				down.pop_back();
			down.push_back(p[i]);
		}
	}
	for (int i = down.size() - 2; i >= 0; --i)
	{
		up.push_back(down[i]);
	}
	return up;
}
