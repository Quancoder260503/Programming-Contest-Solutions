#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int T; 
  cin >> T; 
  for(int iter = 0, N, Q; iter < T; iter++) { 
    cin >> N; 
    vector<int>x(N), h(N), last(N);
    vector<int64_t>prefix(N); 
    stack<int>stk; 
    for(int i = 0; i < N; i++) { 
      cin >> x[i]; 
    }
    for(int i = 0; i < N; i++) {
      cin >> h[i];  
      prefix[i] = (i ? prefix[i - 1] : 0) + h[i]; 
    }
    for(int i = 0; i < N; i++) { 
      while(sz(stk) && h[stk.top()] < h[i]) { stk.pop(); }
      last[i] = (sz(stk) ? stk.top() : -1); 
      stk.push(i); 
    }
    vector<int64_t>dyn(N); 
    auto range = [&](int L, int R) { 
      if(L > R) return 0LL; 
      return prefix[R] - (L ? prefix[L - 1] : 0); 
    }; 
    for(int i = 0; i < N; i++) { 
      if(last[i] == -1) { 
        dyn[i] = 1LL * x[i] * h[i] - range(0, i - 1); 
      }
      else { 
        dyn[i] = dyn[last[i]] + 1LL * (x[i] - x[last[i]] - 1) * h[i] - range(last[i] + 1, i - 1);  
      }
    }
    cin >> Q; 
    for(int q = 0; q < Q; q++) { 
      int64_t x; 
      cin >> x; 
      int pos = lower_bound(dyn.begin(), dyn.end(), x) - dyn.begin();
      cout << pos << '\n'; 
    }
  } 
  return 0; 
}

