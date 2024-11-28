#include "bits/stdc++.h"
using namespace std;
const int MAX = 750; 
const int INF = 1e9; 
const int dx[4] = {0, 0, -1, 1}; 
const int dy[4] = {-1, 1, 0, 0}; 
int g[MAX][MAX]; 
int dyn[MAX][MAX];
int N, G, T;  
int doit(int sx, int sy, int w)
{
    deque<pair<int, int>>q; 
    q.push_back({sx, sy}); 
    dyn[sx][sy] = (w > g[sx][sy]);
    while(q.size())
    {
        auto [u, v] = q.front(); 
        q.pop_front(); 
        for(int i = 0; i < 4; i++) 
        {
            int su = u + dx[i]; 
            int sv = v + dy[i]; 
            if(0 <= su && su < N && 0 <= sv && sv < N && dyn[su][sv] == -1)
            {
                if(g[su][sv] >= w)
                {
                    dyn[su][sv] = dyn[u][v]; 
                    q.push_front({su, sv}); 
                }
                else 
                {
                    dyn[su][sv] = dyn[u][v] + 1; 
                    q.push_back({su, sv}); 
                }
            }
        }
    }
    return dyn[N - 1][N - 1]; 
}
int chk(int W)
{
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
    {
        dyn[i][j] = -1;
    }
    return (doit(0, 0, W) == 0); 
}
int main(void)
{
    while(cin >> T)
    {
        if(T == 1)
        {
            cin >> N >> G;
            for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
            {
                dyn[i][j] = -1; 
                cin >> g[i][j];
            }
            cout << doit(0, 0, G) << '\n'; 
        }
        else 
        {
            cin >> N; 
            for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
            {
                cin >> g[i][j]; 
            }
            int L = 1;
            int R = 1e4; 
            while(L < R)
            {
                int mid = (L + R + 1) / 2; 
                if(chk(mid))
                {
                    L  = mid; 
                }
                else 
                {
                    R = mid - 1; 
                }
            }
            cout << L << '\n'; 
        }
    }
    return 0; 
}