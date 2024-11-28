#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int maxf = 3e7 + 1;
const int maxc = 5430;

int nA, nB, nC, visited[maxc][maxc], gcd_[maxc][maxc], mpA[maxf], mpB[maxf], mpC[maxf];

int find_gcd(int a, int b) { 
  if(a == 0) return b; 
  if(visited[a][b]) return gcd_[a][b]; 
  visited[a][b] = true; 
  return gcd_[a][b] = find_gcd(b % a, a); 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> nA >> nB >> nC;
  for (int i = 0, x; i < nA; i++) {
    cin >> x;
    mpA[x]++;
  }
  for (int i = 0, x; i < nB; i++) {
    cin >> x;
    mpB[x]++;
  }
  for (int i = 0, x; i < nC; i++) {
    cin >> x;
    mpC[x]++;
  }
  int64_t ret = 0;
  for (int n = 1; n < maxc; n++) {
    for (int m = n + 1; m < maxc; m += 2) {
      if (1LL * n * n + 1LL * m * m >= maxf) break; 
      if (find_gcd(n, m) > 1) continue;
      int64_t a = 1LL * m * m - 1LL * n * n;
      int64_t b = 2LL * m * n;
      int64_t c = 1LL * m * m + 1LL * n * n;
      int64_t jump_a = a, jump_b = b, jump_c = c;
      while (c < maxf) {
        if(mpA[a] && mpB[b] && mpC[c]) ret += 1LL * mpA[a] * mpB[b] * mpC[c];
        if(mpA[b] && mpB[a] && mpC[c]) ret += 1LL * mpA[b] * mpB[a] * mpC[c];
        a += jump_a;
        b += jump_b;
        c += jump_c;
      }
    }
  }
  cout << ret << '\n';
  return 0;
}