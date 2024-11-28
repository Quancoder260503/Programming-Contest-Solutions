#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, M, K;
    while (cin >> N >> M)
    {
        vector<vector<pair<int, int>>> adj(N);
        for (int i = 0; i < M; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].push_back({v, -1});
            adj[v].push_back({u, -1});
        }
        cin >> K;
        for (int i = 0; i < K; i++)
        {
            int t, u, v;
            cin >> t >> u >> v;
            --u, --v;
            adj[u].push_back({v, t});
            adj[v].push_back({u, t});
        }
        auto dijsktra = [&](int src)
        {
            using T = pair<int, int>;
            priority_queue<T, vector<T>, greater<T>> pq;
            vector<int> dyn(N, -1);
            dyn[src] = 0;
            pq.push({0, src});
            while (pq.size())
            {
                auto [dist_u, u] = pq.top();
                pq.pop();
                if (dyn[u] != dist_u)
                    continue;
                for (auto [v, cost] : adj[u])
                {
                    int dist_from = max(dyn[u] + 1, cost);
                    if (dyn[v] < 0 || dyn[v] > dist_from)
                    {
                        dyn[v] = dist_from;
                        pq.push({dist_from, v});
                    }
                }
            }
            return dyn[N - 1];
        };
        cout << dijsktra(0) << '\n';
    }
    return 0;
}