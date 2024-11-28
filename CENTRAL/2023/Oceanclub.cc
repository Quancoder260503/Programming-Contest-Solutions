#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int mod = 2023;
const int M = 1e5 + 2;
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
signed main(void)
{
    int N, Q;
    while (cin >> N)
    {
        vector<int> arr(N);
        vector<int> pos(M);
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        for (int i = 0; i < N; i++)
        {
            pos[arr[i]] = i;
        }
        cin >> Q;
        vector<vector<vector<Lint>>> dyn(N, vector<vector<Lint>>(N, vector<Lint>(N + 1)));
        for (int i = 0; i < N; i++)
        {
            dyn[i][i][0] = 1;
        }
        for (int k = 1; k < N; k++)
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = i; j < N; j++)
                {
                    for (int t = i; t < j; t++)
                    {
                        if (gcd(arr[t], arr[j]) == 1)
                        {
                            dyn[i][j][k] = (dyn[i][j][k] + dyn[i][t][k - 1] + mod) % mod;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < Q; i++)
        {
            int u, v, k;
            cin >> u >> v >> k;
            cout << dyn[pos[u]][pos[v]][k] << '\n';
        }
    }
    return 0;
}