#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e5 + 10; 

#define sz(x) int(x.size())
#define int64_t long long 

const int64_t oo = LLONG_MAX / 10; 

int N;
vector<pair<int, int64_t>>g[maxf]; 
int64_t dyn[maxf][2], inbest[maxf]; 

void dfs(int u, int p) {
  for(int i = 0; i < sz(g[u]); i++) {
    auto [v, w] = g[u][i];  
    if(v == p) continue;
    dfs(v, u); 
    if(dyn[u][0] < dyn[v][0] + w) {
      dyn[u][1] = dyn[u][0];  
      dyn[u][0] = dyn[v][0] + w;
    }
    else if(dyn[u][1] < dyn[v][0] + w) { 
      dyn[u][1] = dyn[v][0] + w; 
    }
  }
  return;
}

void dfs2(int u, int p) {  
 inbest[u] = dyn[u][0] + dyn[u][1]; 
 for (auto [v, w] : g[u]) {
    if (v == p) continue;
    dfs2(v, u);
    inbest[u] = max(inbest[u], inbest[v]); 
  }
  return;
}

void dfs3(int u, int p, int64_t w_out, int64_t max_d, int64_t &ret) { 
  ret = min(ret, llabs(inbest[u] - w_out));
  vector<pair<int64_t, int64_t>>prefix, suffix;
  vector<int64_t>dprefix;
  pair<int64_t, int64_t>best = {0, 0};
  for(int i = 0; i < sz(g[u]); i++) {
    auto [v, w] = g[u][i];  
    if(v == p) continue;
    if(best.first < dyn[v][0] + w) { 
      best.second = best.first; 
      best.first = dyn[v][0] + w; 
    }
    else if(best.second < dyn[v][0] + w) { 
      best.second = dyn[v][0] + w; 
    }
    prefix.push_back(best); 
    dprefix.push_back(inbest[v]); 
  }
  vector<int64_t>dsuffix(dprefix.begin(), dprefix.end()); 
  best = {0, 0}; 
  for(int i = sz(g[u]) - 1; i >= 0; i--) {
    auto [v, w] = g[u][i];  
    if(v == p) continue;
    if(best.first < dyn[v][0] + w) {
      best.second = best.first;  
      best.first = dyn[v][0] + w; 
    }
    else if(best.second < dyn[v][0] + w) { 
      best.second = dyn[v][0] + w; 
    }
    suffix.push_back(best); 
  }
  reverse(suffix.begin(), suffix.end()); 
  for(int i = 1; i < sz(g[u]); i++) { 
    dprefix[i] = max(dprefix[i], dprefix[i - 1]); 
  }
  for(int i = sz(g[u]) - 2; i >= 0; i--) { 
    dsuffix[i] = max(dsuffix[i], dsuffix[i + 1]); 
  }
  for(int i = 0; i < sz(g[u]); i++) {
    auto [v, w] = g[u][i];  
    if(v == p) continue;
    int64_t opt = max_d + w; 
    if(i > 0)             opt = max(opt, w + prefix[i - 1].first); 
    if(i + 1 < sz(g[u]))  opt = max(opt, w + suffix[i + 1].first);
    int64_t opt_sz = max(max_d, w_out); 
    if(i > 0) { 
      opt_sz = max(opt_sz, dprefix[i - 1]); 
      opt_sz = max(opt_sz, prefix[i - 1].first + max(max_d, prefix[i - 1].second)); 
    }
    if(i + 1 < sz(g[u])) { 
      opt_sz = max(opt_sz, dsuffix[i + 1]);
      opt_sz = max(opt_sz, suffix[i + 1].first + max(max_d, suffix[i + 1].second)); 
    } 
    if(0 < i && i + 1 < sz(g[u])) { 
      opt_sz = max(opt_sz, suffix[i + 1].first + prefix[i - 1].first); 
    }    
    dfs3(v, u, opt_sz, opt, ret); 
  }
  return;  
}

void solve(void) {
  for(int i = 1; i <= N; i++) { 
    g[i].clear();
    dyn[i][0] = dyn[i][1] = inbest[i] = 0;
  }
  for(int i = 2, c; i <= N; i++) {
    int64_t x; 
    cin >> c >> x;
    g[c].push_back({i, x}); 
  }
  dfs(1, 0);
  dfs2(1, 0); 
  int64_t ret = oo; 
  dfs3(1, 0, 0, 0, ret); 
  cout << ret << '\n'; 
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  while(cin >> N && N) { 
    solve(); 
  }
  return 0;
}