/**
 * @file Grouping.cc
 * @author Minh Quan Le 
 * @brief 
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7; 
using type = int64_t; 

struct Matrix {
  vector<vector<type>> data;
  int row() const { return data.size(); }
  int col() const { return data[0].size(); }
  auto &operator[](int i) { return data[i]; }
  const auto &operator[](int i) const { return data[i]; }
  Matrix() = default;

  Matrix(int r, int c) : data(r, vector<type>(c, 0)) {}

  Matrix(const vector<vector<type>> &d) : data(d) {
    assert(d.size());
    int size = d[0].size();
    assert(size);
    for (auto x : d) assert(x.size() == size);
  }
  friend ostream &operator<<(ostream &out, const Matrix &d) {
    for (auto x : d.data) {
      for (auto y : x) out << y << ' ';
      out << '\n';
    }
    return out;
  }
  Matrix operator*(const Matrix &b) {
    Matrix a = *this;
    assert(a.col() == b.row());

    Matrix c(a.row(), b.col());
    for (int i = 0; i < a.row(); ++i) {
     for (int j = 0; j < b.col(); ++j) {
      for (int k = 0; k < a.col(); ++k) {
        (c[i][j] += a[i][k] * b[k][j]) %= MOD;
       } 
      }
    }
    return c;
  }
  Matrix pow(long long exp) {
    assert(row() == col());
    Matrix base = *this, ans = *this;
    for (; exp > 0; exp >>= 1, base = base * base)
      if (exp & 1) ans = ans * base;
    return ans;
  }
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

void bruteForce(int64_t n, int64_t x) { 
 int cnt = 0; 
 n = 2 * n; 
 for(int mask = 0; mask < (1 << n); mask++) {
   if(__builtin_popcount(mask) < 2) continue; 
   bool good = true; 
   for(int i = 0; i < n; i++) { 
    for(int j = i + 1; j < n; j++) { 
      if((mask >> i & 1) && (mask >> j & 1)) { 
        good &= (abs(i - j) != 1 && abs(i - j) != n / 2 + x); 
      }
    }
   }
  // if(good) cout << mask << '\n'; 
   cnt += good; 
 }
 cout << cnt << '\n'; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int64_t N, X; 
  cin >> N >> X; 
  if(N < 2) { 
    cout << 0 << '\n'; 
    return 0; 
  }
  //bruteForce(N, X); 
  if(X >= N) {
    Matrix matR({{1, 1}, {1, 0}}); 
    cout << ((matR.pow(2 * N))[0][0] - 2 * N % MOD - 1 + 2 * MOD) % MOD << '\n'; 
    return 0; 
  }
  else { 
    Matrix matL({{1, 1, 1}, {1, 0, 1}, {1, 1, 0}});
    Matrix matR({{1, 1}, {1, 0}}); 
    Matrix baseL({{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}); 
    Matrix baseR({{1, 0}, {0, 0}}); 
    auto left  = N > X     ? matL.pow(N - X - 1) * baseL : baseL, 
         right = X > 0     ? matR.pow(2 * X - 1) * baseR : baseR; 
    int64_t ret =   (left[0][0] % MOD * (right[0][0] + right[1][0]) % MOD + 
                     left[1][0] % MOD * right[0][0] % MOD + 
                     left[2][0] % MOD * (right[0][0] + right[1][0]) % MOD) % MOD;               
    if(X == 0) { 
       Matrix baseL1({{0, 0, 0}, {0, 0, 0}, {1, 0, 0}});
       left  = N > 1 ? matL.pow(N - 2) * baseL1 : baseL1;  
       (ret += 2 * MOD - left[1][0] - 2 * N % MOD - 1) %= MOD; 
       cout << ret << '\n'; 
    }
    else { 
       Matrix baseL1({{0, 0, 0}, {0, 0, 0}, {1, 0, 0}});
       Matrix baseR1({{0, 0}, {1, 0}}); 
       left  = N > X + 1 ? matL.pow(N - X - 2) * baseL1 : baseL1;  
       right = 2 * X > 1 ? matR.pow(2 * X - 2) * baseR1 : baseR1;  
       int64_t amt  =  (left[0][0] % MOD * (right[0][0] + right[1][0]) % MOD + 
                        left[1][0] % MOD * right[0][0] % MOD + 
                        left[2][0] % MOD * (right[0][0] + right[1][0]) % MOD) % MOD;  
       (ret += 2 * MOD - 2 * N % MOD - 1 - amt) %= MOD; 
       cout << ret << '\n'; 
    }
  }
  return 0; 
}

