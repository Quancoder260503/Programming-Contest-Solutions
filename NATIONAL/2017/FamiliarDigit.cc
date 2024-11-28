#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

const int mod = 1e9 + 7; 

int64_t dyn[20][2][2][1 << 10], ifact[12], ways[1 << 10]; 
string S; 

int64_t f(int pos, int is_equal, int mask, int start) { 
  if(pos == sz(S)) return (start && !mask); 
  int64_t &ret = dyn[pos][is_equal][start][mask]; 
  if(ret != -1) return ret; 
  ret = 0; 
  int bound = (is_equal ? S[pos] - '0' : 9); 
  for(int digit = 0; digit <= bound; digit++) { 
    if(digit == 0) { 
      if(!start) { 
        ret += f(pos + 1, false, mask, start); 
        ret %= mod; 
      }
      else {
        if(mask & (1 << digit)) { 
          ret += f(pos + 1, is_equal && (digit == bound), mask ^ (1 << digit), start); 
          ret %= mod; 
        } 
        else { 
          ret += f(pos + 1, is_equal && (digit == bound), mask, start); 
          ret %= mod; 
        }
      }
    } 
    else {
      if(mask & (1 << digit)) { 
        ret += f(pos + 1, is_equal && (digit == bound), mask ^ (1 << digit), true); 
        ret %= mod; 
      } 
      else { 
        ret += f(pos + 1, is_equal && (digit == bound), mask, true); 
        ret %= mod; 
      }   
    }
  }
  return ret;
}

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (long long)res % mod * tmp % mod;
    }
    tmp = (long long)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}


int64_t Comb(int64_t N, int64_t K) { 
  int64_t ret = ifact[K]; 
  for(int64_t x = N - K + 1; x <= N; x++) { 
    ret = 1LL * ret % mod * x % mod;  
  } 
  return ret;
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  ifact[0] = 1; 
  for(int i = 1; i < 12; i++) { 
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod; 
  }
  int Q; 
  cin >> Q; 
  int64_t A, B, ret; 
  for(int iter = 0, K, D; iter < Q; iter++) { 
    cin >> A >> B >> K >> D; 
    A--; 
    ret = 0;
    S = to_string(B);  
    memset(dyn, -1, sizeof(dyn)); 
    for(int mask = 0; mask < (1 << 10); mask++) { 
      ways[mask] = f(0, true, mask, false);
    }
    S = to_string(A); 
    memset(dyn, -1, sizeof(dyn));
    for(int mask = 0; mask < (1 << 10); mask++) { 
      ways[mask] = (mod + ways[mask] - f(0, true, mask, false)) % mod; 
      ways[mask] = Comb(ways[mask], K); 
    } 
    for(int digit = 0; digit < 10; digit++) { 
      for(int mask = 0; mask < (1 << 10); mask++) { 
        if(mask & (1 << digit)) { 
          ways[mask ^ (1 << digit)] = (ways[mask ^ (1 << digit)] - ways[mask] + mod) % mod; 
        }
      }
    }
    for(int mask = 0; mask < (1 << 10); mask++) { 
      if(__builtin_popcount(mask) == D) { 
        ret = (ret + ways[mask]) % mod; 
      }
    }
    cout << ret << '\n';
  }
  return 0; 
}
