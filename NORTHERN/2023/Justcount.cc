#include "bits/stdc++.h"
using namespace std;
const int mod = 123456789;
#define Lint long long
template <int D, typename T>
struct Vec : public vector<Vec<D - 1, T>>
{
    static_assert(D >= 1, "Dimension must be positive");
    template <typename... Args>
    Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};
template <typename T>
struct Vec<1, T> : public vector<T>
{
    Vec(int n = 0, T val = T()) : vector<T>(n, val) {}
};
signed main(void)
{
    int N, M, K;
    while (cin >> N >> M >> K)
    {
        if (N > M) swap(N, M);
        vector<int> V;
        for (int mask = 0; mask < (1 << N); mask++)
        {
            if (mask & (1 << mask)) continue;
            if (mask & (mask >> 1)) continue;
            V.push_back(mask);
        }
        vector<vector<int>> E(V.size());
        for (int i = 0; i < V.size(); i++)
        {
            for (int j = 0; j < V.size(); j++)
            {
                int u = V[i], v = V[j]; 
                if (u & v) continue;
                int fmask = u | v; 
                if (fmask & (1 << fmask)) continue;
                if (fmask & (fmask >> 1)) continue;
                E[i].push_back(j);
            }
        }
        Vec<3, Lint>dyn(M + 1, K + 1, V.size(), 0); 
        dyn[0][0][0] = 1;
        for (int i = 0; i < M; i++)
        {
            for(int j = 0; j <= K; j++)
            {
                for (int u = 0; u < V.size(); u++)
                {
                    if(dyn[i][j][u] == 0) continue; 
                    for (auto v : E[u])
                    {
                        int mask = V[v]; 
                        if (j + __builtin_popcount(mask) <= K)
                        {
                            dyn[i + 1][j + __builtin_popcount(mask)][v] = (dyn[i + 1][j + __builtin_popcount(mask)][v] + dyn[i][j][u] + mod) % mod;
                        }
                    }
                }
            }
        }
        Lint ret = 0; 
        for(int i = 0; i < V.size(); i++)
        {
            ret = (ret + mod + dyn[M][K][i]) % mod; 
        }
        cout << ret << '\n'; 
    }
    return 0;
}