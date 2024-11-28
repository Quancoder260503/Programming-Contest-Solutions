/**
 * @file ExpectedValue.cc
 * @author Minh Quan Le
 * @brief Problem E 
 * @version 0.1
 * @date 2024-10-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

template <int N>
struct MultiplicativeFunction {
  MultiplicativeFunction() {
    // Init sieve
    for (int i = 2; i * i < N; i++) {
      if (!sieve[i]) {
        for (int j = i * i; j < N; j += i) {
          sieve[j] = i;
        }
      }
    }
    for (int i = 2; i < N; i++) {
      if (!sieve[i]) {
        pk[i] = {i, 1};
      } else {
        int p = sieve[i];

        if (pk[i / p].first == p) {  // i = p^k
          pk[i] = {p, pk[i / p].second + 1};
        } else {
          pk[i] = {-1, 0};
        }
      }
    }
  }
  array<int, N> divisors() {
    array<int, N> res;
    res[1] = 1;

    for (int i = 2; i < N; i++) {
      if (pk[i].first > 0) {  // i = p^k
        res[i] = pk[i].second + 1;
      } else {
        // i = u * v, gcd(u, v) = 1
        int u = i, v = 1;
        int p = sieve[i];
        while (u % p == 0) {
          u /= p;
          v *= p;
        }
        res[i] = res[u] * res[v];
      }
    }

    return res;
  }
  array<int, N> mobius() {
    array<int, N> res;
    res[1] = 1;

    for (int i = 2; i < N; ++i) {
      if (pk[i].first > 0) {  // i = p^k
        res[i] = (pk[i].second >= 2) ? 0 : -1;
      } else {
        // i = u * v, gcd(u, v) = 1
        int u = i, v = 1;
        int p = sieve[i];
        while (u % p == 0) {
          u /= p;
          v *= p;
        }
        res[i] = res[u] * res[v];
      }
    }
    return res;
  }
  array<int, N> sieve = {0};
  array<pair<int, int>, N> pk;
};

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

void bruteForce(int n) {
  vector<int>a(n); 
  iota(a.begin(), a.end(), 1);
  int sum = 0, perm = 0; 
  do { 
    int g = a[0]; 
    set<int>ms{g}; 
    for(int i = 1; i < sz(a); i++) { 
      g = gcd(g, a[i]); 
      ms.insert(g); 
    }
    sum += sz(ms); 
    perm++; 
  }
  while(next_permutation(a.begin(), a.end())); 
  sum = sum % MOD * mod_inv(perm, MOD) % MOD; 
  cout << sum << '\n'; 
  return; 
}

MultiplicativeFunction<200001>phi; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int64_t>fact(N + 1), ifact(N + 1); 
  fact[0] = ifact[0] = 1; 
  for(int i = 1; i < N + 1; i++) { 
    fact[i] = fact[i - 1] % MOD * i % MOD;
  }
  ifact.back() = mod_inv(fact.back(), MOD); 
  for(int i = N - 1; i > 0; i--) { 
    ifact[i] = ifact[i + 1] % MOD * (i + 1) % MOD; 
  }
  auto Comb = [&](int n, int k) -> int64_t { 
    if(n < k) return 0; 
    return fact[n] % MOD * ifact[k] % MOD * ifact[n - k] % MOD; 
  }; 
  vector<int64_t>ways(N + 1); 
  for(int i = 2; i <= N; i++) { 
   for(int j = 1; j <= N / i; j++) { 
    (ways[i] += Comb(N / i, j) % MOD * fact[j] % MOD * fact[N - j - 1] % MOD) %= MOD; 
   }
  }
  auto mobius = phi.mobius(); 
  vector<int64_t>g(N + 1);
  int64_t ret = 0;  
  for(int x = N; x > 1; x--) {
   for(int j = x; j <= N; j += x) { 
     (g[x] += MOD + mobius[j / x] % MOD * ways[j] % MOD) %= MOD; 
   }
   (ret += g[x] % MOD * fact[N - N / x] % MOD * ifact[N - 1 - N / x] % MOD) %= MOD; 
//   cout << ret << '\n'; 
  }
  (ret += fact[N]) %= MOD; 
  ret = ret % MOD * ifact[N] % MOD; 
  // bruteForce(N); 
  cout << ret << '\n';  
  return 0;
}