#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Q; 
  cin >> Q; 
  for(int iter = 0, N, M; iter < Q; iter++) { 
    cin >> N >> M; 
    vector<int>a(N), l(N), r(N);
    vector<int64_t>prefix(N);  
    for(int i = 0; i < N; i++) { 
      cin >> a[i]; 
      prefix[i] = (i ? prefix[i - 1] : 0) + a[i]; 
    }
    stack<int>stk;
    for(int i = 0; i < N; i++) { 
      while(sz(stk) && a[stk.top()] > a[i]) { 
        stk.pop(); 
      }
      l[i] = (sz(stk) ? stk.top() : -1); 
      stk.push(i);  
    }
    while(stk.size()) stk.pop(); 
    for(int i = N - 1; i >= 0; i--) { 
      while(sz(stk) && a[stk.top()] > a[i]) { 
        stk.pop(); 
      }
      r[i] = (sz(stk) ? stk.top() : -1); 
      stk.push(i);  
    }
    auto sum_range = [&](int L, int R) {
      if(L > R) return 0LL;  
      return prefix[R] - (L ? prefix[L - 1] : 0); 
    };
    int64_t ret = 0; 
    for(int i = 0; i < N; i++) { 
      if(a[i] != M) continue; 
      if(l[i] != -1 && r[i] != -1) { 
        ret = max(ret, sum_range(l[i] + 1, r[i] - 1)); 
      }
      else if(l[i] != -1) { 
        ret = max(ret, sum_range(l[i] + 1, N - 1)); 
      }
      else if(r[i] != -1) {
        ret = max(ret, sum_range(0, r[i] - 1)); 
      }
      else { 
        ret = max(ret, sum_range(0, N - 1)); 
      }
    }
    cout << ret << '\n'; 
  }
  return 0; 
}
