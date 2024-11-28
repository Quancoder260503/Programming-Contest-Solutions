#include<bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
  int R, C; 
  cin >> R >> C; 
  vector<vector<int>>g(R, vector<int>(C)); 
  for(int i = 0; i < R; i++) { 
   for(int j = 0; j < C; j++) { 
    cin >> g[i][j]; 
    g[i][j]--; 
   } 
  } 
  auto cmp = [&](vector<int>&a, vector<int>&b) -> int { 
    for(int i = 0; i < sz(a); i++) { 
      if(a[i] != b[i]) return a[i] < b[i]; 
    } 
    return 0; 
  }; 
  vector<vector<int>>ret = g; 
  vector<vector<int>>b(R, vector<int>(C)); 
  vector<int>col(C); 
  for(int i = 0; i < R; i++) { 
   for(int j = 0; j < C; j++) { 
    col[j] = C - 1 - g[i][j]; 
   } 
   for(int r = 0; r < R; r++) { 
    for(int c = 0; c < C; c++) { 
     b[r][col[c]] = g[r][c]; 
    } 
   }
   sort(b.rbegin(), b.rend(), cmp); 
   if(b > ret) ret = b; 
  } 
  int x, y, Q; 
  cin >> Q; 
  while(Q--) { 
    cin >> x >> y; 
    cout << ret[--x][--y] + 1 << '\n'; 
  } 
  return 0; 
}