struct HalfPlane
{
	Point A, n;
	bool containPoint(Point P, bool strict) const
	{
		if (strict)
			return Gr((P - A) % n, 0);
		return GrEq((P - A) % n, 0);
	}
	bool operator < (const HalfPlane &a) const
	{
		if (getQ(n) != getQ(a.n))
			return getQ(n) < getQ(a.n);
		if (!Eq(n * a.n, 0))
			return n * a.n > 0;
		return !containPoint(a.A, false);
	}
};

const int N = (int)1e6 + 10;
HalfPlane hull[N];

//WORKS CORRECTLY ONLY WITH BOUNDING BOX
vector <Point> getIntersection(vector <HalfPlane> planes)
{
	sort(planes.begin(), planes.end());
	planes.resize(unique(planes.begin(), planes.end(), 
				[](const HalfPlane &a, const HalfPlane &b) 
				{ return Eq(a.n * b.n, 0); }) - planes.begin());;
	int l = N / 2, r = N / 2;
	for (int i = 0; i < (int)planes.size(); i++)
	{
		while (r - l > 1 && 
			   !planes[i].containPoint(hull[r - 1].intersects(hull[r - 2]), true))
			r--;
		while (r - l > 1 && 
			   !planes[i].containPoint(hull[l].intersects(hull[l + 1]), true))
			l++;
		if (r - l > 1 && Ls(hull[l].n * hull[r - 1].n, 0))
		{
			if (hull[r - 1].containPoint(hull[l].intersects(planes[i]), true))
				hull[r++] = planes[i];
		}
		else
			hull[r++] = planes[i];
		if (r - l > 1 && LsEq(hull[r - 2].n * hull[r - 1].n, 0))
			return {};
	}
	vector <Point> inter = {};
	for (int i = l; i < r; i++)
		inter.push_back(hull[i].intersects(hull[i == r - 1 ? l : i + 1]));
	return inter;
}
