#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

template <class T>
struct LazySeg {
  int sz;
  vector<T> st, ycoord;
  vector<int> lz;
  T comb(T a, T b) { return a + b; }
  LazySeg(int n, vector<T> &_ycoord) : ycoord(_ycoord) {
    sz = 1;
    while (sz < n) sz <<= 1;
    st.assign(4 * sz, 0);
    lz.assign(4 * sz, 0);
    return;
  }
  T length(int ql, int qr) { return ycoord[qr] - ycoord[ql]; }
  void pull(int i, int ql, int qr) {
    if (lz[i] < 1)
      st[i] = (ql + 1 == qr ? 0 : comb(st[i << 1], st[i << 1 | 1]));
    else
      st[i] = length(ql, qr);
    return;
  }
  void update(int ql, int qr, int x, int i, int l, int r) {
    if (ql >= r || qr <= l) return;
    if (ql <= l && r <= qr) {
      lz[i] += x; 
    } else {
      int m = (l + r) >> 1;
      update(ql, qr, x, i << 1, l, m);
      update(ql, qr, x, i << 1 | 1, m, r);
    }
    pull(i, l, r);
    return;
  }
  void update(int ql, int qr, int x) { update(ql, qr, x, 1, 0, sz - 1); }
};

template <class T>
struct LazySeg2 {
  int sz;
  vector<T> st, ycoord, lz;
  T comb(T a, T b) { return a + b; }
  LazySeg2(int n, vector<T> &_ycoord) : ycoord(_ycoord) {
    sz = 1;
    while (sz < n) sz <<= 1;
    st.assign(4 * sz, 0);
    lz.assign(4 * sz, 0);
    return;
  }
  T length(int ql, int qr) { return ycoord[qr] - ycoord[ql]; }
  void push(int i, int ql, int qr) { 
    if(lz[i]) { 
      st[i] = length(ql, qr) - st[i]; 
      if(ql + 1 < qr) { 
        lz[i << 1] = (lz[i << 1] + lz[i]) % 2; 
        lz[i << 1 | 1] = (lz[i << 1 | 1] + lz[i]) % 2; 
      }
      lz[i] = 0; 
    }
    return; 
  }
  void update(int ql, int qr, int x, int i, int l, int r) {
    push(i, l, r); 
    if (ql >= r || qr <= l) return;
    if (ql <= l && r <= qr) {
      lz[i] += x; 
      return void(push(i, l, r)); 
    } else {
      int m = (l + r) >> 1;
      update(ql, qr, x, i << 1, l, m);
      update(ql, qr, x, i << 1 | 1, m, r);
      st[i] = comb(st[i << 1], st[i << 1 | 1]); 
    }
    return;
  }
  void update(int ql, int qr, int x) { update(ql, qr, x, 1, 0, sz - 1); }
};

struct event {
  int type, x, ylo, yhi;
  event(int _x, int _ylo, int _yhi, int _type)
      : x(_x), ylo(_ylo), yhi(_yhi), type(_type) {}
  bool operator<(const event &other) const {
    if (x != other.x) return x < other.x;
    return type < other.type;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N;
  cin >> N;
  vector<tuple<int, int, int, int>> _stick;
  vector<int64_t> ycoord;
  for (int i = 0; i < N; i++) {
    int xA, xB, yA, yB;
    cin >> xA >> yA >> xB >> yB;
    if(xA > xB) swap(xA, xB); 
    if(yA > yB) swap(yA, yB); 
    _stick.push_back({xA, yA, yB, 1});
    _stick.push_back({xB, yA, yB, -1});
    ycoord.push_back(yA);
    ycoord.push_back(yB);
  }
  sort(ycoord.begin(), ycoord.end());
  ycoord.erase(unique(ycoord.begin(), ycoord.end()), ycoord.end());
  vector<event> stick;
  for (auto [x, yA, yB, type] : _stick) {
    int pA = lower_bound(ycoord.begin(), ycoord.end(), yA) - ycoord.begin();
    int pB = lower_bound(ycoord.begin(), ycoord.end(), yB) - ycoord.begin();
    stick.push_back(event(x, pA, pB, type));
  }
  sort(stick.begin(), stick.end());
  LazySeg<int64_t> tree(sz(ycoord), ycoord);
  LazySeg2<int64_t>tree2(sz(ycoord), ycoord); 
  int64_t ret = 0;
  for (int i = 0; i < sz(stick) - 1; i++) {
    tree.update(stick[i].ylo, stick[i].yhi, stick[i].type);
    tree2.update(stick[i].ylo, stick[i].yhi, 1); 
    ret  += 1LL * (-stick[i].x + stick[i + 1].x) * tree.st[1] - 
            1LL * (-stick[i].x + stick[i + 1].x) * tree2.st[1];  
  }
  cout << ret << '\n';
  return 0;
}