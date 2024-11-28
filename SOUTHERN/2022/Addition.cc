#include "bits/stdc++.h"

using namespace std; 

const int LOG = 10; 
const int oo = 1e9; 

#define ctoi(x) x - '0'

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N; 
  string a, b, c; 
  while(cin >> N) {
    if(!N) break; 
    cin >> a >> b >> c;
    vector<vector<int>>dyn(N + 1, vector<int>(LOG, oo));
    dyn[N][0] = 0;  
    for(int i = N - 1; i >= 0; i--) { 
      for(int j = i + 1; j <= N; j++) { 
        for(int carry = 0; carry < LOG; carry++) { 
          if(dyn[j][carry] == oo) continue; 
          int cc = (ctoi(a[i]) + ctoi(b[i]) + carry); 
          if(cc % 10 == ctoi(c[i])) { 
            dyn[i][cc / 10] = min(dyn[i][cc / 10], dyn[j][carry] + j - i - 1); 
          }
        }
      } 
    }
    int ret = oo; 
    for(int i = 0; i <= N; i++) { 
      ret = min(ret, N - i + dyn[N - i][0]); 
    }
    cout << ret << '\n'; 
  } 
  return 0; 
}