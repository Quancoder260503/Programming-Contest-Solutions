#include "bits/stdc++.h"

using namespace std;

#define double long double

double xA, yA, xB, yB, xC, yC;

const double oo = 1e5;
const int L = 100; 

double dist(double x, double y, double x2, double y2) {
  return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
}

double g(double x, double y) {
  return dist(x, y, xA, yA) + dist(x, y, xB, yB) + dist(x, y, xC, yC);
}
pair<double, double> findy(double x) {
  double left = -oo, right = oo;
  for (int i = 1; i < L; i++) {
    double y1 = (2 * left + right) / 3.0;
    double y2 = (left + 2 * right) / 3.0;
    if (g(x, y1) < g(x, y2))
      right = y2;
    else
      left = y1;
  }
  return {g(x, left), left};
}
pair<double, double> findx() {
  double left = -oo, right = oo;
  for (int i = 1; i < L; i++) {
    double x1 = (2 * left + right) / 3.0;
    double x2 = (left + 2 * right) / 3.0;
    if (findy(x1).first < findy(x2).first)
      right = x2;
    else
      left = x1;
  }
  return {left, findy(left).second};
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> xA >> yA >> xB >> yB >> xC >> yC; 
  pair<double, double> ret = findx(); 
  cout << setprecision(12) << ret.first << " " << ret.second << '\n';
  return 0;
}