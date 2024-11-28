#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 998244353;
const int PRIMITIVE_ROOT = 3;
const int LOG = 20; 

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

template <int mod, int root, int maxf>
struct NTT {
  vector<int64_t>rt, out; 
  NTT() { 
    int s = 32 - __builtin_clz(maxf - 1), n = (1 << s); 
    rt.resize(n); 
    rt[0] = rt[1] = 1; 
    for (int k = 2, s = 2; k < n; k *= 2, s++) {
      int64_t z[] = {1, mod_pow(root, mod >> s, mod)};
      for(int i = k; i < 2 * k; i++) { 
        rt[i] = rt[i / 2] % mod * z[i & 1] % mod;
      } 
    }
  }
  void ntt(vector<int64_t> &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    vector<int> rev(n);
    for(int i = 0; i < n; i++) { 
      rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    }
    for(int i = 0; i < n; i++) { 
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
      for (int i = 0; i < n; i += 2 * k) { 
        for(int j = 0; j < k; j++) {
          int64_t z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
          a[i + j + k] = ai - z + (z > ai ? mod : 0);
          ai += (ai + z >= mod ? z - mod : z);
        } 
      }
    } 
  }
  vector<int64_t> conv(const vector<int64_t> &a, const vector<int64_t>  &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    int inv = mod_pow(n, mod - 2, mod);
    out.resize(n); 
    vector<int64_t> L(a), R(b);
    L.resize(n); 
    R.resize(n); 
    ntt(L), ntt(R);
    for(int i = 0; i < n; i++) { 
      out[-i & (n - 1)] = 1LL * L[i] * R[i] % mod * inv % mod;
    } 
    ntt(out);
    return {out.begin(), out.begin() + s};
  }
};

NTT<MOD, PRIMITIVE_ROOT, 1 << LOG>ntt; 

vector<int64_t> polyInv(vector<int64_t>&g) { 
  vector<int64_t>ret = {mod_pow(g[0], MOD - 2, MOD)}; 
  while(sz(ret) < sz(g)) { 
    vector<int64_t>gCut(g.begin(), g.begin() + min(sz(g), sz(ret) * 2)); 
    vector<int64_t> x = ntt.conv(ntt.conv(ret, ret), gCut); 
    ret.resize(sz(ret) * 2); 
    for(int i = sz(ret) / 2; i < min(sz(x), sz(ret)); i++) { 
      ret[i] = (MOD + x[i]) % MOD; 
    }
  }
  ret.resize(sz(g)); 
  return ret; 
}

vector<int64_t> polyDerivative(vector<int64_t>g) { 
  for(int i = 0; i < sz(g); i++) { 
    g[i] = g[i] % MOD * i % MOD;  
  }
  g.erase(g.begin()); 
  return g; 
}

vector<int64_t> polyIntegrate(vector<int64_t>g) { 
  for(int i = 0; i < sz(g); i++) { 
    g[i] = g[i] % MOD * mod_pow(i + 1, MOD - 2, MOD) % MOD; 
  }
  g.insert(g.begin(), 0); 
  return g; 
}
 
vector<int64_t>polyLog(vector<int64_t>&g) { 
  if(sz(g) == 1) return {0}; 
  vector<int64_t> ret = polyIntegrate(ntt.conv(polyDerivative(g), polyInv(g))); 
  ret.resize(sz(g)); 
  return ret; 
}

vector<int64_t>polyExp(vector<int64_t>&g) { 
  vector<int64_t>ret = {1}; 
  while(sz(ret) < sz(g)) { 
    vector<int64_t> x(g.begin(), g.begin() + min(sz(g), sz(ret) * 2)); 
    x[0] = 1; 
    ret.resize(sz(ret) * 2); 
    vector<int64_t>logP = polyLog(ret); 
    for(int i = 0; i < sz(x); i++) { 
      (x[i] += MOD - logP[i]) %= MOD; 
    }
    ret.resize(sz(ret) / 2); 
    x = ntt.conv(ret, x); 
    ret.resize(sz(ret) * 2); 
    for(int i = sz(ret) / 2; i < sz(ret); i++) { 
      ret[i] = x[i]; 
    }
  }
  ret.resize(sz(g)); 
  return ret;
}

vector<int64_t> polyDiv(vector<int64_t> a, vector<int64_t> b) { 
  int n = sz(a), m = sz(b); 
  if(n < m) return {}; 
  reverse(a.begin(), a.end()); 
  reverse(b.begin(), b.end()); 
  b.resize(n - m + 1); 
  a = ntt.conv(a, polyInv(b)); 
  a.erase(a.begin() + n - m + 1, a.end());
  reverse(a.begin(), a.end()); 
  return a;  
}


int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  vector<int64_t>inv(1 << LOG); 
  for(int i = 1; i < sz(inv); i++) { 
    inv[i] = mod_pow(i, MOD - 2, MOD); 
  }
  int N, D;
  cin >> N >> D;
  int maxBound = 250000; 
  if(1LL * maxBound > 1LL * N * (N - 1) / 2) { 
    maxBound = N * (N - 1) / 2; 
  }
  vector<int64_t>num(maxBound + 1); 
  for(int i = 1; i <= N; i++) { 
    for(int j = 1; i * j < maxBound + 1; j++) { 
      (num[i * j] += MOD - inv[j]) %= MOD; 
    }
  }
  for(int i = 1; i < maxBound + 1; i++) { 
    (num[i] += inv[i] % MOD * N % MOD) %= MOD; 
  } 
  vector<int64_t> ret = polyExp(num);
  for(int i = 1; i <= maxBound; i++) { 
   if(i < sz(ret)) { 
    cout << ret[i] << '\n'; 
   } 
   else { 
    cout << 0 << '\n'; 
   }
  }
  return 0; 
}