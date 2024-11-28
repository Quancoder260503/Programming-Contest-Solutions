#include "bits/stdc++.h"
using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int mod = 998244353;
const int PRIMITIVE_ROOT = 3; 
const int max_f = (1 << 21); 

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

void dft(vector<int64_t> &f, const bool inv) {
  const int N = sz(f);  // N must be power of 2.
  if (N == 1) return;
  vector<int64_t> f0(N / 2), f1(N / 2);
  for (int i = 0; i < N / 2; i++) {
    f0[i] = f[i * 2];
    f1[i] = f[i * 2 + 1];
  }
  dft(f0, inv);
  dft(f1, inv);
  int64_t w1 = fpow(PRIMITIVE_ROOT, (mod - 1) / N);
  if (inv) w1 = fpow(w1, mod - 2);
  int64_t w = 1;
  for (int i = 0; i < N; i++) {
    const int i2 = (i < N / 2 ? i : i - N / 2);
    f[i] = (f0[i2] + w * f1[i2]) % mod;
    (w *= w1) %= mod;
  }
}

vector<int64_t> NTT(vector<int64_t> g, vector<int64_t> h) {
  int N = 1;
  while (N < g.size() + h.size() - 1) N *= 2;
  while (g.size() < N) g.push_back(0);
  while (h.size() < N) h.push_back(0);
  dft(g, false);
  dft(h, false);
  vector<int64_t> ff(N);
  for (int i = 0; i < N; i++) {
    ff[i] = (g[i] * h[i]) % mod;
  }
  dft(ff, true);
  int64_t invN = fpow(N, mod - 2);
  for (int i = 0; i < N; i++) {
    (ff[i] *= invN) %= mod;
  }
  return ff;
}

int64_t fact[max_f], ifact[max_f];

int64_t Comb(int a, int b) {
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < max_f; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

vector<int64_t>multiply(vector<int64_t>&a, vector<int64_t>&b) { 
  vector<int64_t>ret(sz(a) + sz(b)); 
  for(int i = 0; i < sz(a); i++) { 
    for(int j = 0; j < sz(b); j++) { 
      ret[i + j] += a[i] % mod * b[j] % mod; 
      ret[i + j] %= mod; 
    }
  }
  return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  init();  
  int N; 
  cin >> N;  
  vector<int64_t>den(max_f >> 1); 
  for(int i = 0; i < sz(den); i++) { 
    den[i] = Comb(i + N - 1, N - 1); 
  }
  vector<int64_t>num(10 * (N - 1) + 1); 
  for(int i = 0; i < N; i++) { 
    num[10 * i] = (i & 1 ? mod - Comb(N - 1, i) : Comb(N - 1, i)); 
  }
  vector<int64_t>ret(11);
  ret[1] = 1, ret[10] = mod - 1; 
  ret = multiply(ret, num);
  ret = NTT(ret, den); 
  int64_t ans = (N == 1); 
  for(int i = 0; i < (9 * N + 1); i++) {
    ans += ret[i] % mod * ret[i] % mod; 
    ans %= mod; 
  }
  cout << ans << '\n'; 
  return 0; 
}