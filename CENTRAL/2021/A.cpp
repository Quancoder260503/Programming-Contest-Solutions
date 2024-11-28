#include "bits/stdc++.h"
using namespace std;
const int INF = 1000000000;
const int MAXN = 2e2 + 10;
int n, m, t;
const int LOG = 24;
int up[LOG][MAXN];
vector<int> adj[MAXN];
int dp[LOG][MAXN];
int dep[MAXN];
int arr[MAXN][MAXN];
int res[MAXN][MAXN];
void dfs(int u, int p)
{
    for (int i = 1; i < LOG; i++)
    {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int i = 0; i < adj[u].size(); i++)
    {
        auto v = adj[u][i];
        if(v == p) continue; 
        dp[0][v] = arr[u][v];
        dep[v] = dep[up[0][v] = u] + 1;
        dfs(v, u);
    }
    return;
}
int jump(int dist, int u)
{
    for (int i = 0; i < LOG; i++)
    {
        if (dist & (1 << i))
            u = up[i][u];
    }
    return u;
}

int calc(int dist, int u)
{
    int opt = (dist == 0 ? 0 : INT_MAX);
    for (int i = 0; i < LOG; i++)
    {
        if (dist & (1 << i)) 
        {
            opt = min(opt, dp[i][u]);
            u = up[i][u];
        }
    }
    return opt;
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int dist = dep[u] - dep[v];
    u = jump(dist, u);
    if (u == v)
        return u;
    for (int i = LOG - 1; i >= 0; i--)
    {
        int tu = up[i][u];
        int tv = up[i][v];
        if (tu != tv)
        {
            u = tu;
            v = tv;
        }
    }
    return up[0][u];
}
int fa[MAXN];
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
int calc2(int u, int v)
{
    if(dep[u] > dep[v]) swap(u, v); 
    int anc = LCA(u, v);
    if(anc == u) return calc(dep[v] - dep[u], v); 
    else return min(calc(dep[u] - dep[anc], u), calc(dep[v] - dep[anc], v));
}
void solve()
{
    cin >> n;
    vector<pair<int, pair<int, int>>> edge;
    for(int i = 0; i < n; i++)
    {
        adj[i].clear(); 
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
            if (i < j)
            {
                edge.push_back({arr[i][j], {i, j}});
            }
        }
    }
    sort(edge.rbegin(), edge.rend());
    memset(dp, 63, sizeof(dp));
    memset(res, 0, sizeof(res));
    iota(fa, fa + n, 0);
    for (auto e : edge)
    {
        auto v = e.second;
        if (find(v.first) == find(v.second))
            continue;
        fa[find(v.first)] = find(v.second);
        adj[v.first].push_back(v.second);
        adj[v.second].push_back(v.first);
        res[v.first][v.second] = res[v.second][v.first] = e.first;
    }
    dfs(0, -1);
    for (int i = 1; i < LOG; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][up[i - 1][j]]);
        }
    }
    bool chk = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //cout << calc2(i, j) << " " << arr[i][j] << endl;
            chk = chk & (calc2(i, j) == arr[i][j]);
        }
    }
    printf("Case #%d: ", t);
    puts(chk ? "YES" : "NO");
    if (chk)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << res[i][j] << " ";
            }
            cout << '\n';
        }
    }
    return;
}
signed main(void)
{
    int T;
    cin >> T;
    for (t = 1; t <= T; t++)
    {
        solve();
    }
    return 0;
}