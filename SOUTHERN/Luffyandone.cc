#include "bits/stdc++.h"
using namespace std;
#define int64_t long long 
int main(void)
{ 
    int64_t N, M, X, Y, K;
    while(cin >> M >> N >> X >> Y >> K)
    {
        int ret = 0;
        auto ctr = [&](int64_t m, int64_t n, int64_t d)
        {
            int64_t L = min(n, max(1LL, d - m + 1));
            int64_t R = min(n, d);
            int64_t ret =  (R - L + 1) * (R + L) / 2; 
            int64_t tmp = min(m, d) - (R - L + 1); 
            return ret += (tmp > 0 ? tmp * n : 0); 
        }; 
        auto solve = [&](int64_t d)
        {
            return ctr(X, Y, d) + ctr(X, N - Y + 1, d) + ctr(M - X + 1, Y, d) + ctr(M - X + 1, N - Y + 1, d) + 1 - min(X, d) - min(M - X + 1, d) - min(Y, d) - min(N - Y + 1, d); 
        }; 
        int64_t L = 0; 
        int64_t R = 7e9;
        K = M * N - K + 1; 
        while(L < R)
        {
            int64_t mid = (L + R) / 2;
            if(solve(mid + 1) >= K) R = mid; 
            else L = mid + 1;  
        } 
        cout << L << '\n';
    }
    return 0;  
}