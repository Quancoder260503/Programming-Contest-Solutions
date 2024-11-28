#include "bits/stdc++.h"
using namespace std;
const int M = 1002;
const int Limit = 500; 
signed main(void)
{
    int N;
    while (cin >> N)
    {
        vector<int> arr(N);
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }
        vector<int> L(N), R(N);
        stack<int> stk;
        for (int i = 0; i < N; i++)
        {
            while (stk.size() && arr[stk.top()] <= arr[i])
            {
                stk.pop();
            }
            L[i] = (stk.size() ? stk.top() + 1 : 0);
            stk.push(i);
        }
        while (stk.size()) stk.pop();
        for (int i = N - 1; i >= 0; i--)
        {
            while (stk.size() && arr[stk.top()] <= arr[i])
            {
                stk.pop();
            }
            R[i] = (stk.size() ? stk.top() - 1 : N - 1);
            stk.push(i);
        }
        vector<vector<pair<int, int>>> pivot(M);
        for (int i = 0; i < N; i++)
        { 
            pivot[arr[i] + Limit].push_back({L[i], R[i]}); 
        }
        auto max_sub_array = [&](int L, int R)
        {
            int prefix_sum = 0; 
            int max_so_far = 0; 
            int ret = -1e9; 
            for(int i = L; i < R; i++)
            {
                prefix_sum += arr[i]; 
                ret = max(ret, prefix_sum + max_so_far); 
                max_so_far = max(max_so_far, -prefix_sum); 
            }
            return ret;
        };
        int ret = 0;
        for(int i = 0; i < M; i++)
        {
            for(auto [L, R] : pivot[i])
            {
                ret = max(ret, max_sub_array(L, R) - i + Limit); 
            }
        }
        cout << ret << '\n'; 
    }
    return 0;
}