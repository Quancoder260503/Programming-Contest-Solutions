#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int64_t INF = 1e16;
const int maxf = 1002;

template <typename T>
pair<T, vector<int>> Hungarian(int n, int m, T c[][maxf]) {
    vector<T> v(m), dist(m);
    vector<int> L(n, -1), R(m, -1);
    vector<int> index(m), prev(m);
    auto getc = [&](int i, int j)
    { return c[i][j] - v[j]; };
    iota(index.begin(), index.end(), 0);
    for (int f = 0; f < n; ++f)
    {
        for (int j = 0; j < m; ++j)
        {
            dist[j] = getc(f, j), prev[j] = f;
        }
        T w = 0;
        int j, l = 0, s = 0, t = 0;
        while (true)
        {
            if (s == t)
            {
                l = s, w = dist[index[t++]];
                for (int k = t; k < m; ++k)
                {
                    j = index[k];
                    T h = dist[j];
                    if (h <= w)
                    {
                        if (h < w)
                            t = s, w = h;
                        index[k] = index[t], index[t++] = j;
                    }
                }
                for (int k = s; k < t; ++k)
                {
                    j = index[k];
                    if (R[j] < 0)
                        goto augment;
                }
            }
            int q = index[s++], i = R[q];
            for (int k = t; k < m; ++k)
            {
                j = index[k];
                T h = getc(i, j) - getc(i, q) + w;
                if (h < dist[j])
                {
                    dist[j] = h, prev[j] = i;
                    if (h == w)
                    {
                        if (R[j] < 0)
                            goto augment;
                        index[k] = index[t], index[t++] = j;
                    }
                }
            }
        }
    augment:
        for (int k = 0; k < l; ++k)
            v[index[k]] += dist[index[k]] - w;
        int i;
        do
        {
            i = R[j] = prev[j];
            swap(j, L[i]);
        } while (i != f);
    }
    T ret = 0;
    for (int i = 0; i < n; ++i)
        ret += c[i][L[i]];
    return {ret, L};
}

int64_t cost[maxf][maxf]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    int n, m, k; 
    cin >> m >> n >> k; 
    for(int i = 0, u, v, w; i < k; i++) { 
        cin >> u >> v >> w; 
        --u, --v; 
        cost[u][v] = -w;
    }
    n = max(m, n); 
    auto [ret, idx] = Hungarian<int64_t>(n, n, cost); 
    cout << -ret << '\n'; 
    int match = 0; 
    for(int i = 0; i < idx.size(); i++) { 
        match += (cost[i][idx[i]] != 0); 
    }
    cout << match << '\n'; 
    for(int i = 0; i < idx.size(); i++) { 
        if(cost[i][idx[i]]) cout << i + 1 << " " << idx[i] + 1 << '\n'; 
    }
    return 0;
}