#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Q; 
  cin >> Q; 
  for(int iter = 0; iter < Q; iter++) { 
    int xa, ya, xb, yb; 
    cin >> xa >> ya >> xb >> yb; 
    int64_t dx = abs(xa - xb), dy = abs(ya - yb);
    cout << 2 * max(dx, dy) - (max(dx, dy) - min(dy, dx)) % 2 << '\n';  
  }
  return 0; 
}
