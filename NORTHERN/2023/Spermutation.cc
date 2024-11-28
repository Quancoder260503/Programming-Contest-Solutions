#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7; 
const int maxf = 500; 

map<vector<int>, int64_t>dyn[maxf]; 
int N, M; 

int64_t doit(int at, vector<int>dist, vector<int>vis)
{
    if(at == N) return 1; 
    if(dyn[at].count(dist)) return dyn[at][dist]; 
    int ret = 0;  
    for(int x = 0; x < 8; x++) 
    {
        if(vis[x] && x == dist[x])
        {
            vector<int>ndist(8); 
            for(int y = 0; y < 8; y++) ndist[y] = min(dist[y] + 1, y); 
            ndist[x] = 0; 
            ret += doit(at + 1, ndist, vis); 
            ret %= mod; 
        }
    }
    return dyn[at][dist] = ret; 
}

int main(void)
{
    cin >> N >> M; 
    vector<int>vis(8), dist(8);
    iota(dist.begin(), dist.end(), 0); 
    for(int i = 0; i < M; i++)
    {
        int x;
        cin >> x;
        vis[x - 1] = 1; 
    }
    cout << doit(0, dist, vis) << '\n'; 
    return 0; 
}