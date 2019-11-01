#pragma GCC optimize("O3")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
#define pb(x) push_back(x)
#define pob(x) pop_back(x)
#define FOR(i, n) for (int i = 0; i < n; i++)
#define gc(x) getchar(x)

int readint()
{
	int c = gc(), x = 0;
	bool neg = 0;
	for (; (c < 48 || c > 57) && c != 45; c = gc())
		;
	for (; (c > 47 && c < 58) || c == 45; c = gc())
	{
		if (c == 45)
		{
			neg = true;
			continue;
		}
		x = (x << 1) + (x << 3) + c - 48;
	}
	return neg ? x * (-1) : x;
}

const double EPS = 0.0;
const double INF = 1E9;
double between_d(double x, double l, double r)
{
	return (min(l, r) <= x + EPS && x <= max(l, r) + EPS);
}
double same_d(double x, double y)
{
	return between_d(x, y, y);
}

/*Point*/
struct point
{
	double x, y;
	bool fixed;
	point()
	{
		x = y = 0.0;
		fixed = 0;
	}
	point(double _x, double _y, bool _fixed = false)
	{
		x = _x;
		y = _y;
		fixed = _fixed;
	}
	bool operator<(point other) const
	{
		if (y < other.y + EPS)
			return true;
		if (y + EPS > other.y)
			return false;
		return x < other.x + EPS;
	}
	bool operator==(point other) const
	{
		return same_d(x, other.x) && same_d(y, other.y);
	}
	string print()
	{
		return to_string(x) + " " + to_string(y) + " " + to_string(fixed) + "\n";
	}
};
double e_dist(point P1, point P2)
{
	return hypot(P1.x - P2.x, P1.y - P2.y);
}

/*Vector*/
struct vec
{
	double x, y;
	vec()
	{
		x = y = 0.0;
	}
	vec(double _x, double _y)
	{
		x = _x;
		y = _y;
	}
	vec(point A)
	{
		x = A.x;
		y = A.y;
	}
	vec(point A, point B)
	{
		x = B.x - A.x;
		y = B.y - A.y;
	}
};

double cross(vec u, vec v)
{
	return (u.x * v.y - u.y * v.x);
}

double orientation(point O, point P, point Q)
{
	vec OP(O, P), OQ(O, Q);
	double c = cross(OP, OQ);
	return c;
}
/*Line*/
struct line
{
	double a, b, c;
	line()
	{
		a = b = c = 0.0;
	}
	line(double _a, double _b, double _c)
	{
		a = _a;
		b = _b;
		c = _c;
	}
	line(point P1, point P2)
	{
		if (P2 < P1)
		{
			point T;
			T = P1;
			P1 = P2;
			P2 = T;
		}
		if (same_d(P1.x, P2.x))
			a = 1.0, b = 0.0, c = -P1.x;
		else
			a = -(P1.y - P2.y) / (P1.x - P2.x), b = 1.0, c = -(a * P1.x) - P1.y;
	}
	line(point P, double slope)
	{
		if (same_d(slope, INF))
			a = 1.0, b = 0.0, c = -P.x;
		else
			a = -slope, b = 1.0, c = -(a * P.x) - P.y;
	}
	bool operator==(line other) const
	{
		return same_d(a, other.a) && same_d(b, other.b) && same_d(c, other.c);
	}
	double slope()
	{
		if (same_d(b, 0.0))
			return INF;
		return -(a / b);
	}
};

/*Line Segment*/
struct segment
{
	point P, Q;
	line L;
	segment()
	{
		point T1;
		P = Q = T1;
		line T2;
		L = T2;
	}
	segment(point _P, point _Q)
	{
		if (_Q < _P)
		{
			point T1 = _P;
			_P = _Q;
			_Q = T1;
		}
		P = _P;
		Q = _Q;
		line T2(_P, _Q);
		L = T2;
	}
	bool operator==(segment other) const
	{
		return P == other.P && Q == other.Q;
	}
};
bool onSegment(point P, segment S)
{
	if (orientation(S.P, S.Q, P) != 0.0)
		return false;
	return between_d(P.x, S.P.x, S.Q.x) && between_d(P.y, S.P.y, S.Q.y);
}

/*Polygon CW*/
struct polygon
{
	vector<point> P;
	polygon()
	{
		P.clear();
	}
	polygon(vector<point> &_P)
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
	double perimeter()
	{
		double ret = 0;
		FOR(i, P.size())
		{
			ret += e_dist(P[i], P[next(i)]);
		}
		return ret;
	}
	double area()
	{
		double ret = 0;
		FOR(i, P.size())
		{
			ret += P[i].x * (P[prev(i)].y - P[next(i)].y);
		}
		return ret / 2;
	}
};

