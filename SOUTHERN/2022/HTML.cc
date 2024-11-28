#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  vector<array<int, 4>>colour;
  vector<string>colourName = {"White", "Silver", "Gray", "Black", "Red", "Maroon", 
                              "Yellow", "Olive", "Lime", "Green", "Aqua", "Teal", 
                              "Blue", "Navy", "Fuchsia", "Purple"}; 
  colour.push_back({0, 255, 255, 255}); 
  colour.push_back({1, 192, 192, 192}); 
  colour.push_back({2, 128, 128, 128}); 
  colour.push_back({3, 0, 0, 0}); 
  colour.push_back({4, 255, 0, 0}); 
  colour.push_back({5, 128, 0, 0}); 
  colour.push_back({6, 255, 255, 0}); 
  colour.push_back({7, 128, 128, 0}); 
  colour.push_back({8, 0, 255, 0}); 
  colour.push_back({9, 0, 128, 0}); 
  colour.push_back({10, 0, 255, 255}); 
  colour.push_back({11, 0, 128, 128}); 
  colour.push_back({12, 0, 0, 255}); 
  colour.push_back({13, 0, 0, 128}); 
  colour.push_back({14, 255, 0, 255}); 
  colour.push_back({15, 128, 0, 128}); 
  int rA, rB, rC; 
  while(cin >> rA >> rB >> rC) { 
    if(rA == -1) { 
      break; 
    }
    int64_t ret = LLONG_MAX; 
    for(int i = 0; i < colour.size(); i++) { 
      ret = min(ret, 1LL * (colour[i][1] - rA) * (colour[i][1] - rA) + 
                     1LL * (colour[i][2] - rB) * (colour[i][2] - rB) + 
                     1LL * (colour[i][3] - rC) * (colour[i][3] - rC)); 
    }
    for(int i = 0; i < colour.size(); i++) { 
      int64_t cc =   1LL * (colour[i][1] - rA) * (colour[i][1] - rA) + 
                     1LL * (colour[i][2] - rB) * (colour[i][2] - rB) + 
                     1LL * (colour[i][3] - rC) * (colour[i][3] - rC);
      if(cc == ret) { 
        cout << colourName[colour[i][0]] << '\n'; 
        break; 
      } 
    }
  }
  return 0; 
}