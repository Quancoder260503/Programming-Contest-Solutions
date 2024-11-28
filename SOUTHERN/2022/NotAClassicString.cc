#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

class Bit_Presum {
 public:
  static constexpr uint32_t omega = CHAR_BIT * sizeof(uint64_t);
  static constexpr uint32_t lg_omega = __lg(omega);
  static_assert(omega == 64u);

  Bit_Presum(vector<uint64_t> mask_)
      : n(mask_.size()), mask(move(mask_)), presum(n + 1) {
    build();
  }
  Bit_Presum(uint32_t bits, bool init_val = 0)
      : n((bits >> lg_omega) + 1),
        mask(n, init_val ? ~uint64_t{0} : uint64_t{0}),
        presum(n + 1) {
    if (init_val) mask.back() <<= ((n << lg_omega) - bits);
    build();
  }
  // popcount l <= i < r
  uint32_t query(uint32_t l, uint32_t r) const {
    if (__builtin_expect(r < l, false)) return 0;
    return query(r) - query(l);
  }
  // popcount 0 <= i < x
  uint32_t query(uint32_t x) const {
    uint32_t high = x >> lg_omega, low = x & ((uint64_t{1} << lg_omega) - 1);
    uint32_t ret = presum_query(high);
    ret += __builtin_popcountll(mask[high] & ((uint64_t{1} << low) - 1));
    return ret;
  }

  void update_pre_build(uint32_t x, bool val) {
    uint32_t high = x >> lg_omega, low = x & ((1u << lg_omega) - 1);
    mask[high] = (mask[high] & ~(uint64_t{1} << low)) | (uint64_t{val} << low);
  }
  void do_build() { build(); }

  friend ostream& operator<<(ostream& o, Bit_Presum const& b) {
    for (auto const& e : b.mask) {
      stringstream ss;
      ss << bitset<omega>(e);
      auto s = ss.str();
      reverse(s.begin(), s.end());
      o << s << "|";
    }
    o << " : ";
    for (auto const& e : b.presum) o << e << " ";
    o << "\n";
    return o;
  }

 private:
  void presum_build() {
    for (uint32_t x = 1; x <= n; ++x) {
      presum[x] += presum[x - 1];
    }
  }
  // sum 0 <= i < x
  uint32_t presum_query(uint32_t x) const { return presum[x]; }
  void build() {
    for (uint32_t x = 0; x < n; ++x) {
      presum[x + 1] = __builtin_popcountll(mask[x]);
    }
    presum_build();
  }

  const uint32_t n;
  vector<uint64_t> mask;
  vector<uint32_t> presum;
};
// }}}

template <typename T, typename Bit_Ds = Bit_Presum>
class WaveletMatrix {
 public:
  static_assert(is_integral<T>::value);
  static constexpr uint32_t height = CHAR_BIT * sizeof(T);

  WaveletMatrix(vector<T> v) : n(v.size()), data(height, n) { build(move(v)); }
  // count l <= i < r  s.t.  A <= val[i] < B
  uint32_t range_count(int l, int r, T A, T B) const {
    assert(0 <= l && r <= n);
    return count_lower(l, r, B) - count_lower(l, r, A);
  }
  // count l <= i < r  s.t.  A <= val[i]
  uint32_t range_count_up(int l, int r, T A) const {
    assert(0 <= l && r <= n);
    if (__builtin_expect(l > r, false)) return uint32_t{0};
    return (r - l) - count_lower(l, r, A);
  }
  // k from 0
  // range: [l, r-1]
  T k_th(int l, int r, int k) const {
    assert(0 <= k && k < n);
    return get_kth(l, r, k);
  }

