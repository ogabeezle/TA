#include <bits/stdc++.h>
using namespace std;

const double EPS = 0.0;
const double pi = acos(-1.0);
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
    return (0.0 < x) - (x < 0, 0);
}

struct point
{
    double x, y;
    point()
    {
        x = y = 0.0;
    }
    point(double _x, double _y)
    {
        x = _x;
        y = _y;
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
};

double e_dist(point P1, point P2)
{
    return hypot(P1.x - P2.x, P1.y - P2.y);
}

double m_dist(point P1, point P2)
{
    return dabs(P1.x - P2.x) + dabs(P1.y - P2.y);
}

bool pointBetween(point P, point L, point R)
{
    return (e_dist(L, P) + e_dist(P, R) == e_dist(L, R));
}

point mid(point P, point Q)
{
    return point((P.x + Q.x) / 2, (P.y + Q.y) / 2);
}

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
    vec(point P)
    {
        x = P.x;
        y = P.y;
    }
    vec(point A, point B)
    {
        x = B.x - A.x;
        y = B.y - A.y;
    }
};

vec scale(vec v, double a)
{
    return vec(v.x * a, v.y * a);
}

vec flip(vec v)
{
    return vec(-v.x, -v.y);
}

double dot(vec u, vec v)
{
    return (u.x * v.x + u.y * v.y);
}

double cross(vec u, vec v)
{
    return (u.x * v.y - u.y * v.x);
}

double norm_sq(vec v)
{
    return (v.x * v.x + v.y * v.y);
}

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

double orientation(point O, point P, point Q)
{
    vec OP(O, P), OQ(O, Q);
    double c = cross(OP, OQ);
    return c;
}

polygon convexHull(vector<point> &pts)
{
    sort(pts.begin(), pts.end());
    vector<point> hull;
    //for(int i=0;i<pts.size();i++) printf("%lf %lf\n",pts[i].x,pts[i].y);
    for (int i = 0; i < 2; i++)
    {
        int start = (int)hull.size();
        for (auto pt : pts)
        {
            while ((int)hull.size() >= start + 2 && orientation(hull[(int)hull.size() - 1], hull[(int)hull.size() - 2], pt) <= 0.0)
                hull.pop_back();
            hull.push_back(pt);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if ((int)hull.size() == 2 && hull[0] == hull[1])
        hull.pop_back();
    return polygon(hull);
}

int inConvexPolygon(point &P, polygon &A, int idxTop)
{ //-1 inside,0 onsegment, 1 outside
    if (P < A.P[0] || A.P[idxTop] < P)
        return 1;
    double o = orientation(P, A.P[0], A.P[idxTop]);
    if (o == 0.0)
    {
        if (P == A.P[0] || P == A.P[idxTop])
            return 0;
        return ((idxTop == 1 || idxTop + 1 == (int)A.P.size()) ? 0 : -1);
    }
    else if (o < 0.0)
    {
        vector<point>::reverse_iterator itLeft = upper_bound(A.P.rbegin(), A.P.rend() - idxTop - 1, P);
        return sign(orientation((itLeft == A.P.rbegin()) ? A.P[0] : itLeft[-1], P, itLeft[0]));
    }
    else
    {
        vector<point>::iterator itRight = lower_bound(A.P.begin() + 1, A.P.begin() + idxTop, P);
        return sign(orientation(itRight[0], P, itRight[-1]));
    }
}

polygon generate()
{
    srand(time(NULL));
    vector<point> arr;
    for (int i = 0; i < 20; i++)
    {
        double a = rand() % 10000 - 5000;
        double b = rand() % 10000 - 5000;
        arr.push_back(point(a, b));
    }

    arr.push_back(point(2, 3));
    polygon P = convexHull(arr);
    return P;
}

int main()
{
    polygon P;
    while (1)
    {
        P = generate();
        point x = point(0, 0);
        printf("%d\n", inConvexPolygon(x, P, P.P.size() - 1));
        if (inConvexPolygon(x, P, P.P.size() - 1) < 1)
            break;
    }

    for (int i = 0; i < P.P.size(); i++)
    {
        printf("%lf %lf\n", P.P[i].x, P.P[i].y);
    }
}
