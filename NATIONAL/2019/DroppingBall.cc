#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = 1e18; 

using type = int64_t;

struct Matrix {
  vector<vector<type>> data;
  int row() const { return data.size(); }
  int col() const { return data[0].size(); }
  auto &operator[](int i) { return data[i]; }
  const auto &operator[](int i) const { return data[i]; }
  Matrix() = default;

  Matrix(int r, int c) : data(r, vector<type>(c, -oo)) {}

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
  static Matrix identity(long long n) {
    Matrix a = Matrix(n, n);
    while (n--) a[n][n] = 1;
    return a;
  }
  Matrix operator*(const Matrix &b) {
    Matrix a = *this;
    assert(a.col() == b.row());

    Matrix c(a.row(), b.col());
    for (int i = 0; i < a.row(); ++i) {
      for (int j = 0; j < b.col(); ++j) {
        for (int k = 0; k < a.col(); ++k) {
          c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
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
  void reduce(void) {
    for (int i = 0; i < sz(data); i++) {
      type sum = 0.0;
      for (int j = 0; j < sz(data[i]); j++) {
        sum += data[i][j];
      }
      for (int j = 0; j < sz(data[i]); j++) {
        data[i][j] /= sum;
      }
    }
    return;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M, K;
  cin >> N >> M >> K;
  vector<vector<char>> g(N + 1, vector<char>(M, '.'));
  vector<int64_t> a(M);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> g[i][j];
    }
  }
  for (int i = 0; i < M; i++) {
    cin >> a[i];
  }
  vector<vector<int>> dyn(N + 1, vector<int>(M, -1));
  auto doit = [&](int sx, int sy) {
    for (int i = 0; i <= N; i++) {
      for (int j = 0; j < M; j++) {
        dyn[i][j] = -1;
      }
    }
    queue<pair<int, int>>q;
    q.push({sx, sy}); 
    while (sz(q)) {
      auto [px, py] = q.front();
      q.pop();
      if (px == N || g[px][py] == 'X') continue;
      if(g[px][py] == '?') {
        if(py + 1 < M && dyn[px][py + 1] == -1) {
          dyn[px][py + 1] = dyn[px][py] + 1; 
          q.push({px, py + 1}); 
        } 
        if(py - 1 >= 0 && dyn[px][py - 1] == -1) {
          dyn[px][py - 1] = dyn[px][py] + 1; 
          q.push({px, py - 1}); 
        } 
        continue; 
      }
      int kx = -1, ky = -1;
      if (g[px][py] == '.' && px + 1 <= N) {
        kx = px + 1, ky = py;
      } else if (g[px][py] == 'R' && py + 1 < M) {
        kx = px, ky = py + 1;
      } else if (g[px][py] == 'L' && py - 1 >= 0) {
        kx = px, ky = py - 1;
      }
      if (kx == -1 || ky == -1 || g[kx][ky] == 'X') continue;
      if(dyn[kx][ky] == -1) { 
        dyn[kx][ky] = dyn[px][py] + 1; 
        q.push({kx, ky}); 
      }
    }
  };
  Matrix _mat(M, M);
  int64_t ret = 0; 
  for (int i = 0; i < M; i++) {
    if (g[0][i] == 'X') continue; 
    doit(0, i);
    for (int j = 0; j < M; j++) {
      if (dyn[N][j] == -1) continue; 
      _mat[i][j] = a[j]; 
    }
  }
  _mat = _mat.pow(K - 1); 
  for(int i = 0; i < M; i++) { 
    for(int j = 0; j < M; j++) { 
      ret = max(ret, _mat[i][j]); 
    }
  }
  cout << ret << '\n'; 
  return 0;
}
