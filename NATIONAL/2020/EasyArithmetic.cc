#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int mod = 998244353; 
const int maxf = (1 << 19); 

int64_t pw[maxf]; 

struct Number {
  int64_t val;
  int len; 
  Number(){ val = len = 0; }; 
  Number(int64_t _val, int _len): val(_val), len(_len) {};
  Number operator + (const Number &other) const { 
    Number ret; 
    ret.len = this->len + other.len; 
    ret.val = (this->val % mod * pw[other.len] % mod + other.val) % mod; 
    return ret; 
  }
}; 

struct node {
  Number first, second; 
  int64_t val; 
  char sign; 
  node(){ 
    first  = Number(0, 1); 
    second = Number(0, 1); 
    val = 0; 
    sign = '?'; 
    return; 
  };
  node(Number _first, Number _second, int64_t _val, char _sign): 
  first(_first), second(_second), val(_val), sign(_sign) {};  
  node operator + (const node &other) const {
    if(this->sign  == '?') return other; 
    if(other.sign  == '?') return *this;
    node ret; 
    if(other.sign != '!') { 
      ret.sign = other.sign; 
    }
    else ret.sign = this->sign; 
    if(other.sign != '!') { 
      ret.second = other.second;  
    }
    else ret.second = this->second + other.first; 
    if(this->sign != '!') { 
      ret.first = this->first;
    }
    else ret.first  = this->second + other.first; 
    ret.val = (this->val + other.val) % mod; 
    if(this->sign == '+' && other.sign != '!') { 
      ret.val = (ret.val + (this->second + other.first).val % mod + mod) % mod; 
    }
    if(this->sign == '-' && other.sign != '!') { 
      ret.val = (ret.val - (this->second + other.first).val % mod + mod) % mod; 
    }
    return ret; 
  }
}; 

node tree[maxf << 1]; 

void update(int pos, char c, int l, int r, int p) { 
  if(l == r) {
    if(c == '+' || c == '-') { 
      tree[p].first.val = tree[p].second.val = 0;
      tree[p].first.len = tree[p].second.len = 0; 
      tree[p].val = 0; 
      tree[p].sign = c;  
    }
    else { 
      tree[p].first.val = tree[p].second.val = c - '0';
      tree[p].first.len = tree[p].second.len = 1; 
      tree[p].val = 0; 
      tree[p].sign = '!';  
    } 
    return; 
  }
  int mid = (l + r) / 2; 
  if(pos <= mid) update(pos, c, l, mid, p << 1); 
  else           update(pos, c, mid + 1, r, p << 1 | 1); 
  tree[p] = tree[p << 1] + tree[p << 1 | 1];
  return; 
}

node none;

node query(int ql, int qr, int l, int r, int p = 1) { 
  if(qr < l || r < ql) return none; 
  if(ql <= l && r <= qr) { 
    return tree[p]; 
  }
  int mid = (l + r) / 2; 
  node ret = query(ql, qr, l, mid, p << 1) + query(ql, qr, mid + 1, r, p << 1 | 1);
 // cout << l << " " << r << " " << ret.first.val << " " << ret.val << " " << ret.second.val << '\n'; 
  return ret; 
}

void init() { 
  pw[0] = 1; 
  for(int i = 1; i < maxf; i++) { 
    pw[i] = pw[i - 1] * 10 % mod; 
  }
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  init(); 
  string S; 
  cin >> S; 
  for(int i = 0; i < sz(S); i++) { 
    update(i + 1, S[i], 1, sz(S), 1); 
  }
  int Q;
  cin >> Q; 
  for(int iter = 0; iter < Q; iter++) { 
    char type; 
    cin >> type; 
    if(type == '?') { 
      int l, r; 
      cin >> l >> r; 
      node ret = query(l, r, 1, sz(S), 1); 
      int64_t ans = 0; 
      if(ret.sign == '+') { 
        ans = (ret.first.val + ret.val + ret.second.val + mod) % mod; 
      }
      else if(ret.sign == '-') { 
        ans = (ret.first.val + ret.val - ret.second.val + mod) % mod; 
      }
      else if(ret.sign == '!') { 
        ans = ret.first.val; 
      }
      cout << ans << '\n'; 
    } else { 
      int pos; char c; 
      cin >> pos >> c; 
      S[pos - 1] = c; 
      update(pos, S[pos - 1], 1, sz(S), 1); 
    }
  }
  return 0; 
}

