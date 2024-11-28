#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int mod = 1e9 + 7; 

string L, R;
pair<double, int64_t>best[100005][2][2][2]; 

pair<double, int64_t> memo(int pos, int isStart, int isGreater, int isSmaller) { 
  if(pos == sz(R)) return {0, 1}; 
  pair<double, int64_t> &ret = best[pos][isStart][isGreater][isSmaller]; 
  if(ret.first >= 0) return ret; 
  ret = {0, 0}; 
  int maxBound = (isSmaller ? 9 : R[pos] - '0');
  int minBound = (isGreater ? 1 : max(1, L[pos] - '0'));
  if(L[pos] - '0' == 0 && !isStart) { 
    ret = memo(pos + 1, isStart, isGreater, true); 
  } 
  for(int nextDigit = minBound; nextDigit <= maxBound; nextDigit++) { 
    auto nextState = memo(pos + 1, true, isGreater || (nextDigit > L[pos] - '0'), 
                                         isSmaller || (nextDigit < R[pos] - '0')); 
    if(ret.first < nextState.first + log(nextDigit)) { 
      ret.first = nextState.first + log(nextDigit); 
      ret.second = nextState.second % mod * nextDigit % mod; 
    }
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> L >> R;
  reverse(L.begin(), L.end()); 
  while(sz(L) < sz(R)) L.push_back('0'); 
  for(int i = 0; i < 100005; i++) { 
    for(int j = 0; j < 2; j++) {
      for(int k = 0; k < 2; k++) {
        best[i][j][k][0] = best[i][j][k][1] = {-1, -1}; 
      }
    }
  }
  reverse(L.begin(), L.end()); 
  int64_t ret = memo(0, false, false, false).second; 
  cout << ret << '\n'; 
  return 0; 
}
