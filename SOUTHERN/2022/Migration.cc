#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int maxf = 5e3 + 10;
const int maxc = 1e6 + 10; 
const int64_t oo = LLONG_MAX;

short opt[maxf][maxf]; 
int64_t dyn[maxf][maxf], cost[maxf][maxf];
int N, K;

vector<int64_t>sum, sumW;  

struct ship { 
  int64_t x, w; 
  bool operator < (const ship &other) const { 
    return x < other.x; 
  }
}; 

ship a[maxf]; 

int64_t goLeft(int i, int j) { 
  return (sumW[j] - sumW[i]) - 1LL * i * (sum[j] - sum[i]); 
}

int64_t goRight(int i, int j) { 
  return -(sumW[j] - sumW[i]) + 1LL * j * (sum[j] - sum[i]); 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> K;
  sum.resize(maxc + 1, 0); 
  sumW.resize(maxc + 1, 0);
  for (int i = 1; i <= N; i++) {
    cin >> a[i].x >> a[i].w; 
    sum[a[i].x] += a[i].w;
    sumW[a[i].x] += 1LL * a[i].w * a[i].x; 
  }
  sort(a + 1, a + N + 1);  
  partial_sum(sum.begin(), sum.end(), sum.begin());
  partial_sum(sumW.begin(), sumW.end(), sumW.begin());   
  for (int i = 1; i <= N; i++) {
    for (int j = i; j <= N; j++) {
      int mid = (a[i].x + a[j].x) / 2; 
      cost[i][j] = goLeft(a[i].x, mid) + goRight(mid, a[j].x);
    }
  }
  memset(dyn, 63, sizeof(dyn)); 
  for (int i = 1; i <= N; i++) {
    dyn[1][i] = goRight(0, a[i].x); 
    opt[1][i] = 1;
  }
  for (int i = 2; i <= K; i++) {
    opt[i][N + 1] = N; 
    for (int j = N; j >= i; j--) {
      for (int k = opt[i - 1][j]; k <= opt[i][j + 1]; k++) { 
        if (dyn[i][j] > cost[k][j] + dyn[i - 1][k]) {
          dyn[i][j] = cost[k][j] + dyn[i - 1][k]; 
          opt[i][j] = k;
        }
      } 
    }
  } 
  int64_t ret = oo; 
  for(int i = 1; i <= N; i++) { 
    ret = min(ret, dyn[K][i] + goLeft(a[i].x, 1000001)); 
  }
  cout << ret << '\n'; 
  return 0;
}

