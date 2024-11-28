#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()

bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa,
         vector<int>& A, vector<int>& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (int b : g[a])
    if (B[b] == L + 1) {
      B[b] = 0;
      if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
        return btoa[b] = a, 1;
    }
  return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
  int res = 0;
  vector<int> A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    /// Find the starting nodes for BFS (i.e. layer 0).
    cur.clear();
    for (int a : btoa)
      if (a != -1) A[a] = -1;
    for (int a = 0; a < sz(g); a++)
      if (A[a] == 0) cur.push_back(a);
    /// Find all layers using bfs.
    for (int lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (int a : cur)
        for (int b : g[a]) {
          if (btoa[b] == -1) {
            B[b] = lay;
            islast = 1;
          } else if (btoa[b] != a && !B[b]) {
            B[b] = lay;
            next.push_back(btoa[b]);
          }
        }
      if (islast) break;
      if (next.empty()) return res;
      for (int a : next) A[a] = lay;
      cur.swap(next);
    }
    for (int a = 0; a < sz(g); a++) {
      res += dfs(a, 0, g, btoa, A, B);
    }
  }
  return res;
}

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

int N, M; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> M; 
  vector<vector<int>>g(N); 
  vector<vector<int>>adj(2 * N); 
  map<pair<int, int>, int>counter; 
  for(int i = 0, u, v; i < M; i++) { 
    cin >> u >> v; 
    --u, --v; 
    g[v].push_back(u);
    adj[u].push_back(N + v); 
    counter[{u, N + v}]++; 
  }
  vector<int>atob(N, -1);
  int cc = hopcroftKarp(g, atob); 
  assert(cc == N); 
  for(int i = 0; i < N; i++) { 
    atob[i] += N; 
  }
  g.resize(2 * N); 
  for(int i = 0; i < 2 * N; i++) { 
    g[i].clear(); 
  }
  for(int u = 0; u < N; u++) { 
    g[atob[u]].push_back(u); 
    for(auto v : adj[u]) if(v != atob[u] || counter[{u, v}] > 1) { 
      g[u].push_back(v); 
      counter[{u, v}]--; 
    }
  }
  DirectedDfs scc(g); 
  int ret = M - N;
  for(int i = 0; i < N; i++) { 
    ret += (scc.comp_ids[i] == scc.comp_ids[atob[i]]); 
  }
  cout << ret << '\n';  
  return 0; 
}

