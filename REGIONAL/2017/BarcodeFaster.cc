#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;

int n, ctr, mod;
int64_t fib[maxf], vis[maxf], prime[maxf]; 

void sieve(void) { 
    vis[1] = true;
    ctr = 0; 
    for(int i = 1; i < maxf; i++) { 
        if(!vis[i]) { 
            prime[ctr++] = i;
            for(int j = 2 * i; j < maxf; j += i) { 
                vis[j] = true; 
            } 
        }
    }
    return; 
}

void init(int n) {
    fib[1] = fib[0] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    }
    return;
}

int64_t fpow(int64_t a, int64_t k) {
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

int64_t f(int n, int p) { 
    if(n < p) return 0; 
    return n / p + f(n / p, p); 
}

int64_t C(int n){
    int64_t ret = 1;  
    for(int i = 0; i < ctr && prime[i] <= n; i++) { 
        ret = ret % mod * fpow(prime[i], f(n, prime[i]) - 2 * f(n / 2, prime[i])) % mod; 
    }
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    sieve(); 
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