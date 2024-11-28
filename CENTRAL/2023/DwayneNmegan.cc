#include "bits/stdc++.h"
using namespace std;
#define Lint long long
vector<vector<int>> adj;
int n;
struct BiconnectedComponent
{
    vector<int> low, num, s;
    vector<vector<int>> components;
    int counter;

    BiconnectedComponent() : low(n, -1), num(n, -1), counter(0)
    {
        for (int i = 0; i < n; i++)
            if (num[i] < 0)
                dfs(i, 1);
    }

    void dfs(int x, int isRoot)
    {
        low[x] = num[x] = ++counter;
        if (adj[x].empty())
        {
            components.push_back(vector<int>(1, x));
            return;
        }
        s.push_back(x);
        for (int i = 0; i < (int)adj[x].size(); i++)
        {
            int y = adj[x][i];
            if (num[y] > -1)
                low[x] = min(low[x], num[y]);
            else
            {
                dfs(y, 0);
                low[x] = min(low[x], low[y]);

                if (isRoot || low[y] >= num[x])
                {
                    components.push_back(vector<int>(1, x));
                    while (1)
                    {
                        int u = s.back();
                        s.pop_back();
                        components.back().push_back(u);
                        if (u == y)
                            break;
                    }
                }
            }
        }
    }
};
signed main(void)
{
    int N, M;
    while (cin >> N >> M)
    {
        adj.resize(N * M + 2);
        for(int i = 0; i < N * M; i++)
        {
            adj[i].clear(); 
        }
        vector<vector<char>> g(N, vector<char>(M));
        int p = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cin >> g[i][j];
                p += (g[i][j] == '.');
            }
        }
        auto to = [&](int i, int j)
        {
            return i * M + j;
        };
        auto valid = [&](int i, int j)
        {
            return (0 <= i && i < N && 0 <= j && j < M && g[i][j] == '.');
        };
        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (valid(i, j))
                {
                    for (int k = 0; k < 4; k++)
                    {
                        int px = dx[k] + i;
                        int py = dy[k] + j;
                        if (valid(px, py))
                        {
                            adj[to(i, j)].push_back(to(px, py));
                        }
                    }
                }
            }
        }
        n = N * M + 2;
        BiconnectedComponent bc;
        Lint ret = 1LL * p * (p - 1);
        for(auto comp : bc.components)
        {
            ret = ret - 1LL * (comp.size()) * (comp.size() - 1); 
        }
        cout << ret << '\n';
    }
    return 0;
}
/*
4 5
#...#
#.##.
..##.
..##.
*/