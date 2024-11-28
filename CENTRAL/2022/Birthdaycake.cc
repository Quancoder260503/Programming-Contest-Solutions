#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int mod = 1e9 + 7;
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
    int R, C, N;
    while (cin >> R >> C >> N)
    {
        // f(r, c, k, i) = f(r1, c, k - 1, i + 1) + f(r, c1, k - 1, i + 1)
        vector<vector<int>> prefix(R, vector<int>(C, 0));
        vector<int> arr(N);
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                int x;
                cin >> x;
                prefix[i][j] += x;
                if (i > 0 && j > 0)
                    prefix[i][j] -= prefix[i - 1][j - 1];
                if (i > 0)
                    prefix[i][j] += prefix[i - 1][j];
                if (j > 0)
                    prefix[i][j] += prefix[i][j - 1];
            }
        }
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }
        auto get_sum = [&](int r, int c, int r2, int c2)
        {
            return prefix[r2][c2] - (r ? prefix[r - 1][c2] : 0) - (c ? prefix[r2][c - 1] : 0) + (r && c ? prefix[r - 1][c - 1] : 0);
        };
        Vec<3, Lint> dyn(R, C, N, -1);
        function<Lint(int, int, int)> doit;
        doit = [&](int r, int c, int at) -> Lint
        {
            if (at == N - 1) 
            {
                return get_sum(r, c, R - 1, C - 1) <= arr[at]; 
            }
            if (dyn[r][c][at] != -1) return dyn[r][c][at];
            Lint &ret = dyn[r][c][at];
            ret = 0;
            for (int i = r + 1; i < R; i++)
            {
                if (get_sum(r, c, i - 1, C - 1) <= arr[at])
                {
                    ret += doit(i, c, at + 1);
                    ret %= mod;
                }
            }
            for (int i = c + 1; i < C; i++)
            {
                if (get_sum(r, c, R - 1, i - 1) <= arr[at])
                { 
                    ret += doit(r, i, at + 1);
                    ret %= mod;
                }
            }
            return ret;
        };
        cout << doit(0, 0, 0) << '\n';
    }
    return 0;
}