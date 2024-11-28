#include "bits/stdc++.h" 
using namespace std;
#define Lint long long
const int MAXN = (int)1e5 + 10;
const int K = 23;
vector<pair<int,int>>adj[MAXN];
int up[K][MAXN];
int dep[MAXN];
void dfs(int u, int p)
{
    for (int i = 1; i < K; i++)
    {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i].first;
        if (v == p) continue;
        dep[v] = dep[up[0][v] = u] + 1;
        dfs(v, u);
    }
    return;
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i < K; i++)
    {
        if (d & (1 << i))
        {
            u = up[i][u];
        }
    }
    if (u == v)
        return u;
    for (int i = K - 1; i >= 0; i--)
    {
        int tu = up[i][u], tv = up[i][v];
        if (tu != tv)
            u = tu, v = tv;
    }
    return up[0][u];
}
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>C1, C2; 
        vector<int>f(N); 
        for(int i = 0; i < N - 1; i++)
        {
            int u, v, c1, c2; 
            cin >> u >> v >> c1 >> c2; 
            C1.push_back(c1);
            C2.push_back(c2); 
            --u, --v;
            adj[u].push_back({v, i});
            adj[v].push_back({u, i}); 
        }
        dfs(0, -1);
        for(int i = 0; i + 1 < N; i++)
        {
            f[i]++; 
            f[i + 1]++; 
            f[LCA(i, i + 1)] -= 2; 
        }
        function<void(int, int)>doit; 
        doit = [&](int u, int p)
        {
            for(auto [v, _] : adj[u])
            {
                if(v == p) continue; 
                doit(v, u); 
                f[u] += f[v]; 
            }
        };
        doit(0, -1); 
        function<void(int, int)>doit2;
        Lint ret = 0;
        doit2 = [&](int u, int p)
        {
            for(auto [v, at] : adj[u])
            {
                if(v == p) continue;
                ret += min(1LL * C2[at], 1LL * C1[at] * f[v]); 
                doit2(v, u); 
            }
        };
        doit2(0, -1);
        cout << ret << '\n';  
    }
    return 0;
}