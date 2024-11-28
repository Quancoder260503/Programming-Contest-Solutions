#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int A, B, C, M; 
vector<array<int, 4>>pts; 
using T = array<int, 3>;
vector<pair<T, T>>ret; 

void getZ(int L, int R, int from, int to, int from2, int to2) { 
  for(int i = L, startZ = 1; i <= R; i++) { 
    int last_z = (i == R ? C : pts[i][2]);
    array<int, 3> _from = {from, from2, startZ}; 
    array<int, 3> _to   = {to, to2, last_z}; 
    ret[pts[i][3]] = make_pair(_from, _to);
    startZ = pts[i][2] + 1;   
  }
  return; 
}

void getY(int L, int R, int from, int to) { 
  for(int i = L, last_y = 1; i <= R; i++) { 
    int j = i; 
    while(j + 1 <= R && pts[i][1] == pts[j + 1][1]) { j++; } 
    getZ(i, j, from, to, last_y, (j == R ? B : pts[j][1])); 
    last_y = pts[i][1] + 1; 
    i = j; 
  }  
  return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  while(cin >> A && A > 0) { 
    cin >> B >> C >> M; 
    for(int i = 0; i < M; i++) { 
       int x, y, z; 
       cin >> x >> y >> z; 
       pts.push_back({x, y, z, i});  
    }
    ret.resize(M); 
    sort(pts.begin(), pts.end()); 
    for(int i = 0, last_x = 1; i < sz(pts); i++) { 
      int j = i; 
      while(j + 1 < sz(pts) && pts[i][0] == pts[j + 1][0]) { j++; }
      getY(i, j, last_x, (j + 1 == sz(pts) ? A : pts[j][0])); 
      last_x = pts[i][0] + 1; 
      i = j;  
    }
    cout << "YES\n"; 
    for(int i = 0; i < M; i++) { 
      cout << ret[i].first[0] << " " << ret[i].first[1] << " " << ret[i].first[2] << " "; 
      cout << ret[i].second[0] << " " << ret[i].second[1] << " " << ret[i].second[2] << '\n'; 
    }
    ret.clear(); 
    pts.clear(); 
  }
  return 0; 
}