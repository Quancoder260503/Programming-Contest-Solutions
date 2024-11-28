#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
const int mod  = 1e9 + 7;
const int maxf = 1e6 + 10;

int64_t fact[maxf], ifact[maxf];

int64_t Comb(int a, int b) {
//  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[a - b] % mod;
}

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init(); 
  int N, M, Q; 
  cin >> Q; 
  for(int iter = 0; iter < Q; iter++) {
    cin >> N; 
    vector<int>w(N); 
    for(int i = 0; i < N; i++) { 
      cin >> w[i]; 
    }
    cin >> M; 
    map<pair<char, int>, int>ctr;
    vector<string>word(M); 
    for(int i = 0; i < M; i++) { 
      cin >> word[i]; 
      ctr[{word[i][0], sz(word[i])}]++; 
    }
    int64_t ret = 0; 
    map<pair<char, int>, int>_cache;
    for(int i = 0; i < M; i++) { 
      if(sz(word[i]) != N) continue; 
      ctr[{word[i][0], sz(word[i])}]--; 
      for(int j = 0; j < sz(word[i]); j++) { 
        _cache[{word[i][j], w[j]}]++; 
      }
      int64_t ways = 1;
      for(const auto &[tup, cc] : _cache) { 
        ways = ways % mod * Comb(ctr[tup], cc) % mod;   
      }
      ret += ways; 
      ret %= mod; 
      _cache.clear(); 
      ctr[{word[i][0], sz(word[i])}]++; 
    }
    cout << ret << '\n'; 
  }
  return 0;
}