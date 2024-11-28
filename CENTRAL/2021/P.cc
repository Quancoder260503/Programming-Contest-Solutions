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
const int N = 11;
const int M = 101;
signed main(void)
{
    Vec<4, int> dyn(N, M, M, M);
    for (int u = 1; u < N; u++)
    {
        for (int i = 1; i < M; i++)
        {
            for (int j = 1; j < M; j++)
            {
                for (int k = 1; k < M; k++)
                {
                    dyn[u][i][j][k] = max({dyn[u][i - 1][j][k], dyn[u][i][j - 1][k], dyn[u][i][j][k - 1]}); 
                    if(i >= k && j >= k && k >= u)
                    {
                        dyn[u][i][j][k] = max(dyn[u][i][j][k], i * j); 
                    }
                    if(i >= j && k >= j && j >= u)
                    {
                        dyn[u][i][j][k] = max(dyn[u][i][j][k], i * k);
                    }
                    if(j >= i && k >= i && i >= u)
                    {
                        dyn[u][i][j][k] = max(dyn[u][i][j][k], j * k);
                    }
                    if(i > u)
                    {
                        dyn[u][i][j][k] = max(dyn[u][i][j][k], dyn[u][i - u][j][k] + dyn[u][u][j][k]);
                    }
                    if(j > u)
                    {
                        dyn[u][i][j][k] = max(dyn[u][i][j][k], dyn[u][i][j - u][k] + dyn[u][i][u][k]);
                    }
                    if(k > u)
                    {
                        dyn[u][i][j][k] = max(dyn[u][i][j][k], dyn[u][i][j][k - u] + dyn[u][i][j][u]);
                    }
                }
            }
        }
    }
    int X, Y, Z, U, T; 
    cin >> T;
    while(T--)
    {
        cin >> X >> Y >> Z >> U;
        cout << dyn[U][X][Y][Z]<< '\n'; 
    }
    return 0;
}