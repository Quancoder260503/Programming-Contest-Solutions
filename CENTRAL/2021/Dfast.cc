#include "bits/stdc++.h"
using namespace std;
template <const int64_t mod, const int64_t maxf>
struct NTT {
  NTT() {
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

 private:
  int64_t rts[maxf + 1];
  int64_t bitrev[maxf];
  int64_t iv[maxf + 1];

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
};
template <typename T>
struct CRT {
  T res;

  CRT() { res = 0, prd = 1; }

  // Add condition: res % p == r
  void add(T p, T r) {
    res += mul(r - res % p + p, euclid(prd, p).first + p, p) * prd;
    prd *= p;
    if (res >= prd) res -= prd;
  }

 private:
  T prd;
  T mul(T a, T b, T p) {
    a %= p, b %= p;
    T q = (T)((long double)a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
  }
  pair<T, T> euclid(T a, T b) {
    if (!b) return make_pair(1, 0);
    pair<T, T> r = euclid(b, a % b);
    return make_pair(r.second, r.first - a / b * r.second);
  }
};
const int64_t MOD0 = 1004535809;  // 2^21 * 479 + 1
const int64_t MOD1 = 1012924417;  // 2^21 * 483 + 1
const int64_t MOD2 = 998244353;   // 2^20 * 476 + 1
NTT<MOD0, 1 << 21> NTTA;
NTT<MOD1, 1 << 21> NTTB;
signed main(void) {
  clock_t tStart = clock();
  int64_t N, M, X, Y;
  while (cin >> N >> M >> X >> Y) {
    vector<vector<int64_t>> g(N, vector<int64_t>(M));
    vector<vector<int64_t>> image(X, vector<int64_t>(Y));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cin >> g[i][j];
      }
    }
    for (int i = 0; i < X; i++) {
      for (int j = 0; j < Y; j++) {
        cin >> image[i][j];
      }
    }
    vector<int64_t> polyA(2 * N * M), polyB(2 * N * M);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        polyA[2 * i * M + j] = g[i][j];
      }
    }
    for (int i = 0; i < X; i++) {
      for (int j = 0; j < Y; j++) {
        polyB[2 * M * (X - i - 1) + (Y - j - 1)] = image[i][j];
      }
    }
    auto retA = NTTA.multiply(polyA, polyB);
    auto retB = NTTB.multiply(polyA, polyB);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int at = (i + (X - 1) / 2) * 2 * M + (j + (Y - 1) / 2);
        CRT<int64_t> crt;
        crt.add(MOD0, retA[at]);
        crt.add(MOD1, retB[at]);
        cout << crt.res << " ";
      }
      cout << '\n';
    }
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart) /
    // CLOCKS_PER_SEC);
  }
  return 0;
}
/*
1280 2020 2410 2800 1840
2760 4110 4560 5010 3180
4410 6360 6810 7260 4530
6060 8610 9060 9510 5880
3200 4360 4570 4780 2800

94 154 106
186 285 186
285 420 267
384 555 348
202 280 166

*/