#include "bits/stdc++.h"

using namespace std;

#define double long double 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<double>sum((1 << N));  
  for(int i = 0; i < N; i++) { 
    cin >> sum[(1 << i)]; 
  } 
  for(int i = 0; i < N; i++) {
    for(int mask = 0; mask < (1 << N); mask++) {
      if(mask & (1 << i)) { 
       sum[mask] += sum[mask ^ (1 << i)];  
      }
    }
  }
  vector<double>fact(N + 1); 
  fact[0] = 1; 
  for(int i = 1; i <= N; i++) { 
    fact[i] = fact[i - 1] * i; 
  }
  auto calc = [&](double Prob) { 
    vector<double>dyn(1 << N); 
    double ret = 0; 
    for(int mask = (1 << N) - 1; mask >= 0; mask--) {
      if(mask & 1) { 
        int bitCount = __builtin_popcount(mask); 
        dyn[mask] = sum[mask] - Prob * bitCount; 
        if(mask < (1 << N) - 1) { 
          double sumExp = 0;
          for(int i = 0; i < N; i++) { 
            if(mask & (1 << i)) continue; 
            sumExp += 1. / (N - bitCount) * dyn[mask ^ (1 << i)]; 
          }
          dyn[mask] = max(dyn[mask], sumExp); 
        }
        ret += fact[bitCount - 1] * fact[N - bitCount] * dyn[mask]; 
      }
    }
    return ret; 
  };
  double lo = 0.0, hi = (1 << 20); 
  for(int _ = 0; _ < 80; _++) { 
    double mid = (lo + hi) / 2;
    if(calc(mid) > 0) lo = mid;
    else hi = mid; 
  } 
  cout << fixed << setprecision(10) << lo << '\n'; 
  return 0; 
}