  // internal functions {{{
 private:
  void build(vector<T> v) {
    m_index.resize(height);
    T const a = numeric_limits<T>::min();
    for (int h = height - 1; h >= 0; --h) {
      T const b =
          a + (T{1} << (max(0, h - 1))) - !h + (T{1} << (max(0, h - 1)));
      for (int i = 0; i < n; ++i) {
        data[h].update_pre_build(i, v[i] < b);
      }
      data[h].do_build();
      const int m = stable_partition(v.begin(), v.end(),
                                     [&b](T const& x) { return x < b; }) -
                    v.begin();
      for (int i = m; i < n; ++i) {
        v[i] =
            v[i] - (T{1} << (max(0, h - 1))) + !h - (T{1} << (max(0, h - 1)));
      }
      m_index[h] = m;
    }
  }
  /// count l <= i < r  s.t.  val[i] < B
  uint32_t count_lower(int l, int r, T const& B) const {
    assert(0 <= l && r <= n);
    if (__builtin_expect(r < l, false)) return 0;
    uint32_t ret = 0;
    int h = height;
    T a = numeric_limits<T>::min();
    while (h > 0) {
      --h;
      bool go_left =
          B < a + (T{1} << (max(0, h - 1))) - !h + (T{1} << (max(0, h - 1)));
      const int low_l = data[h].query(l), low_r = data[h].query(r);
      if (go_left) {
        l = low_l;
        r = low_r;
      } else {
        a = a + (T{1} << (max(0, h - 1))) - !h + (T{1} << (max(0, h - 1)));
        ret += low_r - low_l;
        l = m_index[h] + l - low_l;
        r = m_index[h] + r - low_r;
      }
    }
    return ret;
  }
  T get_kth(int l, int r, int k) const {
    assert(0 <= l && r <= n);
    assert(0 <= k && k < r - l);
    int h = height;
    T a = numeric_limits<T>::min();
    while (h > 0) {
      --h;
      const int low_l = data[h].query(l), low_r = data[h].query(r),
                low_lr = low_r - low_l;
      bool go_left = k < low_lr;
      if (go_left) {
        l = low_l;
        r = low_r;
      } else {
        a += T{1} << h;
        k -= low_lr;
        l = m_index[h] + l - low_l;
        r = m_index[h] + r - low_r;
      }
    }
    return a;
  }

  const int n;
  vector<int> m_index;
  vector<Bit_Ds> data;
  // }}}
};

struct suffix_array {
  suffix_array(const char *S) : N(strlen(S)) {
    vector<int> V;
    for (int i = 0; i < N; i++) V.push_back(S[i]);
    init(V);
  }

  suffix_array(const vector<int> &VV) : N(VV.size()) {
    vector<int> V(VV);
    init(V);
  }

  /* Get longest common prefix between two suffix-indicies. */
  int lcp(int si, int sj) {
    if (sj < si) swap(si, sj);
    if (si == sj) return N - SA[si];
    int len = sj - si;
    int buck = 31 - __builtin_clz(len);
    return min(LCP_MRQ[buck][si], LCP_MRQ[buck][sj - (1 << buck)]);
  }

  int N;
  vector<int> SA;
  vector<int> RA;

 private:
  void compress(vector<int> &V, vector<int> &C) {
    copy(V.begin(), V.end(), C.begin());
    sort(C.begin(), C.end());
    auto cend = unique(C.begin(), C.end());
    for (int i = 0; i < N; i++) {
      V[i] = lower_bound(C.begin(), cend, V[i]) - C.begin() + 1;
    }
    V.push_back(0);
    C.push_back(0);
  }

