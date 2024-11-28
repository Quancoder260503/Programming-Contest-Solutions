#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<double>A(N);
        vector<double>prefix(N); 
        for(int i = 0; i < N; i++)
        {
            cin >> A[i]; 
            prefix[i] = (i ? prefix[i - 1] : 0) + A[i]; 
        }
        vector<pair<double, pair<int, int>>>stk;
        for(int i = 0; i < N; i++)
        {
            pair<double, pair<int, int>> at = {A[i], {i, i}}; 
            while(stk.size() && stk.back().first > at.first)
            {
                at.second.first = stk.back().second.first;
                at.first = (prefix[i] - (at.second.first ? prefix[at.second.first - 1] : 0)) / (double)(i - at.second.first + 1);
                stk.pop_back();
            }
            stk.push_back(at);
        }
        double ret = 0; 
        for(int i = 0; i < stk.size(); i++)
        {
            auto [from, to] = stk[i].second; 
            for(int j = from; j <= to; j++)
            {
                ret += (A[j] - stk[i].first) * (A[j] - stk[i].first); 
            }
        }
        ret = sqrt(ret); 
        cout << fixed << setprecision(10) << ret << '\n'; 
    }
    return 0;
}