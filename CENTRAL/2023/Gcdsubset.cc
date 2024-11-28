#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int mod = 1e9 + 7;
const int M = 72;
const int K = 200;
signed main(void)
{
    int N, T;
    cin >> T;
    while (T--)
    {
        cin >> N;
        vector<Lint> arr(M);
        vector<Lint> dyn(M);
        vector<Lint> pw2(K);
        pw2[0] = 1;
        for (int i = 1; i < K; i++)
        {
            pw2[i] = pw2[i - 1] * 2 % mod;
        }
        for (int i = 0; i < N; i++)
        {
            int x;
            cin >> x;
            for (int j = 1; j < M; j++)
            {
                if (x % j == 0)
                {
                    arr[j]++;
                }
            }
        }
        Lint ret = 0;
        for (int i = M - 1; i > 0; i--)
        {
            dyn[i] = (pw2[arr[i]] - 1 + mod) % mod;
            for (int j = 2 * i; j < M; j += i)
            {
                dyn[i] = (dyn[i] - dyn[j] + mod) % mod;
            }
            ret = (ret + 1LL * i % mod * dyn[i] % mod + mod) % mod;
        }
        cout << ret << '\n';
    }
    return 0;
}