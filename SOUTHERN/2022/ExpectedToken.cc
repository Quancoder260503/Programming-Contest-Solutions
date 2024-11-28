#include "bits/stdc++.h"

using namespace std;

const int maxf = 105;

double dyn[maxf][maxf];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, K, X;
  cout << fixed << setprecision(2); 
  while (cin >> N >> K >> X && N) {
    for (int i = 0; i < maxf; i++) {
      for (int j = 0; j < maxf; j++) {
        dyn[i][j] = 0;
      }
    }
    vector<double> a(N + 1), l(N + 1), Prob(N + 1);
    for (int i = 1; i <= N; i++) {
      cin >> a[i] >> l[i] >> Prob[i];
      l[i] /= 100;
      Prob[i] /= 100;
    }
    vector<int> ord(N + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin() + 1, ord.end(), [&](int i, int j) {
      return (a[i] * Prob[i] * (Prob[j] * l[j] - l[j]) > a[j] * Prob[j] * (Prob[i] * l[i] - l[i]));
    });
    dyn[0][0] = X;
    for (int i = 1; i <= N; i++) {
      for (int j = 0; j <= K; j++) {
        dyn[i][j] = dyn[i - 1][j];
        if (j > 0) {
          dyn[i][j] = max(dyn[i][j], Prob[ord[i]] * (dyn[i - 1][j - 1] + a[ord[i]]) +
                                    (1. - Prob[ord[i]]) * (1. - l[ord[i]]) * dyn[i - 1][j - 1]);
        }
      }
    }
    cout << dyn[N][K] << '\n';
  }
  return 0;
}