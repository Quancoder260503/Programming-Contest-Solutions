#include <bits/stdc++.h> 

using namespace std; 

#define double long double

const int ROUND = 1000000; 

int main() {
  double A, H;
  cin >> A >> H;
  auto f = [&](double x) { 
    return ((100 - A) * x - 100 * H / 6 + A * H / 3) * 6 / H * (H - x); 
  }; 
  double ret = max(5 * A * H / 6, 200.0 * H / 3); 
  double lo = H / 6; 
  double hi = H / 3;
  for(int _ = 0; _ < ROUND; _++) { 
    double x1 = (2 * lo + hi) / 3.0; 
    double x2 = (lo + 2 * hi) / 3.0; 
    if(f(x1) <= f(x2)) { 
      lo = x1; 
    } 
    else { 
      hi = x2; 
    } 
  }
  ret = max(ret, f(lo)); 
  cout << fixed << setprecision(10) << ret << '\n'; 
  return 0;
}
