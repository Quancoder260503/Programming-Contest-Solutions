#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int Q; 
  cin >> Q; 
  for(int iter = 0, N, M, L, S; iter < Q; iter++) { 
    cin >> N >> M >> L >> S; 
    vector<tuple<int, int, int>>edge; 
    for(int i = 0, x; i < S; i++) { 
      cin >> x; 
      edge.push_back({0, N + 1, x}); 
    }
    for(int i = 0, w, u, v; i < M; i++) { 
      cin >> u >> v >> w; 
      edge.push_back({w, u, v}); 
    }
    sort(edge.begin(), edge.end()); 
    vector<int>par(N + 2); 
    iota(par.begin(), par.end(), 0); 
    function<int(int)> F = [&](int u) { 
      return par[u] == u ? u : par[u] = F(par[u]); 
    };
    int64_t ret = 0; 
    for(auto [w, u, v] : edge) { 
      if(F(u) == F(v)) continue; 
      par[F(u)] = F(v); 
      ret += w; 
    }
    cout << ret + 1LL * (N - S) * L << '\n'; 
  }
  return 0; 
}

