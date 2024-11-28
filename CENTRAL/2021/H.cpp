#include "bits/stdc++.h"
using namespace std;
#ifndef EPS // allow test files to overwrite EPS
#define EPS 1e-6
#endif

const double PI = acos(-1.0);
double sqr(double x) {return x * x;}; 
double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b)
{
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

// for int types
template <typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type * = nullptr>
inline int cmp(T a, T b)
{
    return (a == b) ? 0 : (a < b) ? -1
                                  : 1;
}

template <typename T>
struct P
{
    T x, y;
    P() { x = y = T(0); }
    P(T _x, T _y) : x(_x), y(_y) {}

    P operator+(const P &a) const { return P(x + a.x, y + a.y); }
    P operator-(const P &a) const { return P(x - a.x, y - a.y); }
    P operator*(T k) const { return P(x * k, y * k); }
    P<double> operator/(double k) const { return P(x / k, y / k); }

    T operator*(const P &a) const { return x * a.x + y * a.y; } // dot product
    T operator%(const P &a) const { return x * a.y - y * a.x; } // cross product

    int cmp(const P<T> &q) const
    {
        if (int t = ::cmp(x, q.x))
            return t;
        return ::cmp(y, q.y);
    }

#define Comp(x) \
    bool operator x(const P &q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
#undef Comp

        T norm()
    {
        return x * x + y * y;
    }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return hypot(x, y); }

    P<double> rotate(double alpha)
    {
        double cosa = cos(alpha), sina = sin(alpha);
        return P(x * cosa - y * sina, x * sina + y * cosa);
    }
};
using Point = P<double>;

// Compare points by (y, x)
template <typename T = double>
bool cmpy(const P<T> &a, const P<T> &b)
{
    if (cmp(a.y, b.y))
        return a.y < b.y;
    return a.x < b.x;
};

template <typename T>
int ccw(P<T> a, P<T> b, P<T> c)
{
    return cmp((b - a) % (c - a), T(0));
}

int RE_TRAI = ccw(P<int>(0, 0), P<int>(0, 1), P<int>(-1, 1));
int RE_PHAI = ccw(P<int>(0, 0), P<int>(0, 1), P<int>(1, 1));

template <typename T>
istream &operator>>(istream &cin, P<T> &p)
{
    cin >> p.x >> p.y;
    return cin;
}
template <typename T>
ostream &operator<<(ostream &cout, const P<T> &p)
{
    cout << p.x << ' ' << p.y;
    return cout;
}

double angle(Point a, Point o, Point b)
{ // min of directed angle AOB & BOA
    a = a - o;
    b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

double directed_angle(Point a, Point o, Point b)
{ // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x) + atan2(b.y - o.y, b.x - o.x);
    while (t < 0)
        t += 2 * PI;
    return t;
}

// Distance from p to Line ab (closest Point --> c)
// i.e. c is projection of p on AB
double distToLine(Point p, Point a, Point b, Point &c)
{
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p - c).len();
}

// Distance from p to segment ab (closest Point --> c)
double distToLineSegment(Point p, Point a, Point b, Point &c)
{
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    if (u < 0.0)
    {
        c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (u > 1.0)
    {
        c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b, c);
}

// NOTE: WILL NOT WORK WHEN a = b = 0.
struct Line
{
    double a, b, c; // ax + by + c = 0
    Point A, B;     // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    Line(Point _A, Point _B) : A(_A), B(_B)
    {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    Line(Point P, double m)
    {
        a = -m;
        b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point p)
    {
        return a * p.x + b * p.y + c;
    }
};
ostream &operator>>(ostream &cout, const Line &l)
{
    cout << l.a << "*x + " << l.b << "*y + " << l.c;
    return cout;
}

bool areParallel(Line l1, Line l2)
{
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(Line l1, Line l2)
{
    return areParallel(l1, l2) && cmp(l1.c * l2.a, l2.c * l1.a) == 0 && cmp(l1.c * l2.b, l1.b * l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p)
{
    if (areParallel(l1, l2))
        return false;
    double dx = l1.b * l2.c - l2.b * l1.c;
    double dy = l1.c * l2.a - l2.c * l1.a;
    double d = l1.a * l2.b - l2.a * l1.b;
    p = Point(dx / d, dy / d);
    return true;
}

// closest point from p in line l.
void closestPoint(Line l, Point p, Point &ans)
{
    if (fabs(l.b) < EPS)
    {
        ans.x = -(l.c) / l.a;
        ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS)
    {
        ans.x = p.x;
        ans.y = -(l.c) / l.b;
        return;
    }
    Line perp(l.b, -l.a, -(l.b * p.x - l.a * p.y));
    areIntersect(l, perp, ans);
}

// Segment intersect
// Tested:
// - https://cses.fi/problemset/task/2190/
// returns true if p is on segment [a, b]
template <typename T>
bool onSegment(const P<T> &a, const P<T> &b, const P<T> &p)
{
    return ccw(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

// Returns true if segment [a, b] and [c, d] intersects
// End point also returns true
template <typename T>
bool segmentIntersect(const P<T> &a, const P<T> &b, const P<T> &c, const P<T> &d)
{
    if (onSegment(a, b, c) || onSegment(a, b, d) || onSegment(c, d, a) || onSegment(c, d, b))
    {
        return true;
    }

    return ccw(a, b, c) * ccw(a, b, d) < 0 && ccw(c, d, a) * ccw(c, d, b) < 0;
}
struct Circle : Point
{
    double r;
    Circle(double _x = 0, double _y = 0, double _r = 0) : Point(_x, _y), r(_r) {}
    Circle(Point p, double _r) : Point(p), r(_r) {}

    bool contains(Point p) { return (*this - p).len() <= r + EPS; }

    double area() const { return r * r * M_PI; }

    // definitions in https://en.wikipedia.org/wiki/Circle
    // assumption: 0 <= theta <= 2*PI
    // theta: angle in radian
    double sector_area(double theta) const
    {
        return 0.5 * r * r * theta;
    }

    // assumption: 0 <= theta <= 2*PI
    // theta: angle in radian
    double segment_area(double theta) const
    {
        return 0.5 * r * r * (theta - sin(theta));
    }
};
istream &operator>>(istream &cin, Circle &c)
{
    cin >> c.x >> c.y >> c.r;
    return cin;
}
ostream &operator<<(ostream &cout, const Circle &c)
{
    cout << '(' << c.x << ", " << c.y << ") " << c.r;
    return cout;
}

// Find common tangents to 2 circles
// Tested:
// - http://codeforces.com/gym/100803/ - H
// Helper method
void tangents(Point c, double r1, double r2, vector<Line> &ans)
{
    double r = r2 - r1;
    double z = sqr(c.x) + sqr(c.y);
    double d = z - sqr(r);
    if (d < -EPS)
        return;
    d = sqrt(fabs(d));
    Line l((c.x * r + c.y * d) / z,
           (c.y * r - c.x * d) / z,
           r1);
    ans.push_back(l);
}
// Actual method: returns vector containing all common tangents
vector<Line> tangents(Circle a, Circle b)
{
    vector<Line> ans;
    ans.clear();
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2)
            tangents(b - a, a.r * i, b.r * j, ans);
    for (int i = 0; i < (int)ans.size(); ++i)
        ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;

    vector<Line> ret;
    for (int i = 0; i < (int)ans.size(); ++i)
    {
        if (std::none_of(ret.begin(), ret.end(), [&](Line l)
                         { return areSame(l, ans[i]); }))
        {
            ret.push_back(ans[i]);
        }
    }
    return ret;
}

// Circle & line intersection
// Tested:
// - http://codeforces.com/gym/100803/ - H
vector<Point> intersection(Line l, Circle cir)
{
    double r = cir.r, a = l.a, b = l.b, c = l.c + l.a * cir.x + l.b * cir.y;
    vector<Point> res;

    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS)
        return res;
    else if (fabs(c * c - r * r * (a * a + b * b)) < EPS)
    {
        res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
        return res;
    }
    else
    {
        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
        res.push_back(Point(bx, by) + Point(cir.x, cir.y));
        return res;
    }
}

// helper functions for commonCircleArea
double cir_area_solve(double a, double b, double c)
{
    return acos((a * a + b * b - c * c) / 2 / a / b);
}
double cir_area_cut(double a, double r)
{
    double s1 = a * r * r / 2;
    double s2 = sin(a) * r * r / 2;
    return s1 - s2;
}
// Tested: http://codeforces.com/contest/600/problem/D
double commonCircleArea(Circle c1, Circle c2)
{ // return the common area of two circle
    if (c1.r < c2.r)
        swap(c1, c2);
    double d = (c1 - c2).len();
    if (d + c2.r <= c1.r + EPS)
        return c2.r * c2.r * M_PI;
    if (d >= c1.r + c2.r - EPS)
        return 0.0;
    double a1 = cir_area_solve(d, c1.r, c2.r);
    double a2 = cir_area_solve(d, c2.r, c1.r);
    return cir_area_cut(a1 * 2, c1.r) + cir_area_cut(a2 * 2, c2.r);
}

// Check if 2 circle intersects. Return true if 2 circles touch
bool areIntersect(Circle u, Circle v)
{
    if (cmp((u - v).len(), u.r + v.r) > 0)
        return false;
    if (cmp((u - v).len() + v.r, u.r) < 0)
        return false;
    if (cmp((u - v).len() + u.r, v.r) < 0)
        return false;
    return true;
}

// If 2 circle touches, will return 2 (same) points
// If 2 circle are same --> be careful
// Tested:
// - http://codeforces.com/gym/100803/ - H
// - http://codeforces.com/gym/100820/ - I
vector<Point> circleIntersect(Circle u, Circle v)
{
    vector<Point> res;
    if (!areIntersect(u, v))
        return res;
    double d = (u - v).len();
    double alpha = acos((u.r * u.r + d * d - v.r * v.r) / 2.0 / u.r / d);

    Point p1 = (v - u).rotate(alpha);
    Point p2 = (v - u).rotate(-alpha);
    res.push_back(p1 / p1.len() * u.r + u);
    res.push_back(p2 / p2.len() * u.r + u);
    return res;
}
signed main(void)
{ 
    Point a, b, c; 
    double R, P; 
    double cons = 0.05;
    cin >> a.x >> a.y; 
    cin >> b.x >> b.y; 
    cin >> c.x >> c.y; 
    cin >> R >> P; 
    P = P / 100.0; 
    Point _; 
    if(cmp(distToLine(c, a, b, _), R) >= 0)
    {
        cout << "NO" << '\n';
        return 0;
    }
    Circle C; 
    auto I = intersection(Line(a, b) , C = Circle(c.x, c.y, R)); 
    double angleA = angle(I[0], c, I[1]);
    double ret = C.segment_area(angleA) / C.area(); 
    cout << (fabsl(ret - P) <= cons ? "YES" : "NO") << '\n';   
    return 0;
}