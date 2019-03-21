struct point
{
	double x, y;
	point (){}
	point (double _x, double _y)
	{
		x = _x;
		y = _y;
	}
	point operator - (const point & other) const
	{
		return point (x - other.x, y - other.y);
	}
	point operator + (const point & other) const
	{
		return point (x + other.x, y + other.y);
	}
	point rot(double alf) const
	{
		return point (cos(alf)*x - sin(alf)*y, sin(alf)*x + cos(alf)*y);
	}
	point operator * (const double f) const
	{
		return point(x*f, y*f);
	}
	point getNorm()
	{
		return point(y, -x);
	}
	point setLen(double len)
	{
		return (*this) * (len/dist());
	}
	double operator * (const point & other) const
	{
		return x*other.x + y*other.y;
	}
	double operator % (const point & other) const
	{
		return x*other.y - y*other.x;
	}	
	double dist()
	{
		return sqrt(x*x + y*y);
	}
	double getAng()
	{
		return atan2(y, x);
	}
	
	bool operator == (const point & other) const
	{
		return fabs(x-other.x) < EPS && fabs(y - other.y) < EPS;
	}
	void scan()
	{
		scanf ("%lf%lf", &x, &y);
	}
	void print() const
	{
		printf("%lf %lf\n", x, y);
	}
	bool operator < (const point & other)
	{
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};
double t;
point inter(point a, point b, point c, point d)
{
	point v1 = (b - a);
	point v2 = (d - c);
	swap(v2.x, v2.y);
	v2.y = -v2.y;
	t = (c - a)*v2 / (v1*v2);
	return a + v1*t;
}
int sign(double x)
{
	if (fabs(x) < EPS) return 0;
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