#include "bits/stdc++.h"
using namespace std;
const int64_t mod = 998244353;
int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (long long)res * tmp % mod;
    }
    tmp = (long long)tmp * tmp % mod;
    k >>= 1;
  }
  return res;
}
template <const int64_t mod, const int64_t maxf>
struct Number_Theoretic_Transfrom {
  Number_Theoretic_Transfrom() {
    int64_t k = 0;
    while ((1 << k) < maxf) k++;
    bitrev[0] = 0;
    for (int64_t i = 1; i < maxf; i++) {
      bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (k - 1));
    }
    int64_t pw = fpow(prt(), (mod - 1) / maxf);
    rts[0] = 1;
    for (int64_t i = 1; i <= maxf; i++) {
      rts[i] = (long long)rts[i - 1] * pw % mod;
    }
    for (int64_t i = 1; i <= maxf; i <<= 1) {
      iv[i] = fpow(i, mod - 2);
    }
  }
  vector<int64_t> multiply(vector<int64_t> a, vector<int64_t> b) {
    static int64_t fa[maxf], fb[maxf], fc[maxf];
    int64_t na = a.size(), nb = b.size();
    for (int64_t i = 0; i < na; i++) fa[i] = a[i];
    for (int64_t i = 0; i < nb; i++) fb[i] = b[i];
    multiply(fa, fb, na, nb, fc);
    int64_t k = na + nb - 1;
    vector<int64_t> res(k);
    for (int64_t i = 0; i < k; i++) res[i] = fc[i];
    return res;
  }
  vector<int64_t> derivative(vector<int64_t> a) {
    int n = a.size();
    vector<int64_t> ret(n - 1);
    for (int i = 1; i < n; i++) {
      ret[i - 1] = 1LL * i % mod * a[i] % mod;
    }
    return ret;
  }
  vector<int64_t> intergral(vector<int64_t> a) {
    int n = a.size();
    vector<int64_t> ret(n + 1, 0);
    for (int i = 1; i < n; i++) {
      ret[i] = 1LL * fpow(i, mod - 2) % mod * a[i - 1] % mod;
    }
    return ret;
  };
  vector<int64_t> get_inverse(vector<int64_t> a, int m) {
    static int64_t fr[maxf], fa[maxf];
    int64_t n = a.size();
    for (int64_t i = 0; i < n; i++) {
      fa[i] = a[i];
    }
    int64_t deg = 1;
    while (deg < m * 2) deg = deg * 2;
    inv(deg, fa, fr);
    vector<int64_t> ret(deg);
    for (int64_t i = 0; i < deg; i++) {
      ret[i] = fr[i];
    }
    return ret;
  }

 private:
  int64_t rts[maxf + 1];
  int64_t bitrev[maxf];
  int64_t iv[maxf + 1];
  int64_t gg[maxf + 1];
  int64_t prt() {
    vector<int64_t> dvs;
    for (int64_t i = 2; i * i < mod; i++) {
      if ((mod - 1) % i) continue;
      dvs.push_back(i);
      if (i * i != mod - 1) dvs.push_back((mod - 1) / i);
    }
    for (int64_t i = 2; i < mod; i++) {
      int64_t flag = 1;
      for (int64_t j = 0; j < (int64_t)dvs.size(); j++) {
        if (fpow(i, dvs[j]) == 1) {
          flag = 0;
          break;
        }
      }
      if (flag) return i;
    }
    assert(0);
    return -1;
  }
  void dft(int64_t a[], int64_t n, int64_t sign) {
    int64_t d = 0;
    while ((1 << d) * n != maxf) d++;
    for (int64_t i = 0; i < n; i++) {
      if (i < (bitrev[i] >> d)) {
        swap(a[i], a[bitrev[i] >> d]);
      }
    }
    for (int64_t len = 2; len <= n; len <<= 1) {
      int64_t delta = maxf / len * sign;
      for (int64_t i = 0; i < n; i += len) {
        int64_t *w = sign > 0 ? rts : rts + maxf;
        for (int64_t k = 0; k + k < len; k++) {
          int64_t &a1 = a[i + k + (len >> 1)], &a2 = a[i + k];
          int64_t t = (long long)*w * a1 % mod;
          a1 = a2 - t;
          a2 = a2 + t;
          a1 += a1 < 0 ? mod : 0;
          a2 -= a2 >= mod ? mod : 0;
          w += delta;
        }
      }
    }
    if (sign < 0) {
      int64_t in = iv[n];
      for (int64_t i = 0; i < n; i++) {
        a[i] = (long long)a[i] * in % mod;
      }
    }
  }
  void multiply(int64_t a[], int64_t b[], int64_t na, int64_t nb, int64_t c[]) {
    static int64_t fa[maxf], fb[maxf];
    int64_t n = na + nb - 1;
    while (n != (n & -n)) n += n & -n;
    for (int64_t i = 0; i < n; i++) fa[i] = fb[i] = 0;
    for (int64_t i = 0; i < na; i++) fa[i] = a[i];
    for (int64_t i = 0; i < nb; i++) fb[i] = b[i];
    dft(fa, n, 1), dft(fb, n, 1);
    for (int64_t i = 0; i < n; i++) fa[i] = (long long)fa[i] * fb[i] % mod;
    dft(fa, n, -1);
    for (int64_t i = 0; i < n; i++) c[i] = fa[i];
  }
  void inv(int64_t deg, int64_t f[], int64_t g[]) {
    if (deg == 1) {
      g[0] = fmod(f[0], mod - 2);
      return;
    }
    inv(deg >> 1, f, g);
    int64_t len = 1;
    while (len < deg * 2) len = len * 2;
    copy(f, f + deg, gg);
    fill(gg + deg, gg + len, 0);
    dft(gg, len, 1);
    dft(g, len, 1);
    for (int64_t i = 0; i < len; i++) {
      g[i] =
          1LL * (2 - 1LL * g[i] % mod * gg[i] % mod + mod) % mod * g[i] % mod;
    }
    dft(g, len, -1);
    fill(g + deg, g + len, 0);
  }
};
Number_Theoretic_Transfrom<mod, 1 << 20> NTT;
signed main(void) {
  int64_t N, M;
  while (cin >> N >> M) {
    vector<int64_t> arr(N);
    for (int64_t i = 0; i < N; i++) {
      cin >> arr[i];
    }
    function<vector<int64_t>(int64_t, int64_t)> doit;
    doit = [&](int64_t L, int64_t R) -> vector<int64_t> {
      if (L == R) {
        return {1, mod - arr[R]};
      }
      int64_t mid = (L + R) / 2;
      return NTT.multiply(doit(L, mid), doit(mid + 1, R));
    };
    auto ret = doit(0, N - 1);
    auto dret = NTT.derivative(ret);
    auto poly_inv = NTT.get_inverse(ret, M);
    auto poly_ing = NTT.intergral(NTT.multiply(poly_inv, dret));
    auto poly = NTT.derivative(poly_ing);
    for (int i = 0; i < M; i++) {
      cout << (mod - poly[i]) % mod << '\n';
    }
  }
  return 0;
}