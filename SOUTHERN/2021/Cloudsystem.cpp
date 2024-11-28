/**
 * @file Cloudsystem.cpp
 * @author Minh Quan Le
 * @brief Problem A 
 * @version 0.1
 * @date 2022-10-24
 * 
 * 
 */

#include "bits/stdc++.h"
using namespace std;
const int INF = 1000000000;
const int MAXN = 2e2 + 10;
struct Edge {
  int a, b, cap, flow;
};
struct MaxFlow {
  int n, s, t;
  vector<int> d, ptr, q;
  vector<Edge> e;
  vector<vector<int>> g;

  MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n) {
    e.clear();
    for (int i = 0; i < n; i++) {
      g[i].clear();
      ptr[i] = 0;
    }
  }

  void addEdge(int a, int b, int cap) {
    Edge e1 = {a, b, cap, 0};
    Edge e2 = {b, a, 0, 0};
    g[a].push_back((int)e.size());
    e.push_back(e1);
    g[b].push_back((int)e.size());
    e.push_back(e2);
  }
  int getMaxFlow(int _s, int _t) {
    s = _s;
    t = _t;
    int flow = 0;
    for (;;) {
      if (!bfs()) break;
      std::fill(ptr.begin(), ptr.end(), 0);
      while (int pushed = dfs(s, INF)) flow += pushed;
    }
    return flow;
  }

 private:
  bool bfs() {
    int qh = 0, qt = 0;
    q[qt++] = s;
    std::fill(d.begin(), d.end(), -1);
    d[s] = 0;

    while (qh < qt && d[t] == -1) {
      int v = q[qh++];
      for (int i = 0; i < (int)g[v].size(); i++) {
        int id = g[v][i], to = e[id].b;
        if (d[to] == -1 && e[id].flow < e[id].cap) {
          q[qt++] = to;
          d[to] = d[v] + 1;
        }
      }
    }
    return d[t] != -1;
  }

  int dfs(int v, int flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
      int id = g[v][ptr[v]], to = e[id].b;
      if (d[to] != d[v] + 1) continue;
      int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
      if (pushed) {
        e[id].flow += pushed;
        e[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }
};

struct GomoryHu {
  int ok[MAXN], cap[MAXN][MAXN];
  int answer[MAXN][MAXN], parent[MAXN];
  int n;
  MaxFlow flow;
  GomoryHu(int _n) : n(_n), flow(_n) {
    for (int i = 0; i < n; ++i) {
      ok[i] = parent[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cap[i][j] = 0, answer[i][j] = INF;
      }
    }
  }
  void addEdge(int u, int v, int c) { cap[u][v] += c; }

  void calc() {
    for (int i = 1; i <= n - 1; ++i) {
      flow = MaxFlow(n);
      for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
          if (cap[u][v]) {
            flow.addEdge(u, v, cap[u][v]);
          }
        }
      }
      int f = flow.getMaxFlow(i, parent[i]);
      bfs(i);
      for (int j = i + 1; j < n; ++j)
        if (ok[j] && parent[j] == parent[i]) parent[j] = i;

      answer[i][parent[i]] = answer[parent[i]][i] = f;
      for (int j = 0; j < i; ++j)
        answer[i][j] = answer[j][i] = min(f, answer[parent[i]][j]);
    }
  }
  void bfs(int start) {
    memset(ok, 0, sizeof ok);
    queue<int> qu;
    qu.push(start);
    while (!qu.empty()) {
      int u = qu.front();
      qu.pop();
      for (int xid = 0; xid < (int)flow.g[u].size(); ++xid) {
        int id = flow.g[u][xid];
        int v = flow.e[id].b, fl = flow.e[id].flow, c = flow.e[id].cap;
        if (!ok[v] && fl < c) {
          ok[v] = 1;
          qu.push(v);
        }
      }
    }
  }
};
int n, m, t;
void solve() {
  cin >> n;
  GomoryHu go(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x;
      cin >> x;
      go.addEdge(i, j, x);
    }
  }
  printf("Case #%d:\n", t);
  go.calc();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << (go.answer[i][j] == INF ? 0 : go.answer[i][j]) << " ";
    }
    cout << '\n';
  }
  return;
}
signed main(void) {
  int T;
  cin >> T;
  for (t = 1; t <= T; t++) {
    solve();
  }
  return 0;
}