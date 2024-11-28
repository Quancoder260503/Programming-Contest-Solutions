#include <bits/stdc++.h> 

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, M; 
  cin >> N >> M; 
  vector<vector<char>>g(N, vector<char>(M)); 
  for(int i = 0; i < N; i++) { 
   for(int j = 0; j < M; j++) { 
    cin >> g[i][j]; 
   }
  }
  vector<vector<int>>left(N, vector<int>(M)), right(N, vector<int>(M)); 
  for(int i = 0; i < N; i++) { 
   int last = -1; 
   for(int j = 0; j < M; j++) { 
    left[i][j] = last; 
    if(g[i][j] == '0') { 
      last = j; 
    }
   }
   last = M; 
   for(int j = M - 1; j >= 0; j--) { 
    right[i][j] = last; 
    if(g[i][j] == '0') { 
      last = j; 
    }
   }
  }
  vector<vector<int>>up(N, vector<int>(M)), down(N, vector<int>(M)); 
  for(int j = 0; j < M; j++) { 
   int last = -1; 
    for(int i = 0; i < N; i++) {
      up[i][j] = last; 
      if(g[i][j] == '0') { 
       last = i; 
      } 
    }
    last = N; 
    for(int i = N - 1; i >= 0; i--) {
      down[i][j] = last; 
      if(g[i][j] == '0') { 
        last = i; 
      } 
    } 
  }
  int ret = -1; 
  pair<int, int>pos = {N + 1, M + 1}; 
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
      if(g[i][j] == '0') continue; 
      int goLeft  = j - left[i][j] - 1; 
      int goRight = right[i][j] - j - 1; 
      int goUp    = i - up[i][j] - 1; 
      int goDown  = down[i][j] - i - 1; 
     int amt = min({goLeft, goRight, goUp, goDown}); 
      if(ret < amt) { 
        ret = amt;
        pos = {i, j};  
      }
      else if(ret == amt) { 
        pos = min(pos, {i, j}); 
      } 
    } 
  }
  if(ret == -1) { 
    cout << "-1\n"; 
    return 0; 
  } 
  cout << 4 * ret + 1 << '\n' << pos.first + 1 << " " << pos.second + 1 << '\n'; 
  return 0; 
}
