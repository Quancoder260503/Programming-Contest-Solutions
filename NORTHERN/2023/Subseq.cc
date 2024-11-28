#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int mod = 1e9 + 7;
signed main(void)
{
    int N, K;
    string S;
    while (cin >> N >> K >> S)
    {
        S = " " + S;
        vector<vector<Lint>> dyn(N + 1, vector<Lint>(K + 1));
        vector<int> pos(N + 1);
        for (int i = 1; i <= N; i++)
        {
            for (int j = i - 1; j > 0; j--)
            {
                if (S[i] == S[j])
                {
                    pos[i] = j;
                    break; 
                }
            }
        }
        dyn[0][0] = 1;
        for (int i = 1; i <= N; i++)
        {
            for (int j = 0; j <= min(i, K); j++)
            {
                dyn[i][j] = (dyn[i - 1][j] + (j ? dyn[i - 1][j - 1] : 0) + mod) % mod;
                if (pos[i] == 0)
                    continue;
                if (0 <= j - i + pos[i] && j - i + pos[i] <= K)
                {
                    dyn[i][j] = (dyn[i][j] + mod - dyn[pos[i] - 1][j - i + pos[i]]) % mod;
                }
            }
        }
        cout << dyn[N][K] << '\n';
    }
    return 0;
}