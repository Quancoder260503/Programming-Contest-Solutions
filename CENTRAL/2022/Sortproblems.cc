#include "bits/stdc++.h"
using namespace std;
#define Lint long long
struct fenwick
{
    int N;
    vector<Lint> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    Lint sum(int i)
    {
        Lint c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    void upd(int i, Lint dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
}; 
signed main(void)
{
    int N, K; 
    while(cin >> N >> K)
    {
        vector<pair<int,int>>sortme; 
        for(int i = 0; i < N; i++)
        {
            int a, b;
            cin >> a >> b; 
            sortme.push_back({a, b}); 
        }
        sort(sortme.begin(), sortme.end()); 
        vector<vector<Lint>>dyn(N + 1, vector<Lint>(K + 1, 0));
        for(auto [_, i] : sortme)
        {
            dyn[i][0] = 1; 
        }
        for(int j = 1; j < K; j++)
        {
            fenwick fenw;
            fenw.init(N + 1);
            for(auto [_, i] : sortme)
            {
                dyn[i][j] = fenw.sum(i - 1);
                fenw.upd(i, dyn[i][j - 1]);
            }
        }
        Lint ret = 0; 
        for(int i = 0; i < N; i++)
        {
            ret += dyn[i + 1][K - 1]; 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}