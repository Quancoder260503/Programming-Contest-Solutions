#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

struct point { 
  int x, y, z; 
  point() {
    x = y = z = 0; 
    return; 
  }; 
  point(int _x, int _y, int _z) { 
    x = _x, y = _y, z = _z; 
    return; 
  }
}; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int A, B, C, M; 
  while(cin >> A) { 
    if(A == -1) break;
    cin >> B >> C >> M; 
    vector<point>cakes; 
    vector<pair<point, point>>boxes; 
    int ret = true;
    for(int i = 0; i < M; i++) { 
      point p;
      cin >> p.x >> p.y >> p.z; 
      cakes.push_back(p); 
    }
    int64_t volume = 0; 
    for(int i = 0; i < M; i++) { 
      point p1, p2;
      cin >> p1.x >> p1.y >> p1.z;
      cin >> p2.x >> p2.y >> p2.z;
      ret &= (1 <= p1.x && p1.x <= p2.x && p2.x <= A); 
      ret &= (1 <= p1.y && p1.y <= p2.y && p2.y <= B); 
      ret &= (1 <= p1.z && p1.z <= p2.z && p2.z <= C); 
      volume += 1LL * (p2.x - p1.x + 1) * (p2.y - p1.y + 1) * (p2.z - p1.z + 1); 
      ret = ret & ((p1.x <= cakes[i].x && cakes[i].x <= p2.x) && 
                   (p1.y <= cakes[i].y && cakes[i].y <= p2.y) && 
                   (p1.z <= cakes[i].z && cakes[i].z <= p2.z));  
      boxes.push_back({p1, p2});  
    }
    ret = ret & (volume == 1LL * A * B * C);
    for(int i = 0; i < M; i++) { 
      for(int j = i + 1; j < M; j++) { 
        ret = ret & !(max(boxes[i].first.x, boxes[j].first.x) <= min(boxes[i].second.x, boxes[j].second.x) &&
                      max(boxes[i].first.y, boxes[j].first.y) <= min(boxes[i].second.y, boxes[j].second.y) && 
                      max(boxes[i].first.z, boxes[j].first.z) <= min(boxes[i].second.z, boxes[j].second.z)); 
      }                
    }
    cout << (ret ? "YES" : "NO") << '\n'; 
  }
  return 0; 
}

