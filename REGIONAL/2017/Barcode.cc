#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e6 + 10;
int n, mod;

int64_t fib[maxf], prime[maxf];

void init(int n)
{
    fib[1] = fib[0] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    }
    return;
}

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}



int64_t C(int n) {
    for (int i = n + 2; i <= 2 * n; i += 2) {
        int x = i;
        for (int j = 2; j * j <= x; j++) {
            while (x % j == 0) {x = x / j; prime[j]++; } 
        }
        if (x > 1) prime[x]++;
    }
    for (int i = 2; i <= n; i += 2) {
        int x = i;
        for (int j = 2; j * j <= x; j++) {
            while (x % j == 0) {x = x / j; prime[j]--; }
        }
        if (x > 1) prime[x]--; 
    }
    int64_t ret = 1;
    for(int i = 1; i <= n; i++) if(prime[i]) { 
        ret = ret % mod * fpow(i, prime[i]) % mod; 
        prime[i] = 0; 
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        cin >> n >> mod;
        init(n + 2);
        int64_t ret = 0;
        if (n % 2 == 0) {
            ret = (C(n) - (n / 2 + 1) % mod + mod) % mod;
        }
        ret = (ret + fib[n + 1]) % mod;
        cout << ret << '\n';
    }
    return 0;
}