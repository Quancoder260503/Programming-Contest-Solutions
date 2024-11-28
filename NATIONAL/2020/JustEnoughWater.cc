#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int64_t calc(vector<int>&h) { 
   int N = sz(h); 
   vector<int>L(N), R(N); 
   for(int i = 0; i < N; i++) { 
     L[i] = h[i]; 
     if(i > 0) L[i] = max(L[i], L[i - 1]); 
   } 
   for(int i = N - 1; i >= 0; i--) { 
     R[i] = h[i]; 
     if(i + 1 < N) R[i] = max(R[i], R[i + 1]); 
   }
   int64_t ret = 0;
   for(int i = 1; i < N - 1; i++) { 
     if(h[i] <= min(L[i - 1], R[i + 1])) { 
       ret += min(L[i - 1], R[i + 1]) - h[i]; 
     }
   }
   return ret;  
}

int main(void) { 
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  cout.tie(0); 
  int N, K; 
  cin >> N >> K; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
    for(int j = i + 1; j < N; j++) { 
      for(int k = j + 1; k < N; k++) { 
        for(int left = 0; left <= K; left++) { 
          for(int right = 0; right + left <= K; right++) { 
            int mid = K - left - right; 
            a[i] += left; a[j] += mid; a[k] += right; 
            ret = max(ret, calc(a)); 
            a[i] -= left; a[j] -= mid; a[k] -= right; 
          }
        }
      }
    }
  }
  cout << ret << '\n'; 
  return 0; 
}
