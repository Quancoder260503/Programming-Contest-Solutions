#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int _N = 1e5 + 10; 

vector<int>g[_N]; 
int maxPathIn[_N], maxPathOut[_N], fa[_N]; 

void dfs(int u, int p) {
  fa[u] = p; 
  for(auto v : g[u]) {
    if(v == p) continue; 
    dfs(v, u); 
    maxPathIn[u] = max(maxPathIn[v] + 1, maxPathIn[u]);    
  } 
  return; 
} 

void dfs2(int u, int p, int maxOut) { 
  maxPathOut[u] = maxOut; 
  vector<int>prefix; 
  vector<int>suffix; 
  for(auto v : g[u]) { 
    if(v == p) continue; 
    prefix.push_back(maxPathIn[v] + 1); 
  }
  suffix = prefix; 
  for(int i = 1; i < sz(prefix); i++) { 
    prefix[i] = max(prefix[i], prefix[i - 1]); 
  } 
  for(int i = sz(suffix) - 2; i >= 0; i--) { 
    suffix[i] = max(suffix[i], suffix[i + 1]); 
  } 
  int ind = 0; 
  for(auto v : g[u]) { 
    if(v == p) continue; 
    dfs2(v, u, 1 + max({maxOut, 
                       ind ? prefix[ind - 1] : 0, 
                       ind + 1 < sz(suffix) ? suffix[ind + 1] : 0})); 
    ind++; 
  } 
  return; 
} 

int main() { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, Q; 
 cin >> N >> Q; 
 for(int i = 0, u, v; i < N - 1; i++) { 
   cin >> u >> v; 
   --u, --v; 
   g[u].push_back(v); 
   g[v].push_back(u); 
 } 
 dfs(0, -1); 
 dfs2(0, -1, 0); 
 vector<vector<int>>pathScore(N); 
 for(int i = 0; i < N; i++) {
  for(auto v : g[i]) { 
    if(v == fa[i]) continue;
    pathScore[i].push_back(1 + maxPathIn[v]); 
  } 
  pathScore[i].push_back(maxPathOut[i]);
  sort(pathScore[i].begin(), pathScore[i].end()); 
 } 
 for(int i = 0, u, v; i < Q; i++) { 
    cin >> u >> v; 
    --u; 
    auto it = lower_bound(pathScore[u].begin(), pathScore[u].end(), v + 1); 
    cout << pathScore[u].end() - it << '\n'; 
 }
 return 0; 
}