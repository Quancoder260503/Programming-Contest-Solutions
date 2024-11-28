#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = (int)(1 << 8);
const int mod = 1e9 + 7;
int n, k;
lint m;
lint dp[MAXN][MAXN];
lint mat[MAXN][MAXN];
map<lint, int> block;
// 0 is filled, 1 is unfilled
struct matrix
{
    lint arr[MAXN][MAXN];
    void print()
    {
        for (int i = 0; i < (1 << n); i++)
        {
            for (int j = 0; j < (1 << n); j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
};
void reset(matrix &c)
{
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            c.arr[i][j] = 0;
        }
    }
}
void f(int c, int mask, int fmask)
{
    if (c == n)
    {
        dp[mask][fmask]++;
        return;
    }
    else
    {
        if (mask & (1 << c))
        {
            f(c + 1, mask, fmask);
        }
        else
        {
            f(c + 1, mask, fmask | (1 << c));
            if (c + 1 < n && !(mask & (1 << c)) && !(mask & (1 << (c + 1))))
            {
                f(c + 2, mask, fmask);
            }
        }
    }
}
void f2(int c, int mask, int fmask, int bmask)
{
    if (c == n)
    {
        dp[mask][fmask]++;
        return;
    }
    else
    {
        if (mask & (1 << c))
        {
            if (bmask & (1 << c))
                f2(c + 1, mask, fmask, bmask);
        }
        else
        {
            if (bmask & (1 << c))
                f2(c + 1, mask, fmask | (1 << c), bmask);
            else
                f2(c + 1, mask, fmask, bmask);
            if (c + 1 < n && !(mask & (1 << c)) && !(mask & (1 << (c + 1))))
            {
                if ((bmask & (1 << c)) && (bmask & (1 << (c + 1))))
                {
                    f2(c + 2, mask, fmask, bmask);
                }
            }
        }
    }
}
matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    reset(c);
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            for (int k = 0; k < (1 << n); k++)
            {
                c.arr[i][j] = (c.arr[i][j] + 1LL * a.arr[i][k] % mod * b.arr[k][j] % mod + mod) % mod;
            }
        }
    }
    return c;
}
signed main(void)
{
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
    {
        int r;
        lint c;
        cin >> r >> c;
        --r, --c;
        block[c] |= (1 << r);
    }
    for (int mask = 0; mask < (1 << n); mask++)
    {
        f(0, mask, 0);
    }
    matrix coef;
    matrix res;
    reset(res);
    reset(coef);
    for (int i = 0; i < (1 << n); i++)
    {
        res.arr[i][i] = 1;
        for (int j = 0; j < (1 << n); j++)
        {
            coef.arr[i][j] = dp[i][j];
        }
    }
    lint last = -1;
    for (auto [c, bmask] : block)
    {
        lint dist = (c - 1) - (last + 1) + 1;
        matrix nowc;
        reset(nowc);
        for (int i = 0; i < (1 << n); i++)
        {
            for (int j = 0; j < (1 << n); j++)
            {
                nowc.arr[i][j] = coef.arr[i][j];
                dp[i][j] = 0;
            }
        }
        while (dist)
        {
            if (dist & 1)
                res = res * nowc;
            nowc = nowc * nowc;
            dist = dist / 2;
        }
        bmask = ((1 << n) - 1) xor bmask;
        for (int mask = 0; mask < (1 << n); mask++)
        {
            f2(0, mask, 0, bmask);
        }
        for (int i = 0; i < (1 << n); i++)
        {
            for (int j = 0; j < (1 << n); j++)
            {
                nowc.arr[i][j] = dp[i][j];
            }
        }
        res = res * nowc;
        last = c;
    }
    m = m - (last + 1);
    while (m)
    {
        if (m & 1)
            res = res * coef;
        coef = coef * coef;
        m = m / 2;
    }
    cout << res.arr[0][0] << '\n';
    return 0;
}