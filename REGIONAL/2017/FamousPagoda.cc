#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int64_t INF = 1e14;
const int maxf = 5000;

int n, m, k;
int64_t psum[maxf], psum2[maxf], a[maxf], dyn[maxf][maxf];

int64_t cost1(int i, int j)
{
    int xmid = (i + j) / 2, ymid = (i + j + 1) / 2;
    return min(psum[j] + psum[i - 1] - 2 * psum[xmid] + 1LL * a[xmid] * (2 * xmid - j - i + 1),
               psum[j] + psum[i - 1] - 2 * psum[ymid] + 1LL * a[ymid] * (2 * ymid - j - i + 1));
}

int64_t cost2(int i, int j)
{
    int64_t x1 = ceil(1.0 * (psum[j] - psum[i - 1]) / (j - i + 1));
    int64_t x2 = floor(1.0 * (psum[j] - psum[i - 1]) / (j - i + 1));
    int64_t a = (psum2[j] - psum2[i - 1]);
    int64_t b = 2 * (psum[j] - psum[i - 1]);
    return min(a - 1LL * b * x1 + 1LL * x1 * x1 * (j - i + 1), a - 1LL * b * x2 + 1LL * x2 * x2 * (j - i + 1));
}

void DP1(int l, int r, int optl, int optr, int now)
{
    if (l > r)
        return;
    int mid = (l + r) / 2;
    pair<int64_t, int> best = {INT64_MAX, -1};
    for (int i = optl; i <= min(mid, optr); i++)
    {
        best = min(best, {dyn[now - 1][i - 1] + cost1(i, mid), i});
    }
    dyn[now][mid] = best.first;
    int opt = best.second;
    DP1(l, mid - 1, optl, opt, now);
    DP1(mid + 1, r, opt, optr, now);
    return;
}

void DP2(int l, int r, int optl, int optr, int now)
{
    if (l > r)
        return;
    int mid = (l + r) / 2;
    pair<int64_t, int> best = {INT64_MAX, -1};
    for (int i = optl; i <= min(mid, optr); i++)
    {
        best = min(best, {dyn[now - 1][i - 1] + cost2(i, mid), i});
    }
    dyn[now][mid] = best.first;
    int opt = best.second;
    DP2(l, mid - 1, optl, opt, now);
    DP2(mid + 1, r, opt, optr, now);
    return;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        psum[i] = psum[i - 1] + a[i];
        psum2[i] = psum2[i - 1] + 1LL * a[i] * a[i];
    }
    if (k == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            dyn[0][i] = cost1(1, i);
        }
        for (int i = 1; i < m; i++)
            DP1(1, n, 1, n, i);
        cout << dyn[m - 1][n] << '\n';
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            dyn[0][i] = cost2(1, i);
        }
        for (int i = 1; i < m; i++)
            DP2(1, n, 1, n, i);
        cout << dyn[m - 1][n] << '\n';
    }
    return 0;
}