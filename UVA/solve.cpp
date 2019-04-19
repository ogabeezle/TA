#include <bits/stdc++.h>
using namespace std;

#define limit 20

int gcd(int a, int b)
{
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (b == 0 || a == 0)
		return 1;
	if (a % b == 0)
		return b;
	return gcd(b, a % b);
}

class Frac
{
  public:
	int num;
	int denum;
	Frac(int _num)
	{
		num = _num;
		denum = 1;
	}
	Frac(int _num, int _denum)
	{
		if (_denum < 0)
		{
			_num *= -1;
			_denum *= -1;
		}
		int g = gcd(_num, _denum);
		num = _num / g;
		denum = _denum / g;
	}
	Frac()
	{
		num = 0;
		denum = 1;
	}
	Frac operator+(Frac other) const
	{
		int n, d;
		n = num * other.denum + other.num * denum;
		d = denum * other.denum;
		int g = gcd(n, d);
		return Frac(n / g, d / g);
	}
	Frac operator-(Frac other) const
	{
		int n, d;
		n = num * other.denum - other.num * denum;
		d = denum * other.denum;
		int g = gcd(n, d);
		return Frac(n / g, d / g);
	}
	Frac operator*(Frac other) const
	{
		int n, d;
		n = num * other.num;
		d = denum * other.denum;
		int g = gcd(n, d);
		return Frac(n / g, d / g);
	}
	Frac operator/(Frac other) const
	{
		int n, d;
		n = num * other.denum;
		d = denum * other.num;
		int g = gcd(n, d);
		return Frac(n / g, d / g);
	}
	Frac operator=(int other) const
	{
		return Frac(other);
	}
	bool operator>(Frac other) const
	{
		return (num * other.denum > other.num * denum);
	}
	bool operator<(Frac other) const
	{
		return (num * other.denum < other.num * denum);
	}
	bool operator<=(Frac other) const
	{
		return (num * other.denum <= other.num * denum);
	}
	bool operator>=(Frac other) const
	{
		return (num * other.denum >= other.num * denum);
	}
	bool operator==(Frac other) const
	{
		return (num * other.denum == other.num * denum);
	}
	bool operator>(int other) const
	{
		Frac x = Frac(num, denum);
		return x > Frac(other);
	}
	bool operator<(int other) const
	{
		Frac x = Frac(num, denum);
		return x < Frac(other);
	}
	bool operator>=(int other) const
	{
		Frac x = Frac(num, denum);
		return x >= Frac(other);
	}
	bool operator<=(int other) const
	{
		Frac x = Frac(num, denum);
		return x <= Frac(other);
	}
	bool operator==(int other) const
	{
		Frac x = Frac(num, denum);
		return x == Frac(other);
	}
	void print()
	{
		cout << num << "/" << denum;
	}
	void print(char x)
	{
		print();
		if (x != '\n')
			cout << x;
		else
			cout << endl;
	}
	void printInt()
	{
		cout << num / denum;
	}
	void printInt(char x)
	{
		printInt();
		if (x != '\n')
			cout << x;
		else
			cout << endl;
	}
};

Frac maxFrac(Frac a, Frac b)
{
	if (a > b)
		return a;
	return b;
}

Frac minFrac(Frac a, Frac b)
{
	if (a > b)
		return b;
	return a;
}

bool between_d(Frac x, Frac l, Frac r)
{
	return (minFrac(l, r) <= x && x <= maxFrac(l, r));
}

bool same_d(Frac x, Frac y)
{
	return between_d(x, y, y);
}

Frac dabs(Frac x)
{
	if (x.num < 0)
		x.num *= -1;
	return x;
}

class Point
{
  public:
	Frac x;
	Frac y;
	Point()
	{
		x = Frac(0);
		y = Frac(0);
	}
	Point(Frac _x, Frac _y)
	{
		x = _x;
		y = _y;
	}
	Point(int xnum, int xdenum, int ynum, int ydenum)
	{
		x = Frac(xnum, xdenum);
		y = Frac(ynum, ydenum);
	}
	bool operator<(Point other) const
	{
		if (y < other.y)
			return true;
		if (y > other.y)
			return false;
		return x < other.x;
	}
	bool operator==(Point other) const
	{
		return same_d(x, other.x) && same_d(y, other.y);
	}
	void print()
	{
		x.printInt(' ');
		y.printInt();
	}
	void print(char x)
	{
		print();
		if (x != '\n')
			cout << x;
		else
			cout << endl;
	}
};

