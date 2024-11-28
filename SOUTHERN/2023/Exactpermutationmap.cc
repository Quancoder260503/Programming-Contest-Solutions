#include "bits/stdc++.h"
using namespace std;
const int MAX = 3000; 
const int64_t INF = 1e18; 
int64_t dyn[MAX][MAX];
int64_t memo(int sum, int ropen)
{
    if(sum == 0 && ropen == 0) return 1; 
    if(dyn[sum][ropen] != -1) return dyn[sum][ropen]; 
    int64_t &ret = dyn[sum][ropen]; 
    ret = 0; 
    if(ropen  > 0) ret  = memo(sum + 1, ropen - 1); 
    if(sum    > 0) ret += memo(sum - 1, ropen);
    if(ret >= INF) ret = INF; 
    return ret;  
}
int main(void)
{ 
    int N, K, T; 
    memset(dyn, -1, sizeof(dyn)); 
    while(cin >> T >> N)
    {
        if(T == 1)
        {
            cin >> K; 
            vector<int>ret(2 * N); 
            int open, close, tot; 
            open = close = tot = 0; 
            for(int i = 0; i < 2 * N; i++)
            {
                if(open < N && memo(tot + 1, N - 1 - open) >= K)
                {
                    ret[open] = i + 1;
                    open++;
                    tot++; 
                }
                else 
                {
                    if(open < N) K = K - memo(tot + 1, N - 1 - open); 
                    ret[N + close] = i + 1; 
                    close++; 
                    tot--; 
                }
            }
            for(auto it : ret) cout << it << " "; 
            cout << '\n'; 
        }
        else
        {
            vector<int> a(2 * N);
            for (int i = 0; i < 2 * N; i++) cin >> a[i];
            int open, tot, pos, ret; 
            open = tot = ret = 0;
            pos = 1; 
            for(int i = 0; i < N; i++)
            {
                while(pos < a[i])
                {
                    ret += memo(tot + 1, N - 1 - open);
                    pos++; 
                    tot--; 
                }
                open++; 
                tot++; 
                pos++; 
            }
            cout << ret + 1 << '\n'; 
        }
    }
    return 0; 
}