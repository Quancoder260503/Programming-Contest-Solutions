#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 1e9 + 7;
const int MAXN = (int)2e2 + 10;
char g[MAXN][MAXN];
int n, m, h;
int N;
struct matrix
{
    lint arr[MAXN][MAXN];
    void init()
    {
        memset(arr, 0, sizeof(arr));
    }
    void print()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    lint get()
    {
        lint ans = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                ans = (ans + arr[i][j] + mod) % mod;
            }
        }
        return ans;
    }
};
matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    c.init();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                c.arr[i][j] = (c.arr[i][j] + 1LL * a.arr[i][k] % mod * b.arr[k][j] % mod + mod) % mod;
            }
        }
    }
    return c;
}
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
map<char, int> dir;
bool valid(int i, int j)
{
    return (0 <= i && i < n && 0 <= j && j < m && g[i][j] != '#');
}
int to(int i, int j)
{
    return i * m + j;
}
signed main(void)
{
    cin >> n >> m >> h;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
        }
    }
    dir['R'] = 0;
    dir['L'] = 1;
    dir['U'] = 2;
    dir['D'] = 3;
    dir['+'] = 4;
    matrix s, res;
    s.init();
    res.init();
    N = n * m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (g[i][j] == '#')
                continue;
            int direc = dir[g[i][j]];
            if (direc == 4)
            {
                for (int k = 0; k < direc; k++)
                {
                    int px = i + dx[k];
                    int py = j + dy[k];
                    if (valid(px, py))
                    {
                        s.arr[to(i, j)][to(px, py)] += 1;
                    }
                }
            }
            else
            {
                int px = i + dx[direc];
                int py = j + dy[direc];
                if (valid(px, py))
                {
                    s.arr[to(i, j)][to(px, py)] += 1;
                }
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        res.arr[i][i] = 1;
    }
    while (h)
    {
        if (h & 1)
        {
            res = res * s;
        }
        s = s * s;
        h = h / 2;
    }
    cout << res.get() << '\n';
    return 0;
}