Frac hypot(Frac a, Frac b)
{
	return (a * a) + (b * b);
}

Frac e_dist(Point P1, Point P2)
{
	// printf("e_dist of point ");
	// P1.print(" and ");
	// P2.print("\n");
	// (P1.x - P2.x).print('\n');
	// (P1.y - P2.y).print("\nhasil hypot = ");
	// hypot(P1.x - P2.x, P1.y - P2.y).print("\n");
	return hypot(P1.x - P2.x, P1.y - P2.y);
}

Frac m_dist(Point P1, Point P2)
{
	return dabs(P1.x - P2.x) + dabs(P1.y - P2.y);
}

bool pointBetween(Point P, Point L, Point R)
{
	Frac a = e_dist(L, P);
	Frac b = e_dist(P, R);
	Frac c = e_dist(L, R);
	return (a * b) == (c - a - b) * (c - a - b) / 4;
}

Point mid(Point P, Point Q)
{
	return Point((P.x + Q.x) / 2, (P.y + Q.y) / 2);
}

class Vec
{
  public:
	Frac x;
	Frac y;
	Vec()
	{
		x = y = Frac(0);
	}
	Vec(Frac _x, Frac _y)
	{
		x = _x;
		y = _y;
	}
	Vec(Point P)
	{
		x = P.x;
		y = P.y;
	}
	Vec(Point A, Point B)
	{
		x = B.x - A.x;
		y = B.y - A.y;
	}
};

Vec scale(Vec v, int a)
{
	return Vec(v.x * a, v.y * a);
}

Vec flip(Vec v)
{
	return Vec(v.x * -1, v.y * -1);
}

Frac dot(Vec u, Vec v)
{
	return (u.x * v.x + u.y * v.y);
}

Frac cross(Vec u, Vec v)
{
	return (u.x * v.y - u.y * v.x);
}

Frac norm_sq(Vec v)
{
	return (v.x * v.x + v.y * v.y);
}

struct Polygon
{
	vector<Point> P;
	Polygon()
	{
		P.clear();
	}
	Polygon(vector<Point> &_P)
	{
		P = _P;
	}
	int prev(int idx)
	{
		return (idx == 0 ? P.size() - 1 : idx - 1);
	}
	int next(int idx)
	{
		return (idx == P.size() - 1 ? 0 : idx + 1);
	}
	// Frac perimeter()
	// {
	// 	Frac ret = 0;
	// 	for (int i = 0; i < P.size(); i++)
	// 	{
	// 		ret = ret + e_dist(P[i], P[next(i)]);
	// 	}
	// 	return ret;
	// }
	Frac area()
	{
		Frac ret = Frac(0);
		for (int i = 0; i < P.size(); i++)
		{
			ret = ret + P[i].x * (P[prev(i)].y - P[next(i)].y);
		}
		return ret / 2;
	}
};

void swap(Frac &a, Frac &b)
{
	Frac temp;
	temp = a;
	a = b;
	b = temp;
}

int getX(map<Frac, Frac> check[], int asked)
{
	Frac x = Frac(asked);
	Frac maxi = Frac(-10000), mini = Frac(10000);
	cout << "AskX " << asked << endl;
	int count;
	cin >> count;
	for (int i = 0; i < count; i++)
	{
		int a, b;
		Frac temp;
		cin >> a >> b;
		temp = Frac(a, b);
		if (temp > maxi)
			maxi = temp;
		if (temp < mini)
			mini = temp;
	}
	if (count)
	{
		check[0][x] = maxi;
		check[1][x] = mini;
		if (mini == maxi)
			return 1;
		return 2;
	}
	return count;
}

