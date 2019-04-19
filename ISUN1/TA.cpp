#include <bits/stdc++.h>
using namespace std;
const double EPS = 0.0;
const double PI = acos(-1.0);
const double INF = 1E9;
double between_d(double x, double l, double r)
{
    return (min(l, r) <= x + EPS && x <= max(l, r) + EPS);
}
double same_d(double x, double y)
{
    return between_d(x, y, y);
}
double dabs(double x)
{
    if (x < EPS)
        return -x;
    return x;
}
int sign(double x)
{
    return (0.0 < x) - (x < 0.0);
}

struct Point
{
    double x, y;
    int z;
    Point()
    {
        x = y = 0.0;
        z = 0;
    }
    Point(double _x, double _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z
    }
    bool operator<(Point other) const
    {
        if (y < other.y + EPS)
            return true;
        if (y + EPS > other.y)
            return false;
        return x < other.x + EPS;
    }
    bool operator==(Point other) const
    {
        return same_d(x, other.x) && same_d(y, other.y);
    }
    void print(char c)
    {
        printf("%lf %lf%c", x, y, c);
    }
};
double e_dist(Point P1, Point P2)
{
    return hypot(P1.x - P2.x, P1.y - P2.y);
}
double m_dist(Point P1, Point P2)
{
    return dabs(P1.x - P2.x) + dabs(P1.y - P2.y);
}
bool PointBetween(Point P, Point L, Point R)
{
    return (e_dist(L, P) + e_dist(P, R) == e_dist(L, R));
}
Point mid(Point P, Point Q)
{
    return Point((P.x + Q.x) / 2, (P.y + Q.y) / 2);
}

struct Vec
{
    double x, y;
    Vec()
    {
        x = y = 0.0;
    }
    Vec(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    Vec(Point A)
    {
        x = A.x;
        y = A.y;
    }
    Vec(Point A, Point B)
    {
        x = B.x - A.x;
        y = B.y - A.y;
    }
};
Vec scale(Vec v, double s)
{
    return Vec(v.x * s, v.y * s);
}
Vec flip(Vec v)
{
    return Vec(-v.x, -v.y);
}
double dot(Vec u, Vec v)
{
    return (u.x * v.x + u.y * v.y);
}
double cross(Vec u, Vec v)
{
    return (u.x * v.y - u.y * v.x);
}
double norm_sq(Vec v)
{
    return (v.x * v.x + v.y * v.y);
}
Point translate(Point P, Vec v)
{
    return Point(P.x + v.x, P.y + v.y);
}
Point rotate(Point P, Point O, double angle)
{
    Vec v(O);
    P = translate(P, flip(v));
    return translate(Point(P.x * cos(angle) - P.y * sin(angle), P.x * sin(angle) + P.y * cos(angle)), v);
}

double orientation(Point O, Point P, Point Q)
{
    Vec OP(O, P), OQ(O, Q);
    double c = cross(OP, OQ);
    return c;
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
    double perimeter()
    {
        double ret = 0;
        for (int i = 0; i < P.size(); i++)
        {
            ret += e_dist(P[i], P[next(i)]);
        }
        return ret;
    }
    double area()
    {
        double ret = 0;
        for (int i = 0; i < P.size(); i++)
        {
            ret += P[i].x * (P[prev(i)].y - P[next(i)].y);
        }
        return ret / 2;
    }
};

Polygon convexHull(vector<Point> &pts)
{
    sort(pts.begin(), pts.end());
    vector<Point> hull;
    for (int i = 0; i < 2; i++)
    {
        int start = (int)hull.size();
        for (auto pt : pts)
        {
            while ((int)hull.size() >= start + 2 && (orientation(hull[(int)hull.size() - 1], hull[(int)hull.size() - 2], pt) <= 0.0))
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
    Polygon p;
    vector<Point> arr;
    arr.push_back(Point(0, 0, 0));
    arr.push_back(Point(4, 0, 0));
    arr.push_back(Point(0, 4, 0));
    arr.push_back(Point(0, -4, 0));
    arr.push_back(Point(-4, 0, 0));
    arr.push_back(Point(-1, 1, 1));
    arr.push_back(Point(-1, -1, 1));
    arr.push_back(Point(1, 1, 1));
    arr.push_back(Point(1, -1, 1));
    p = convexHull(arr);
    for (int i = 0; i < p.P.size(); i++)
    {
        p.P[i].print('\n');
    }
}
