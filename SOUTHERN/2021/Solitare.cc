#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

struct FT {
  int N;
  vector<int> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int query(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c + bit[i];
    }
    return c;
  }
  int query(int l, int r) { 
    int64_t ret = query(r) - query(l - 1); 
    if(l > r) ret += query(N - 1); 
    return ret; 
  } 
  void update(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = dif + bit[i];
    }
  }
};

int main() {
  int N; 
  cin >> N; 
  vector<int>a(N + 1); 
  vector<int>coord; 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
    coord.push_back(a[i]); 
  }
  sort(coord.begin(), coord.end()); 
  coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
  int M = sz(coord); 
  vector<vector<int>>pos(M + 1); 
  FT fenw(N + 7);
  for(int i = 1; i <= N; i++) { 
    int at = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin() + 1; 
    pos[at].push_back(i);
    fenw.update(i, 1); 
  }
  int64_t ret = 0; 
  for(int key = M, ptr = 1; key > 0; key--) { 
    auto start = lower_bound(pos[key].begin(), pos[key].end(), ptr); 
    for(auto it = start; it != pos[key].end(); it++) { 
      fenw.update(*it, -1); 
      ret += fenw.query(ptr, (*it)); 
      ptr = (*it); 
    } 
    for(auto it = pos[key].begin(); it != start ; it++) { 
      fenw.update(*it, -1); 
      ret += fenw.query(ptr, (*it)); 
      ptr = (*it); 
    } 
  }
  cout << ret << '\n'; 
  return 0;
}