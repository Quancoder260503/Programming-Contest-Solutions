#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 10; 

vector<int>graph[maxf]; 
int vis[maxf], col[maxf], isBiparte, cnt0, cnt1, cnt; 

void dfs(int u, int c) { 
  vis[u] = true; 
  col[u] = c; 
  (col[u] == 1 ? cnt0 : cnt1)++; 
  cnt++; 
  for(auto v : graph[u]) { 
    if(!vis[v]) {
      dfs(v, c ^ 3);  
    }
    else if(col[u] == col[v]) { 
      isBiparte = false;  
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);   
  int N, M;
  cin >> N >> M; 
  for(int i = 0, u, v; i < M; i++) { 
    cin >> u >> v; 
    --u, --v; 
    graph[u].push_back(v); 
    graph[v].push_back(u); 
  }
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) {
    if(!vis[i]) {
      isBiparte = true; 
      cnt0 = cnt1 = cnt = 0;  
      dfs(i, 1); 
      ret += 1LL * cnt * cnt;
      if(!isBiparte) continue; 
      ret -= 2LL * cnt0 * cnt1;  
    }
  }
  cout << ret << '\n'; 
  return 0; 
}