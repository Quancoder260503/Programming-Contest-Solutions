#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int N, M; 
const int dx[8] = {-1, 0, 0, 1, -1, -1, 1, 1}; 
const int dy[8] = {0, -1, 1, 0, -1, 1, 1, -1}; 

int solve(void) {
  vector<vector<char>>g(N, vector<char>(M)); 
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
      cin >> g[i][j]; 
    }
  }
  deque<pair<int, int>>dq; 
  vector<vector<int>>memo(N, vector<int>(M, -1)); 
  auto add = [&](int x, int y, int cur_d) { 
    if(g[x][y] == '#') { 
      dq.push_front({x, y}); 
      memo[x][y] = cur_d; 
    }
    else if(g[x][y] == '.') {
      dq.push_back({x, y});  
      memo[x][y] = cur_d + 1; 
    }
    return; 
  }; 
  for(int i = 0; i < N; i++) {
    if(g[i][0] == '@') continue;  
    add(i, 0, 0); 
  }
  for(int i = 0; i < M; i++) { 
    if(g[N - 1][i] == '@') continue; 
    add(N - 1, i, 0); 
  }
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
   //   cout << memo[i][j] << " "; 
    }
    //cout << '\n'; 
  }
  while(sz(dq)) { 
    auto [x, y] = dq.front(); 
    dq.pop_front(); 
    if(x == 0 || y == M - 1) return memo[x][y]; 
    for(int dir = 0; dir < 8; dir++) { 
      int nx = x + dx[dir], ny = y + dy[dir]; 
      if(0 <= nx && nx < N && 0 <= ny && ny < M && g[nx][ny] != '@' && memo[nx][ny] == -1) {
        add(nx, ny, memo[x][y]); 
      }
    }
  }
  return -1; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  while(cin >> N >> M) { 
    if(!N) break; 
    cout << solve() << '\n'; 
  }
  return 0; 
}
