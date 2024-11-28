#include <bits/stdc++.h> 

using namespace std; 

#define int64_t long long 

int main(void) {
  int N;
  cin >> N; 
  map<pair<int, int>, int>countPair; 
  map<int, int>rx, ry; 
  for(int i = 0, x, y; i < N; i++) { 
    cin >> x >> y; 
    rx[x]++, ry[y]++; 
    countPair[{x, y}]++; 
  } 
  int64_t ret = 0; 
  for(auto [_, x] : rx) { 
    ret += 1LL * x * (x - 1) / 2; 
  } 
  for(auto [_, y] : ry) { 
    ret += 1LL * y * (y - 1) / 2; 
  } 
  for(auto [_, xy] : countPair) { 
    ret -= 1LL * xy * (xy - 1) / 2; 
  } 
  cout << ret << '\n'; 
  return 0; 
} 