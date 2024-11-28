#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 
const int _N = 1e7 + 2; 

int64_t fact[_N], sumFact[_N], ret[_N]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  fact[0] = sumFact[0] = 1; 
  for(int i = 1; i < _N; i++) { 
    fact[i] = fact[i - 1] * i % MOD; 
    sumFact[i] = (sumFact[i - 1] + fact[i]) % MOD; 
  }
  ret[0] = 1; 
  for(int i = 1; i < _N; i++) { 
    ret[i] = (2 * fact[i] % MOD - sumFact[i - 1] + MOD + ret[i - 1]) % MOD; 
  }
  int N, T; 
  cin >> T; 
  while(T--) { 
    cin >> N; 
    cout << (fact[N] + MOD - ret[N - 1]) % MOD << '\n'; 
  }
  return 0; 
}