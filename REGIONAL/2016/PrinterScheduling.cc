#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1000000000;
const int maxf = 300; 

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
      while (int pushed = dfs(s, oo)) flow += pushed;
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

int l[maxf], r[maxf], d[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int Q;
  cin >> Q;
  for (int iter = 0; iter < Q; iter++) {
    int N, M;
    cin >> N >> M;
    int opt = 0, sumin = 0;
    for (int i = 0; i < N; i++) {
      cin >> d[i] >> l[i] >> r[i];
      opt = max(opt, r[i]);
      sumin += d[i];
    }
    MaxFlow dinic(N + opt + 3);
    int src = N + opt + 1;
    int sink = N + opt + 2;
    for (int i = 0; i < N; i++) {
      dinic.addEdge(src, i, d[i]);
      for (int j = l[i] + 1; j <= r[i]; j++) {
        dinic.addEdge(i, N + j, 1);
      }
    }
    for (int i = 0; i <= opt; i++) {
      dinic.addEdge(N + i, sink, M);
    }
    int cc = dinic.getMaxFlow(src, sink);
    if (cc == sumin) {
      cout << "YES\n"; 
      vector<int>marked(opt + 1, 0); 
      for (int i = 0; i < N; i++) {
        vector<int>ret; 
        for(auto id : dinic.g[i]) { 
           auto edge = dinic.e[id];
           if(edge.a == i && edge.b < src && edge.flow == edge.cap) {
             ret.push_back(edge.b - N); 
           }  
        }
        vector<tuple<int, int, int>>ans; 
        for(int j = 0; j < sz(ret); j++) { 
          int st = j; 
          while(st + 1 < sz(ret) && ret[st] + 1 == ret[st + 1] && marked[ret[st]] == marked[ret[st + 1]]) { 
            st++; 
          }
          ans.push_back({ret[j] - 1, ret[st], marked[ret[st]] + 1}); 
          j = st; 
        }
        cout << sz(ans) << '\n'; 
        for(auto [from, to, id] : ans) { 
          cout << from << " " << to << " " << id << '\n'; 
        }
        for(int j = 0; j < sz(ret); j++) { 
          marked[ret[j]]++; 
        }
      }
    } 
    else {
      cout << "NO\n";
    }
    cout << '\n'; 
  }
  return 0;
}