  void compute_sa(vector<int> &V, vector<int> &C) {
    vector<int> T(N + 1);
    for (int i = 0; i <= N; i++) SA.push_back(i);
    for (int ski = 0; V[SA[N]] < N; ski = ski ? ski << 1 : 1) {
      fill(C.begin(), C.end(), 0);
      for (int i = 0; i < ski; i++) T[i] = N - i;
      for (int i = 0, p = ski; i <= N; i++)
        if (SA[i] >= ski) T[p++] = SA[i] - ski;
      for (int i = 0; i <= N; i++) C[V[i]]++;
      for (int i = 1; i <= N; i++) C[i] += C[i - 1];
      for (int i = N; i >= 0; i--) SA[--C[V[T[i]]]] = T[i];

      T[SA[0]] = 0;
      for (int j = 1; j <= N; j++) {
        int a = SA[j];
        int b = SA[j - 1];
        T[a] = T[b] + (a + ski >= N || b + ski >= N || V[a] != V[b] ||
                       V[a + ski] != V[b + ski]);
      }
      V.swap(T);
    }
  }

  void compute_lcp(const vector<int> &OV) {
    LCP_MRQ.push_back(vector<int>(N));
    int len = 0;
    for (int i = 0; i < N; i++, len = max(0, len - 1)) {
      int si = RA[i];
      int j = SA[si - 1];
      for (; i + len < N && j + len < N && OV[i + len] == OV[j + len]; len++);
      LCP_MRQ[0][si - 1] = len;
    }
    for (int i = 1; 1 << i <= N; i++) {
      LCP_MRQ.push_back(vector<int>());
      const vector<int> &plcp = LCP_MRQ[i - 1];
      for (int j = 0; j + (1 << i) <= N; j++) {
        LCP_MRQ[i].push_back(min(plcp[j], plcp[j + (1 << (i - 1))]));
      }
    }
  }

  void init(vector<int> &V) {
    vector<int> OV(V);
    vector<int> C(N);
    compress(V, C);
    compute_sa(V, C);
    RA.resize(N + 1);
    for (int i = 0; i <= N; i++) RA[SA[i]] = i;
    compute_lcp(OV);
    return;
  }

  vector<vector<int>> LCP_MRQ;
}; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  string A, B; 
  cin >> A >> B; 
  char c = 127; 
  string combined = A + c + B; 
  suffix_array suffixArray(combined.c_str()); 
  auto getRight = [&](int ind, int amt) { 
    int lo = ind, hi = sz(combined) - 1; 
    while(lo < hi) { 
      int mid = (lo + hi + 1) / 2;
      if(suffixArray.lcp(ind, mid) < amt) { 
        hi = mid - 1; 
      }
      else { 
        lo = mid; 
      }
    }
    return lo; 
  }; 
  auto getLeft = [&](int ind, int amt) { 
    int lo = 0, hi = ind; 
    while(lo < hi) { 
      int mid = (lo + hi) / 2;
      if(suffixArray.lcp(ind, mid) < amt) { 
        lo = mid + 1; 
      }
      else { 
        hi = mid; 
      }
    }
    return lo; 
  }; 
  WaveletMatrix<int> data(suffixArray.SA);
  vector<int>posSA(suffixArray.SA); 
  for(int i = 0; i < sz(suffixArray.SA); i++) { 
    posSA[suffixArray.SA[i]] = i; 
  }
  int Q; 
  cin >> Q; 
  for(int iter = 0, a, b, c, d; iter < Q; iter++) { 
    cin >> a >> b >> c >> d; 
    --a, --b, --c, --d; 
    if (a > b || c > d) {
        cout << 0 << '\n';
        continue;
    }

    if (a < 0 || b >= sz(A) || c < 0 || d >= sz(B)) {
        cout << 0 << '\n';
        continue;
    }
    assert(0 <= a && a <= b && b < sz(A));
    assert(0 <= c && c <= d && d < sz(B));
    int pos = posSA[a]; 
    int posL = getLeft(pos, b - a + 1); 
    int posR = getRight(pos, b - a + 1);
    int cc = c + sz(A) + 1; 
    int cd = d - (b - a) + 1 + sz(A); 
    int ret = 0; 
    if(cc <= cd) { 
      ret = data.range_count(posL, posR + 1, cc, cd + 1); 
    } 
    cout << ret << '\n'; 
  }
  return 0; 
}