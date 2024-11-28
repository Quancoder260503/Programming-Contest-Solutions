#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);  
  int n, r, x1, x2;
  cin >> n >> r >> x1 >> x2; 
  for(int i = 0; i < n; i++) { 
    auto c = [&](int x) { 
      if(x1 < x2) { return x + r <= x1; }
      else {return x - r >= x1; }
    }; 
    int x; 
    cin >> x; 
    if(c(x)) { 
      cout << "GOAL\n"; 
      return 0; 
    }
  }
  cout << "NO GOAL\n"; 
  return 0; 
}