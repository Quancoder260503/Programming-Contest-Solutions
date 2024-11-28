#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())
#define rep(i, j, k) for (int i = j; i < k; i++)

const int maxf = 5e5 + 2;

template <class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      rep(j, 0, sz(jmp[k])) jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b);  // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

struct LCA {
  int T = 0;
  vector<int> time, path, ret;
  vector<int64_t> depth;
  RMQ<int> rmq;

  LCA(vector<vector<pair<int, int>>>& C)
      : depth(sz(C)), time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
  void dfs(vector<vector<pair<int, int>>>& C, int v, int par) {
    time[v] = T++;
    for (auto [y, w] : C[v])
      if (y != par) {
        path.push_back(v), ret.push_back(time[v]);
        depth[y] = depth[v] + w;
        dfs(C, y, v);
      }
    return;
  }
  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  int64_t dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
  }
};

vector<int>_divisor[maxf], group[maxf]; 
int vis[maxf], label[maxf]; 


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  for (int i = 1; i < maxf; i++) {
    for (int j = i; j < maxf; j += i) {
      _divisor[j].push_back(i);
    }
  }
  for (int iter = 1, N; ; iter++) {
    cin >> N;
    if(N == 0) break; 
    vector<int> get_gcd; 
    for (int i = 0; i < N; i++) {
      cin >> label[i];
      for (auto c : _divisor[label[i]]) {
        if (vis[c] != iter) {
          vis[c] = iter;
          get_gcd.push_back(c);
        }
        group[c].push_back(i);
      }
    }
    vector<vector<pair<int, int>>>g(N); 
    for (int i = 0, u, v, w; i < N - 1; i++) {
      cin >> u >> v >> w;
      --u, --v;
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    LCA tree(g);
    int64_t ret = 0;
    for (auto curr_g : get_gcd) {
      int root = group[curr_g][0], _nxt = root;
      int64_t dst = 0; 
      for (auto c : group[curr_g]) {
        int64_t curr_dist = tree.dist(root, c);
        if (curr_dist > dst) {
          dst = curr_dist;
          _nxt = c;
        }
      }
      root = _nxt; 
      ret = max(ret, 1LL * curr_g * dst); 
      for(auto c : group[curr_g]) { 
        ret = max(ret, 1LL * tree.dist(root, c) * curr_g); 
      }
      group[curr_g].clear(); 
    }
    cout << ret << '\n';
  }
  return 0;
}