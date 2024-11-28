#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int mod = 1e9 + 7;
const int maxf = 1e5 + 2;

int mark[maxf];
int64_t fact[maxf], ifact[maxf]; 
vector<int> primes;

void sieve(void) {
  for (int64_t i = 2; i < maxf; ++i) {
    if (!mark[i]) {
      primes.emplace_back(i);
      for (int64_t j = i * i; j < maxf; j += i) {
        mark[j] = true;
      }
    }
  }
  return;
}

vector<vector<int64_t>> segmentedSieve(int64_t L, int64_t R) {
  vector<vector<int64_t>> primeSet(R - L + 1);
  for (int64_t i : primes) {
    for (int64_t j = max(1LL * i * i, (L + i - 1) / i * i); j <= R; j += i) {
      primeSet[j - L].push_back(i);
    }
  }
  return primeSet;
}

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
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
  int Q;
  cin >> Q;
  sieve();
  init(); 
  for (int iter = 0; iter < Q; iter++) {
    int64_t A, B;
    cin >> A >> B;
    vector<vector<int64_t>> g = segmentedSieve(A, B);
    vector<int> ctr(sz(g));
    int counter = 0;
    for (int i = 0; i < sz(g); i++) {
      int64_t num = A + i;
      for (int64_t d : g[i]) {
        while (num % d == 0) {
          num = num / d;
          ctr[i]++;
        }
      }
      if (num > 1) {
        ctr[i]++;
      }
      counter += (ctr[i] == 1);
    }
    int64_t ret = 0; 
    for (int choose = 1; choose <= counter; choose += 2) { 
      ret = (ret + Comb(counter, choose)) % mod; 
    } 
    int N = sz(g); 
    vector<vector<vector<int64_t>>>dyn(N + 1, vector<vector<int64_t>>(2, vector<int64_t>(1 << 6)));
    dyn[0][0][0] = 1; 
    for(int i = 0; i < N; i++) {
      for(int one = 0; one < 2; one++) { 
        for(int sum = 0; sum < (1 << 6); sum++) { 
           (dyn[i + 1][one][sum] += dyn[i][one][sum]) %= mod; 
           (dyn[i + 1][one || (ctr[i] > 1)][sum ^ ctr[i]] += dyn[i][one][sum]) %= mod;  
        }
      } 
    }
    ret = (ret + dyn[N][true][0]) % mod; 
    cout << ret << '\n'; 
  }
  return 0;
}
/*
  dyn[i][one][xor_sum] = {number of configurations of the first-ith piles that have included number larger than 1 and have 
                          the xor sum among all pipes equals xor_sum}

*/