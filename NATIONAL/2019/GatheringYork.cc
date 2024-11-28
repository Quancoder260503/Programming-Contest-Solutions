#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int64_t oo = LLONG_MAX / 2; 

int64_t range(int L, int R, vector<int64_t>&psum) { 
  return psum[R] - psum[L - 1]; 
} 

int64_t calc(int L, int R, vector<int>&a, vector<int64_t>&psum) { 
  int mid = (L + R) / 2; 
  return 1LL * a[mid] * (mid - L + 1) - range(L, mid, psum) + 
         range(mid + 1, R, psum) - 1LL * a[mid] * (R - mid); 
} 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N;
  cin >> N; 
  vector<int>a(N + 1); 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
  }
  sort(a.begin() + 1, a.end()); 
  vector<int64_t>sum(N + 1), Sum(N + 1);
  for(int i = 1; i <= N; i++) { 
    sum[i] = sum[i - 1] + a[i]; 
    Sum[i] = Sum[i - 1] + llabs(a[i]); 
  } 
  int64_t ret = oo; 
  for(int i = 1; i <= N; i++) { 
    ret = min(ret, range(1, i - 1, Sum) + calc(i, N, a, sum));
    ret = min(ret, range(i + 1, N, Sum) + calc(1, i, a, sum));  
  }
  cout << ret << '\n'; 
  return 0; 
}

