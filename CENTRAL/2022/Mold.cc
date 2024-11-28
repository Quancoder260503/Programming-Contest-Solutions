#include "bits/stdc++.h"

using namespace std;
#define double long double

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<double> P;
double ccRadius(const P &A, const P &B, const P &C)
{
    return (B - A).dist() * (C - B).dist() * (A - C).dist() /
           abs((B - A).cross(C - A)) / 2;
}
P ccCenter(const P &A, const P &B, const P &C)
{
    P b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
}

pair<P, double> mec(vector<P> ps)
{
    shuffle(ps.begin(), ps.end(), mt19937(time(0)));
    P o = ps[0];
    double r = 0, EPS = 1 + 1e-8;
    for(int i = 0; i < ps.size(); i++) if ((o - ps[i]).dist() > r * EPS)
    {
        o = ps[i], r = 0;
        for(int j = 0; j < i; j++) if ((o - ps[j]).dist() > r * EPS)
        {
            o = (ps[i] + ps[j]) / 2;
            r = (o - ps[i]).dist();
            for(int k = 0; k < j; k++) if ((o - ps[k]).dist() > r * EPS)
            {
                o = ccCenter(ps[i], ps[j], ps[k]);
                r = (o - ps[i]).dist();
            }
        }
    }
    return {o, r};
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<P> pset;
    cout << fixed << setprecision(10);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            P p; 
            cin >> p.x >> p.y;
            pset.push_back(p);
        }
        auto [ret, r] = mec(pset);
        cout << ret.x << " " << ret.y << " " << r << '\n';
    }
    return 0;
}