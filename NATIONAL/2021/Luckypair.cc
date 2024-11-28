#include "bits/stdc++.h"
using namespace std;
#define lint long long
lint a, b, c, d;
lint ans = 0;
using ulint = unsigned long long;
using ld = long double;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lint get_rand(lint B)
{
    return (ulint)rng() % B;
}
lint mult(lint x, lint y, lint md)
{
    ulint q = (ld)x * y / md;
    lint res = ((ulint)x * y - q * md);
    if (res >= md)
        res -= md;
    if (res < 0)
        res += md;
    return res;
}
lint powMod(lint x, lint p, lint md)
{
    if (p == 0)
        return 1;
    if (p & 1)
        return mult(x, powMod(x, p - 1, md), md);
    return powMod(mult(x, x, md), p / 2, md);
}

bool checkMillerRabin(lint x, lint md, lint s, int k)
{
    x = powMod(x, s, md);
    if (x == 1)
        return true;
    while (k--)
    {
        if (x == md - 1)
            return true;
        x = mult(x, x, md);
        if (x == 1)
            return false;
    }
    return false;
}
bool isPrime(lint x)
{
    if (x == 2 || x == 3 || x == 5 || x == 7)
        return true;
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0)
        return false;
    if (x < 121)
        return x > 1;
    lint s = x - 1;
    int k = 0;
    while (s % 2 == 0)
    {
        s >>= 1;
        k++;
    }
    if (x < 1LL << 32)
    {
        for (lint z : {2, 7, 61})
        {
            if (!checkMillerRabin(z, x, s, k))
                return false;
        }
    }
    else
    {
        for (lint z : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
        {
            if (!checkMillerRabin(z, x, s, k))
                return false;
        }
    }
    return true;
}

lint gcd(lint x, lint y)
{
    return y == 0 ? x : gcd(y, x % y);
}
void pollard(lint x, vector<lint> &ans)
{
    if (isPrime(x))
    {
        ans.push_back(x);
        return;
    }
    lint c = 1;
    while (true)
    {
        c = 1 + get_rand(x - 1);
        auto f = [&](lint y)
        {
            lint res = mult(y, y, x) + c;
            if (res >= x)
                res -= x;
            return res;
        };
        lint y = 2;
        int B = 100;
        int len = 1;
        lint g = 1;
        while (g == 1)
        {
            lint z = y;
            for (int i = 0; i < len; i++)
            {
                z = f(z);
            }
            lint zs = -1;
            int lft = len;
            while (g == 1 && lft > 0)
            {
                zs = z;
                lint p = 1;
                for (int i = 0; i < B && i < lft; i++)
                {
                    p = mult(p, abs(z - y), x);
                    z = f(z);
                }
                g = gcd(p, x);
                lft -= B;
            }
            if (g == 1)
            {
                y = z;
                len <<= 1;
                continue;
            }
            if (g == x)
            {
                g = 1;
                z = zs;
                while (g == 1)
                {
                    g = gcd(abs(z - y), x);
                    z = f(z);
                }
            }
            if (g == x)
                break;
            assert(g != 1);
            pollard(g, ans);
            pollard(x / g, ans);
            return;
        }
    }
}
// return list of alint prime factors of x (can have duplicates)
vector<lint> factorize(lint x)
{
    vector<lint> ans;
    for (lint p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43})
    {
        while (x % p == 0)
        {
            x /= p;
            ans.push_back(p);
        }
        if (x == 1)
            break;
    }
    if (x != 1)
    {
        pollard(x, ans);
    }
    sort(ans.begin(), ans.end());
    return ans;
}
signed main(void)
{
    clock_t tStart = clock();
    int n;
    cin >> n;
    map<int, lint> dyn;
    lint ans = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        vector<lint> factor = factorize(x);
        sort(factor.begin(), factor.end());
        factor.erase(unique(factor.begin(), factor.end()), factor.end());
        lint prod = 1;
        for (auto f : factor)
        {
            prod = f * prod;
        }
        ans += dyn[prod];
        dyn[prod]++;
    }
    cout << ans << '\n'; 
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}
// Complexity : O(Nsqrt(N) where N ~ 1e6))