Point getBetween(map<Frac, Frac> check[], Polygon &convex, int idx, Point to)
{
	Point from = convex.P[idx];
	Point midPoint;
	if (from.x - to.x == 1 || to.x - from.x == 1 || to.x == from.x)
		return to;

	Frac midFrac = (from.x + to.x) / Frac(2);
	int mid = midFrac.num / midFrac.denum;
	if (check[0].find(Frac(mid)) == check[0].end())
		getX(check, mid);

	if (from.x < to.x)
		midPoint = Point(Frac(mid), check[0][Frac(mid)]);
	else
		midPoint = Point(Frac(mid), check[1][Frac(mid)]);

	if (pointBetween(midPoint, from, to))
	{
		Frac min = to.x, max = convex.P[convex.next(idx)].x;
		while (1)
		{
			midFrac = (min + max) / Frac(2);
			mid = midFrac.num / midFrac.denum;
			if (check[0].find(Frac(mid)) == check[0].end())
				getX(check, mid);

			if (from.x < to.x)
				midPoint = Point(Frac(mid), check[0][Frac(mid)]);
			else
				midPoint = Point(Frac(mid), check[1][Frac(mid)]);

			if (pointBetween(midPoint, from, to))
			{
				min = Frac(mid);
				if (min - max == Frac(1) || max - min == Frac(1) || min == max)
					return midPoint;
			}

			else
			{
				max = Frac(mid);
				if (min - max == Frac(1) || max - min == Frac(1) || min == max)
				{
					if (midPoint.x == max)
					{
						if (from.x < to.x)
							return Point(min, check[0][min]);
						else
							return Point(min, check[1][min]);
					}
					else
					{
						if (from.x < to.x)
							return Point(max, check[0][max]);
						else
							return Point(max, check[1][max]);
					}
				}
			}
		}
	}
	else
	{
		return getBetween(check, convex, idx, midPoint);
	}
}

void convexing(map<Frac, Frac> check[], Polygon &convex)
{
	for (int i = 0; i < convex.P.size(); i++)
	{
		Point from = convex.P[i], to = convex.P[convex.next(i)];
		if (from.x - to.x == Frac(1) || to.x - from.x == Frac(1))
			continue;

		Frac midFrac = (from.x + to.x) / Frac(2);
		int mid = midFrac.num / midFrac.denum;

		if (check[0].find(Frac(mid)) == check[0].end())
			getX(check, mid);

		Point midPoint;
		if (from.x < to.x)
			midPoint = Point(Frac(mid), check[0][Frac(mid)]);
		else
			midPoint = Point(Frac(mid), check[1][Frac(mid)]);

		if (!pointBetween(midPoint, from, to))
			convex.P.insert(convex.P.begin() + i + 1, getBetween(check, convex, i, midPoint));
	}
}

Frac orientation(Point O, Point P, Point Q)
{
	Vec OP(O, P), OQ(O, Q);
	Frac c = cross(OP, OQ);
	return c;
}

Polygon convexHull(vector<Point> &pts)
{
	sort(pts.begin(), pts.end());
	// cout << endl;
	// for (int i = 0; i < pts.size(); i++)
	// {
	// 	pts[i].print('\n');
	// }
	// cout << endl;
	vector<Point> hull;
	//for(int i=0;i<pts.size();i++) printf("%lf %lf\n",pts[i].x,pts[i].y);
	for (int i = 0; i < 2; i++)
	{
		int start = (int)hull.size();
		for (auto pt : pts)
		{
			while ((int)hull.size() >= start + 2 && orientation(hull[(int)hull.size() - 1], hull[(int)hull.size() - 2], pt) <= Frac(0))
				hull.pop_back();
			hull.push_back(pt);
		}
		hull.pop_back();
		reverse(pts.begin(), pts.end());
	}
	if ((int)hull.size() == 2 && hull[0] == hull[1])
		hull.pop_back();
	return Polygon(hull);
}

int main()
{
	// Point p1 = Point(Frac(10), Frac(33, 4));
	// Point p2 = Point(Frac(2), Frac(5, 4));
	// Point p3 = mid(p1, p2);
	// p3 = mid(p1, p3);
	// p3.print('\n');
	// e_dist(p1, p2).print('\n');
	// bool x = pointBetween(p3, p1, p2);
	// printf("%d\n", x);
	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		map<Frac, Frac> check[2];
		Polygon convex;
		for (int i = 0; i < 2; i++)
		{
			int max = 20, min = 0, count, a, b;
			if (i == 0)
				max *= -1;
			while (1)
			{
				int mid = (min + max) / 2;
				count = getX(check, mid);
				if (count == 0)
					max = mid;
				else if (count == 1)
				{
					convex.P.push_back(Point(Frac(mid), check[0][Frac(mid)]));
					break;
				}
				else
					min = mid;
			}
		}
		convexing(check, convex);
		convex = convexHull(convex.P);
		cout << "Answer " << convex.P.size() << endl;
		for (int i = convex.P.size() - 1; i >= 0; i--)
			convex.P[i].print('\n');
	}
	return 0;
}