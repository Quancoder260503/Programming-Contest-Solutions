#include "bits/stdc++.h"

using namespace std;

#define double long double
#define sz(x) int(x.size())

const double oo = 1e50; 
const int _round = 100; 

using type = double; 

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
  static Matrix identity(long long n) {
    Matrix a = Matrix(n, n);
    while (n--) a[n][n] = 1;
    return a;
  }
  static Matrix infinity(long long n) {
    Matrix a = Matrix(n, n);
    for (int i = 0; i < a.row(); i++) {
      for (int j = 0; j < a.col(); j++) {
        a[i][j] = oo;
      }
    }
    return a;
  }
  Matrix operator*(const Matrix &b) {
    Matrix a = *this;
    assert(a.col() == b.row());

    Matrix c(a.row(), b.col());
    for (int i = 0; i < a.row(); ++i) {
      for (int j = 0; j < b.col(); ++j) {
        for (int k = 0; k < a.col(); ++k) {
          c[i][j] += a[i][k] * b[k][j];
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
    for(int i = 0; i < sz(data); i++) { 
      type sum = 0.0; 
      for(int j = 0; j < sz(data[i]); j++) { 
        sum += data[i][j]; 
      }
      for(int j = 0; j < sz(data[i]); j++) { 
        data[i][j] /= sum; 
      }
    }
    return; 
  }
};

vector<int> prefix_function(const string &s) {
  int n = sz(s); 
  vector<int> pi(n + 1);
  for (int i = 2; i <= n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i - 1] != s[j]) j = pi[j];
    if (s[i - 1] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

int get_next(vector<int>&pi, string &s, int pos, char c) { 
  if(pos == sz(s)) pos = pi[pos]; 
  while(pos > 0 && c != s[pos]) pos = pi[pos]; 
  if(s[pos] == c) pos++;
  return pos; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  double Prob_Dice; 
  string A, B; 
  cin >> A >> B >> Prob_Dice; 
  int N = sz(A), M = sz(B);
  vector<vector<int>>idx(N + 1, vector<int>(M + 1, -1)); 
  queue<pair<int, int>>q; 
  vector<int>kmpA = prefix_function(A); 
  vector<int>kmpB = prefix_function(B); 
  vector<char>choices = {'H', 'T'}; 
  q.push({0, 0}); 
  int n_states = 0; 
  idx[0][0] = n_states++; 
  while(sz(q)) { 
    auto [state_a, state_b] = q.front(); 
    q.pop(); 
    for(auto c : choices) { 
      int nxt_a = get_next(kmpA, A, state_a, c); 
      int nxt_b = get_next(kmpB, B, state_b, c); 
      if(nxt_a == N || nxt_b == M) continue; 
      if(idx[nxt_a][nxt_b] == -1) { 
        idx[nxt_a][nxt_b] = n_states++; 
        q.push({nxt_a, nxt_b}); 
      }
    }
  }
  int _win  = n_states++; 
  int _lose = n_states++;  
  Matrix _Prob(n_states, n_states); 
  for(int state_a = 0; state_a < N; state_a++) { 
    for(int state_b = 0; state_b < M; state_b++) {
      if(idx[state_a][state_b] < 0) continue;  
      int next_state, curr_state = idx[state_a][state_b]; 
      for(auto c : choices) { 
        int nxt_a = get_next(kmpA, A, state_a, c); 
        int nxt_b = get_next(kmpB, B, state_b, c); 
        if(nxt_a == N)      { next_state = _win; } 
        else if(nxt_b == M) { next_state = _lose; } 
        else                { next_state = idx[nxt_a][nxt_b]; } 
        //cout << curr_state << " " << next_state << '\n'; 
        _Prob[curr_state][next_state] = (c == 'H' ? Prob_Dice : 1.0 - Prob_Dice); 
      }
    }
  }
  _Prob[_win][_win] = _Prob[_lose][_lose] = 1.;
  for(int iter = 0; iter < _round; iter++) { 
    _Prob = _Prob * _Prob; 
    _Prob.reduce(); 
  }
  cout << fixed << setprecision(12) << boolalpha << _Prob.data[0][_win] << '\n'; 
  return 0; 
}