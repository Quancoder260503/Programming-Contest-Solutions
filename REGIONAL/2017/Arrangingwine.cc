#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e6 + 10; 
const int mod = 1e9 + 7; 

int64_t ifact[maxf], fact[maxf], w, r, d; 

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

void init(void) {
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        fact[i] = fact[i - 1] * i % mod; 
        ifact[i] = ifact[i - 1] * fpow(i, mod - 2) % mod; 
    } 
    return; 
}

int64_t C(int64_t n, int64_t k) { 
    if(n < k) return 0;
    return fact[n] % mod * ifact[n - k] % mod * ifact[k] % mod; 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init(); 
    cin >> r >> w >> d; 
    int64_t ret = 0; 
    int sign = 1; 
    for(int i = 0; i <= w + 1; i++) { 
        ret = (ret + mod + C(w + 1, i) % mod * C(w + r - 1LL * i * d - i, w) % mod * sign) % mod;
        sign = -sign;  
    }   
    cout << ret << '\n'; 
    return 0; 
}