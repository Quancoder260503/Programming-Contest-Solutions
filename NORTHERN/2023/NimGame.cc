#include "bits/stdc++.h"

using namespace std;

const int maxf = (1 << 20);
const int LOG = 12;
const int mod = 1e9 + 9;

int64_t roota, rootb, inv3; 

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1) {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

int prt()
{
    vector<int> dvs;
    for (int i = 2; i * i < mod; i++) {
        if ((mod - 1) % i) continue;
        dvs.push_back(i);
        if (i * i != mod - 1) dvs.push_back((mod - 1) / i);
    }
    for (int i = 2; i < mod; i++)
    {
        int flag = 1;
        for (int j = 0; j < (int)dvs.size(); j++){ 
            if (fpow(i, dvs[j]) == 1) {
                flag = 0;
                break;
            }
        }
        if (flag) return i;
    }
    assert(0);
    return -1;
}

void get_root(void) {
    roota = 115381398;
    rootb = 884618610;
    return;
}

void get_mult(int64_t &a, int64_t &b, int64_t &c) { 
    int64_t x = (a + b + c) % mod;
    int64_t y = (a + b % mod * roota % mod + c % mod * rootb % mod) % mod;
    int64_t z = (a + b % mod * rootb % mod + c % mod * roota % mod) % mod; 
    a = x, b = y, c = z; 
    return; 
}

void get_rev_mult(int64_t &a, int64_t &b, int64_t &c) {
    int64_t x = (a + b + c) % mod;
    int64_t y = (a + b % mod * rootb % mod + c % mod * roota % mod) % mod;
    int64_t z = (a + b % mod * roota % mod + c % mod * rootb % mod) % mod;
    x = x % mod * inv3 % mod; 
    y = y % mod * inv3 % mod; 
    z = z % mod * inv3 % mod; 
    a = x, b = y, c = z;
    return; 
}

void FWHT(int64_t *P, int deg, bool invert) {
    for (int len = 1; 3 * len <= deg; len = len * 3) {
        for (int i = 0; i < deg; i += 3 * len) {
            for (int j = 0; j < len; j++) {
                if(!invert) { 
                    get_mult(P[i + j], P[i + j + len], P[i + j + 2 * len]);  
                }
                else {
                    get_rev_mult(P[i + j], P[i + j + len], P[i + j + 2 * len]);
                } 
            }
        }
    }
    return; 
}

int64_t P[maxf + 10]; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    get_root(); 
    inv3 = fpow(3, mod - 2); 
    int64_t n, k; 
    cin >> n >> k; 
    for(int i = 0, x; i < n; i++) { 
        cin >> x;
        int acc = 0; 
        for(int j = 0; j < LOG; j++) { 
            if((1 << j) & x) acc += pow(3, j); 
        }
        P[acc]++; 
    }
    int ctr = 0; 
    int deg = pow(3, 10); 
    FWHT(P, deg, 0);
    for(int i = 0; i < deg; i++) {
        P[i] = fpow(P[i], k);
    }
    FWHT(P, deg, 1); 
    cout << P[0] << '\n'; 
    return 0;
}