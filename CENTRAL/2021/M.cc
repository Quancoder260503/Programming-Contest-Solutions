#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
#define lint long long
signed main(void)
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<int> fa(n);
        vector<int> comp(n);
        iota(fa.begin(), fa.end(), 0);
        fill(comp.begin(), comp.end(), 1);
        function<int(int)>find; 
        function<void(int, int)>unite; 
        find = [&](int u)
        {
            return u == fa[u] ? u : fa[u] = find(fa[u]); 
        }; 
        unite = [&](int u, int v)
        {
            u = find(u), v = find(v);
            if(u == v) return;
            if(comp[u] < comp[v]) swap(u, v); 
            comp[u] += comp[v];
            fa[v] = u; 
        }; 
        for (int i = 0; i < m; i++)
        {
            int u, v; 
            cin >> u >> v;
            unite(u, v); 
        }
        vector<lint>fact(n + 1, 0); 
        fact[0] = 1; 
        for(int i = 1; i <= n; i++)
        {
            fact[i] = fact[i - 1] % mod * i % mod; 
        }
        lint ans = 0; 
        for(int i = 0; i < n; i++)
        {
            if(fa[i] == i && comp[i] > 2)
            {
                ans = (ans + fact[comp[i]] + mod) % mod; 
            }
        }
        cout << ans << '\n'; 
    }
    return 0;
}