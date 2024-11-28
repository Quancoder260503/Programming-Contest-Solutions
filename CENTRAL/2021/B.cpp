#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 2e5 + 10;
const int mod = 1e9 + 7;
int n;
lint arr[MAXN];
lint pr[MAXN], sf[MAXN];
signed main(void)
{
    cin >> n;
    int neg = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        neg += (arr[i] < 0);
    }
    sort(arr + 1, arr + n + 1);
    reverse(arr + 1, arr + n + 1);
    lint ans = 1;
    int at = 0;
    for (at = 1; at <= n; at++)
    {
        if (arr[at] <= 0)
            break;
        ans = 1LL * ans % mod * arr[at] % mod;
    }
    if (arr[at] == 0)
    {
        if (neg % 2 == 0)
        {
            for (int i = at + 1; i <= n; i++)
            {
                ans = ans % mod * arr[i] % mod;
            }
        }
        else
        {
            ans = 0;
        }
    }
    else
    {
        if (neg % 2 == 0)
        {
            for (int i = at; i <= n; i++)
            {
                ans = ans % mod * arr[i] % mod;
            }
        }
        else
        {
            for (int i = at + 1; i <= n; i++)
            {
                ans = ans % mod * arr[i] % mod;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}