#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  if(N == 1) { 
    cout << 1 << '\n';
    return 0; 
  }
  vector<vector<char>>g(N, vector<char>(M)); 
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
      cin >> g[i][j];
    }
  }
  vector<vector<int>>dist(N, vector<int>(M, -1)); 
  queue<pair<int, int>>q; 
  q.push({0, 0}); 
  dist[0][0] = 0; 
  while(sz(q)) { 
    auto [x, y] = q.front();
    q.pop(); 
    for(int dirx = -1; dirx <= 1; dirx++) { 
      for(int diry = -1; diry <= 1; diry++) if(dirx * dirx + diry * diry <= 1) { 
        int next_x = x + dirx;
        int next_y = (y + diry + M) % M; 
        if(next_x < 0) continue; 
        if(g[next_x][next_y] == 'M') continue; 
        next_y = (next_y + M - 1) % M; 
        if(g[next_x][next_y] == 'M' || dist[next_x][next_y] >= 0) continue;  
        dist[next_x][next_y] = dist[x][y] + 1; 
        if(next_x + 1 == N) { 
          cout << dist[next_x][next_y] + 1 << '\n'; 
          return 0; 
        }
        q.push({next_x, next_y}); 
      }
    }
  }
  cout << -1 << '\n'; 
  return 0; 
}