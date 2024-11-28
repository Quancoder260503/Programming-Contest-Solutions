#include "bits/stdc++.h"
using namespace std;
#define Lint long long
signed main(void)
{
    int N, K, T; 
    cin >> T;
    while (T--)
    {
        cin >> N >> K;
        vector<Lint> prefix(N + 1);
        for (int i = 0; i < N; i++)
        {
            int x; 
            cin >> x;
            prefix[i + 1] = prefix[i] + x;
        }
        array<vector<Lint>, 2>dyn; 
        dyn[0].resize(N + 1); 
        dyn[1].resize(N + 1); 
        dyn[1][0] = dyn[0][0] = 0;
        for (int i = 1; i <= N; i++)
        {
            dyn[0][i] = dyn[0][i - 1];
            dyn[1][i] = dyn[1][i - 1];
            if (i >= K)
            {
                dyn[1][i] = max(dyn[1][i], dyn[0][i - K] + prefix[i] - prefix[i - K]);
                dyn[0][i] = max(dyn[0][i], dyn[1][i - K] + prefix[i - K] - prefix[i]);
            }
        }
        cout << max(dyn[0][N], dyn[1][N]) << '\n';
    }
    return 0;
}