polygon convexHull(vector<point> &pts)
{
	sort(pts.begin(), pts.end());
	vector<point> hull;
	for (int i = 0; i < 2; i++)
	{
		int start = (int)hull.size();
		for (int i = 0; i < pts.size(); i++)
		{
			point pt = pts[i];
			while ((int)hull.size() >= start + 2 && orientation(hull[(int)hull.size() - 1], hull[(int)hull.size() - 2], pt) <= 0.0)
				hull.pob();
			hull.pb(pt);
		}
		hull.pop_back();
		reverse(pts.begin(), pts.end());
	}
	if ((int)hull.size() == 2 && hull[0] == hull[1])
		hull.pob();
	return polygon(hull);
}

int inSimplePolygon(point P, polygon &A)
{ //-1 inside,0 onsegment, 1 outside
	int ret = 0;
	FOR(i, A.P.size())
	{
		if (P == A.P[i])
			return 0;
		int j = A.next(i);
		if (onSegment(P, segment(A.P[i], A.P[j])))
			return 0;
		bool below = (A.P[i].y < P.y);
		if (below != (A.P[j].y < P.y))
		{
			double o = orientation(P, A.P[i], A.P[j]);
			if (o == 0.0)
				return 0;
			if (below == (o > 0.0))
				ret += below ? 1 : -1;
		}
	}
	return ret == 0 ? 1 : -1;
}

map<point, int> pool;

bool find(queue<point> q, point cur)
{
	if (pool[cur] + pool[point(cur.x, cur.y, !cur.fixed)] > 0)
		return true;
	return false;
}

vector<point> getTriangle(polygon &triangle, queue<point> q, vector<point> trees)
{
	vector<point> points;

	while (!q.empty())
	{
		if (inSimplePolygon(q.front(), triangle) != 1)
		{
			points.pb(q.front());
		}
		q.pop();
	}
	for (int i = 0; i < trees.size(); i++)
	{
		if (inSimplePolygon(trees[i], triangle) != 1)
		{
			points.pb(trees[i]);
		}
	}

	polygon P = convexHull(points);

	vector<point> pts;
	int i = 0;
	while (1)
	{
		if (P.P[i] == triangle.P[0])
		{
			if (P.P[P.next(i)] == triangle.P[2])
			{
				i = P.prev(i);
				while (!(P.P[i] == triangle.P[2]))
				{
					pts.pb(P.P[i]);
					i = P.prev(i);
				}
			}
			else
			{
				i = P.next(i);
				while (!(P.P[i] == triangle.P[2]))
				{
					pts.pb(P.P[i]);
					i = P.next(i);
				}
			}
			break;
		}
		i = P.next(i);
	}
	return pts;
}

polygon solve(polygon &perimeter, vector<point> &trees)
{
	queue<point> q;
	for (int i = 0; i < perimeter.P.size(); i++)
	{
		q.push(perimeter.P[i]);
	}

	point bef = perimeter.P[perimeter.P.size() - 1];
	while (1)
	{
		bool erased = 0;
		int count = q.size();
		while (count--)
		{
			point cur = q.front();
			q.pop();
			pool[cur]--;
			if (!cur.fixed && (!find(q, cur) || cur == bef || cur == q.front()) && orientation(cur, bef, q.front()) <= 0.0)
			{
				erased = true;
				polygon triangle;
				triangle.P.pb(bef);
				triangle.P.pb(cur);
				triangle.P.pb(q.front());
				vector<point> points = getTriangle(triangle, q, trees);
				for (int i = 0; i < points.size(); i++)
				{
					q.push(points[i]);
					pool[points[i]]++;
					bef = points[i];
				}
			}
			else
			{
				q.push(cur);
				pool[cur]++;
				bef = cur;
			}
		}
		if (!erased)
			break;
	}

	vector<point> hull;
	while (!q.empty())
	{
		hull.pb(q.front());
		q.pop();
	}
	return polygon(hull);
}

int main()
{
	int kase = 1;
	int n, m;
	while (cin >> n)
	{
		pool.clear();
		cin >> m;
		polygon perimeter;
		vector<point> trees;

		for (int i = 0; i < n; i++)
		{
			double a = readint(), b = readint();
			pool[point(a, b, false)]++;
			perimeter.P.push_back(point(a, b, false));
		}

		if (m == 0 || m == 1)
		{
			printf("Case #%d: %.3lf\n", kase++, 0.0);
			continue;
		}

		for (int i = 0; i < m; i++)
		{
			double a = readint(), b = readint();
			pool[point(a, b, true)]++;
			trees.push_back(point(a, b, true));
		}

		polygon hasil = solve(perimeter, trees);

		printf("Case #%d: %.3lf\n", kase++, hasil.perimeter());
	}
}
