#include "bits/stdc++.h"


#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

using namespace std; 

#define sz(x) int (x.size())

const int mod = 998244353;
const int maxf = 1e5 + 10; 

struct DirectedDfs {
  vector<vector<int>> g;
  int n;
  vector<int> num, low, current, S;
  int counter;
  vector<int> comp_ids;
  vector<vector<int>> scc;

  DirectedDfs(const vector<vector<int>>& _g)
      : g(_g),
        n(g.size()),
        num(n, -1),
        low(n, 0),
        current(n, 0),
        counter(0),
        comp_ids(n, -1) {
    for (int i = 0; i < n; i++) {
      if (num[i] == -1) dfs(i);
    }
  }

  void dfs(int u) {
    low[u] = num[u] = counter++;
    S.push_back(u);
    current[u] = 1;
    for (auto v : g[u]) {
      if (num[v] == -1) dfs(v);
      if (current[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
      scc.push_back(vector<int>());
      while (1) {
        int v = S.back();
        S.pop_back();
        current[v] = 0;
        scc.back().push_back(v);
        comp_ids[v] = ((int)scc.size()) - 1;
        if (u == v) break;
      }
    }
  }

  // build DAG of strongly connected components
  // Returns: adjacency list of DAG
  std::vector<std::vector<int>> build_scc_dag() {
    std::vector<std::vector<int>> dag(scc.size());
    for (int u = 0; u < n; u++) {
      int x = comp_ids[u];
      for (int v : g[u]) {
        int y = comp_ids[v];
        if (x != y) {
          dag[x].push_back(y);
        }
      }
    }
    return dag;
  }
};

vector<vector<int>>graph; 
int64_t ways[maxf]; 

void dfs(int u) {
  ways[u] = 1; 
  for(auto v : graph[u]) {
    dfs(v); 
    ways[u] = ways[u] % mod * (ways[v] + 1) % mod; 
  }
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  while(cin >> N && N) {
    vector<vector<int>>g(N); 
    int64_t pw = 1; 
    vector<int>cannotGo(N, -1); 
    for(int i = 0, x; i < N; i++) { 
      cin >> x;
      pw = pw * 2 % mod;
      if(x < 0) {
        cannotGo[i] = true; 
        continue; 
      }
      g[x - 1].push_back(i);
    }
    function<void(int)> doit = [&](int u) { 
      if(cannotGo[u] != -1) return; 
      cannotGo[u] = true; 
      for(auto v : g[u]) { 
        doit(v); 
      }
      return; 
    }; 
    for(int i = 0; i < N; i++) { 
      if(cannotGo[i] == true) { 
        for(auto v : g[i]) { 
          doit(v); 
        } 
      }
    }
    for(int i = 0; i < N; i++) { 
      if(cannotGo[i] == true) { 
        g[i].clear(); 
      }
    }
    DirectedDfs Scc(g);
    graph = Scc.build_scc_dag(); 
    vector<int>in(sz(graph), 0); 
    for(int i = 0; i < sz(graph); i++) { 
     for(auto v : graph[i]) { 
      in[v]++; 
     }
    }
    vector<int>canStart(sz(graph), true); 
    for(int i = 0; i < N; i++) { 
      if(cannotGo[i] == true) { 
        canStart[Scc.comp_ids[i]] = false; 
      }
    }
    int64_t ret = 1; 
    for(int i = 0; i < sz(graph); i++) { 
      if(in[i] || !canStart[i]) continue;
      dfs(i);
      ret = ret % mod * (1 + ways[i]) % mod;  
    } 
    ret = (pw - ret + mod) % mod; 
    cout << ret << '\n';  
  }
  return 0; 
}