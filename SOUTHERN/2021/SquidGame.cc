#include <bits/stdc++.h>

using namespace std; 

int main() {
  int N, k, s;
  cin >> N; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  } 
  cin >> k >> s; 
  sort(a.begin(), a.end(), [&](int x, int y) { 
    return abs(x - s) < abs(y - s); 
  }); 
  int dist = abs(k - s); 
  int ret = 0; 
  for(int i = 0; i < N; i++) { 
    if(abs(a[i] - s) < dist) { 
      dist = dist - abs(a[i] - s); 
      ret++; 
    } 
    else break; 
  } 
  cout << ret << '\n'; 
  return 0; 
}