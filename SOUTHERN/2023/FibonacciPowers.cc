#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 2;
const int mod = 998244353;

int64_t finv[maxf];
int64_t fac[maxf];
int64_t inv[maxf];

void binom_init() {
  fac[0] = fac[1] = 1;
  inv[1] = 1;
  finv[0] = finv[1] = 1;
  for (int i = 2; i < maxf; i++) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = mod - mod / i * inv[mod % i] % mod;
    finv[i] = finv[i - 1] * inv[i] % mod;
  }
}
int64_t binom(int64_t n, int64_t r) {
  if (n < r || n < 0 || r < 0) return 0;
  return (fac[n] * finv[r] % mod * finv[n - r] % mod) % mod;
}

struct Zp {
  int64_t a, b;
  Zp(int64_t _a, int64_t _b) : a(_a), b(_b){};
};
Zp operator + (const Zp &alpha, const Zp &theta) {
  return Zp((alpha.a + theta.a) % mod, (alpha.b + theta.b) % mod);
};
Zp operator * (const Zp &alpha, const Zp &theta) {
  return Zp((alpha.a % mod * theta.a % mod + 5 % mod * alpha.b % mod * theta.b % mod) % mod,
            (alpha.a % mod * theta.b % mod + alpha.b % mod * theta.a % mod) % mod);
};
Zp fpow(const Zp &a, int64_t p) {
  auto ret = Zp(1, 0);
  auto tmp = a;
  while (p) {
    if (p & 1) ret = ret * tmp;
    p = p / 2;
    tmp = tmp * tmp;
  }
  return ret;
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

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int64_t N, K;
  binom_init();
  while (cin >> N >> K) {
    int sign = 1;
    auto res = Zp(0, 0);
    auto alpha = Zp(inv[2], inv[2]);
    auto theta = Zp(inv[2], mod - inv[2]);
    for (int j = 0; j <= K; j++) {
      auto beta = fpow(alpha, K - j) * fpow(theta, j);
      Zp ret(0, 0);  
      if(beta.a == 1 && beta.b == 0) { 
        ret = Zp((N + 1) % mod, 0); 
      }
      else { 
        Zp num = fpow(beta, N + 1); 
        num.a = (num.a + mod - 1) % mod; 
        Zp denom = beta; 
        denom.a = (denom.a + mod - 1) % mod; 
        denom.b = (mod - denom.b) % mod; 
        ret = num * denom;
        int64_t cden = fpow((denom.a % mod * denom.a % mod - 5 % mod * denom.b % mod * denom.b % mod + mod) % mod, mod - 2);
        ret.a = ret.a % mod * cden % mod; 
        ret.b = ret.b % mod * cden % mod; 
      }
      ret.a = (mod + ret.a % mod * binom(K, j) % mod * sign % mod) % mod;
      ret.b = (mod + ret.b % mod * binom(K, j) % mod * sign % mod) % mod;
      sign = sign * (-1);
      res = res + ret;
    }
    auto den = Zp(0, 1);
    den = fpow(den, K);
    if (den.a == 0) {
      int64_t ret = fpow(den.b, mod - 2) % mod * res.b % mod;
      cout << ret << '\n';
    } else if (den.b == 0) {
      int64_t ret = fpow(den.a, mod - 2) % mod * res.a % mod;
      cout << ret << '\n';
    }
  }
  // printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
  return 0;
}
/*
   This is the correct solution
   To optimize the runtime, we can treat (a, b) where Zp(a + bsqrt(5)) as a pair
   instead of defining it.
*/