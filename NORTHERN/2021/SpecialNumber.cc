#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxBound = 200;

const vector<int>digitX = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 
const vector<int>digitY = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 
string s; 
int64_t dyn[20][maxBound][maxBound][10];
int vis[maxBound]; 

int64_t memo(int pos, int sumX, int sumY, int carry) { 
  if(pos == -1) return (carry == 0 && sumX == 0 && sumY == 0); 
  int64_t &ret = dyn[pos][sumX][sumY][carry]; 
  if(ret != -1) return ret;
  ret = 0; 
  for(auto nextY : digitY) {
    for(auto nextX : digitX) { 
      if((nextX + 2 * nextY + carry) % 10 == (s[pos] - '0') && nextX <= sumX && nextY <= sumY) { 
        ret += memo(pos - 1, sumX - nextX, sumY - nextY, (nextX + 2 * nextY + carry) / 10);   
      }
    }
  } 
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);  
  cin >> s;
  for(int i = 2; i < maxBound; i++) { 
    if(vis[i]) continue; 
    for(int j = 2 * i; j < maxBound; j += i) { 
      vis[j] = true;
    }
  }
  memset(dyn, -1, sizeof(dyn)); 
  int64_t ret = 0; 
  for(int sumX = 2; sumX < maxBound; sumX++) {
    if(vis[sumX]) continue;  
    for(int sumY = 2; sumY < maxBound; sumY++) { 
      if(vis[sumY]) continue; 
      ret += memo(sz(s) - 1, sumX, sumY, 0); 
    }
  } 
  cout << ret << '\n'; 
  return 0; 
}

/*
  dyn[pos][sumx][sumy][carry]
*/
