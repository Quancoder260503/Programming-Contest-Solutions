#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int R, C;
  cin >> R >> C;
  vector<vector<char>> g(R + 1);
  string s;
  cin.ignore();
  for (int i = 0; i < R + 1; i++) {
    getline(cin, s);
    g[i].resize(sz(s));
    for (int j = 0; j < sz(s); j++) {
      g[i][j] = s[j];
    }
  }
  vector<int>amt(R); 
  for(int i = 0; i < R; i++) { 
    cin >> amt[i]; 
  }
  vector<int> ind(R * C, -1);
  vector<vector<vector<pair<int, int>>>> graph(
      R, vector<vector<pair<int, int>>>(C));
  for (int i = 1; i < R + 1; i++) {
    for (int j = 2; j < 2 * C + 1; j += 2) {
      if (g[i][j] == ' ') {
        graph[i - 1][j / 2 - 1].push_back({i - 1, j / 2});
        graph[i - 1][j / 2].push_back({i - 1, j / 2 - 1});
      }
    }
    for (int j = 1; j < 2 * C + 1; j += 2) {
      if (g[i][j] == ' ' && i < R) {
        graph[i][j / 2].push_back({i - 1, j / 2});
        graph[i - 1][j / 2].push_back({i, j / 2});
      }
    }
  }
  vector<vector<int>>vis(R, vector<int>(C)); 
  auto bfs = [&](int startX, int startY, int id) { 
    vis[startX][startY] = true;
    ind[startX * C + startY] = id; 
    queue<pair<int, int>>q; 
    q.push({startX, startY}); 
    while(sz(q)) { 
      auto [u, v] = q.front();
      q.pop(); 
      for(auto [ni, nj] : graph[u][v]) {
        if(vis[ni][nj]) continue; 
        vis[ni][nj] = true;
        q.push({ni, nj}); 
        ind[ni * C + nj] = id; 
      }
    }
    return; 
  }; 
  int id = 0; 
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if(!vis[i][j]) { 
        bfs(i, j, id++); 
      }
    }
  }
  vector<int>minHeight(id, R + 1), maxHeight(id, -1); 
  for(int i = 0; i < R; i++) {
    for(int j = 0; j < C; j++) {
      minHeight[ind[i * C + j]] = min(minHeight[ind[i * C + j]], i);
      maxHeight[ind[i * C + j]] = max(maxHeight[ind[i * C + j]], i); 
    }
  }
  vector<int64_t>dp(1 << id); 
  for(int row = 0; row < R; row++) {
    for(int num = 0; num < id; num++) {
      for(int mask = 0; mask < (1 << id); mask++) {
        if(mask & (1 << num)) { 
          (dp[mask] += dp[mask ^ (1 << num)]) %= MOD; 
        }
      }
    }
    for(int mask = 0; mask < (1 << id); mask++) { 
      int flag = true; 
      for(int num = 0; num < id; num++) { 
        if(mask & (1 << num)) { 
          if(row < minHeight[num]) { 
            flag = false; 
            break; 
          }
        }
        else { 
          if(row > maxHeight[num]) { 
            flag = false; 
            break; 
          }
        }
      }
      if(!flag) { 
        dp[mask] = 0; 
        continue; 
      }
      int cnt = 0; 
      for(int col = 0; col < C; col++) { 
        if(mask >> ind[row * C + col] & 1) { 
          cnt++; 
        }
      }
      if(amt[row] != -1 && cnt != amt[row]) { 
        dp[mask] = 0; 
        continue; 
      }
      if(row == 0) dp[mask] = 1; 
    }
  }
  int64_t ret = 0; 
  for(int mask = 0; mask < (1 << id); mask++) { 
    (ret += dp[mask]) %= MOD; 
  }
  cout << ret << '\n'; 
  return 0;
}


/*


*/