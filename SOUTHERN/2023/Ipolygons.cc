#include "bits/stdc++.h"
using namespace std;
const int MAX = 5000; 
const int mod = 1e9 + 7;
int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (long long)res * tmp % mod;
        }
        tmp = (long long)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}
int main(void)
{
    int N;
    while (cin >> N) 
    {
        vector<int>L(N); 
        for(int i = 0; i < N; i++) cin >> L[i]; 
        sort(L.begin(), L.end()); 
        vector<vector<int64_t>>dyn(N + 1, vector<int64_t>(MAX + 1, 0)); 
        dyn[0][0] = 1; 
        int64_t ret = 0; 
        for(int i = 1; i <= N; i++) 
        {
            if(i > 2)
            {
                for(int j = 1; j <= L[i - 1]; j++) ret = (ret + mod - dyn[i - 1][j]) % mod; 
                ret = (ret + fpow(2, i - 1) - 1 + mod) % mod; 
            }
            for(int j = 0; j < MAX; j++)
            {
                dyn[i][j] = dyn[i - 1][j]; 
                if(j >= L[i - 1]) dyn[i][j] = (dyn[i][j] + dyn[i - 1][j - L[i - 1]] + mod) % mod;    
            }
        }
        cout << ret << '\n'; 
    }
    return 0;
}