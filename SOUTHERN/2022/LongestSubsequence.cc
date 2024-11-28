#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  vector<int>perm(N); 
  for(int i = 0; i < N; i++) { 
    cin >> perm[i]; 
    perm[i]--; 
  }
  vector<int>par(N);
  iota(par.begin(), par.end(), 0); 
  function<int(int)> find = [&](int u) { 
    return u == par[u] ? u : par[u] = find(par[u]); 
  }; 
  for(int i = 0, u, v; i < M; i++) {
    cin >> u >> v;
    --u, --v; 
    if(find(perm[u]) == find(perm[v])) continue; 
    par[find(perm[u])] = find(perm[v]); 
  }
  for(int i = 0; i < N; i++) { 
    par[i] = find(i); 
  }
  vector<int>dyn(N); 
  for(int i = 0; i < N; i++) {
    for(int j = N - 1; j >= 0; j--) {
      if(par[perm[i]] == par[j]) { 
        if(j == 0) { 
          dyn[j] = 1; 
        }
        else if(dyn[j] < dyn[j - 1] + 1) { 
          dyn[j] = dyn[j - 1] + 1; 
        }
      }
    }
    for(int i = 1; i < N; i++) { 
      dyn[i] = max(dyn[i], dyn[i - 1]); 
    }
  }
  int ret = 0; 
  for(int i = 0; i < N; i++) { 
    ret = max(ret, dyn[i]); 
  }
  cout << ret << '\n'; 
  return 0; 
}