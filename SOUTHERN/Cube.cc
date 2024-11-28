#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, K;
    while (cin >> N >> K)
    {
        vector<tuple<int,int,int>>Xs, Ys, Zs; 
        for(int i = 0; i < K; i++)
        {
            int x, y, z; 
            cin >> x >> y >> z; 
            if(x == 0) Xs.push_back({x, y, z});
            else if(y == 0) Ys.push_back({x, y, z});
            else if(z == 0) Zs.push_back({x, y, z}); 
        }
        map<int, int>ctrx, ctry, ctrz; 
        map<pair<int, int>, int>ctrxy; 
        int64_t ret = 0; 
        for(auto [x, y, z] : Xs)
        {
            ret += N; 
            ctrz[z]++;
            ctry[y]++; 
        }
        for(auto [x, y, z] : Ys)
        {
            ret += (N - ctrz[z]); 
            ctrx[x]++; 
            for(auto [x2, y2, z2] : Xs) 
            {
                if(z == z2) ctrxy[{x, y2}]++; 
            }
        }
        for(auto [x, y, z] : Zs)
        {
            ret += (N - ctrx[x] - ctry[y] + ctrxy[{x, y}]); 
        }
        cout << ret << '\n'; 
    }
    return 0;
}