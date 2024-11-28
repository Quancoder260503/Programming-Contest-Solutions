#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int T;
    cin >> T;
    while (T--)
    {
        int N, M, K, a, b;
        string S;
        cin >> N >> M >> a >> b;
        vector<vector<int>> adj(N), radj(N);
        cin >> S;
        --a, --b;
        for (int i = 0; i < M; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].push_back(v);
            radj[v].push_back(u);
        }
        vector<int> dyn(N, -1), dyn2(N, -1);
        int _, __;
        cin >> _ >> __ >> K;
        for (int i = 0; i < K * 5; i++)
        {
            int _;
            cin >> _;
        }
        function<int(int)> doit;
        function<int(int)> doit2; 
        doit = [&](int u) -> int
        {
            if (dyn[u] >= 0) return dyn[u];
            set<int> g;
            for (auto v : adj[u])
            {
                g.insert(doit(v));
            }
            int mex = 0;
            while (g.count(mex)) mex++;
            return dyn[u] = mex;
        };
        doit2 = [&](int u) -> int
        {
            if (dyn2[u] >= 0) return dyn2[u];
            set<int> g;
            for (auto v : radj[u])
            {
                g.insert(doit2(v));
            }
            int mex = 0;
            while (g.count(mex)) mex++;
            return dyn2[u] = mex;
        };
        int ret = doit(a) xor doit2(b) xor (K & 1);
        cout << (ret ? "YES" : "NO") << '\n';
    }
    return 0;
}