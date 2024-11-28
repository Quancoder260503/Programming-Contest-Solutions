#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, K; 
    string S;
    while(cin >> N >> K >> S)
    {
        vector<vector<vector<int>>>dyn(N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1, -1)));
        function<int(int, int, int)>doit; 
        vector<int>prefix(N); 
        for(int i = 0; i < N; i++)
        {
            prefix[i] = (i ? prefix[i - 1] : 0) + (S[i] == 'B');
        }
        doit = [&](int L, int R, int A_black)
        {
            if(L > R) return 1; 
            if(A_black >= K) return 0;
            if(dyn[L][R][A_black] >= 0) return dyn[L][R][A_black]; 
            int B_black = prefix[N - 1] - (prefix[R] - (L ? prefix[L - 1] : 0)) - A_black; 
            int &ret = dyn[L][R][A_black]; 
            if(S[L] == 'W' || S[L] == 'B' && A_black < K)
            {
                if(doit(L + 1, R, B_black) == 0)
                {
                    return ret = 1; 
                }
            } 
            if(S[R] == 'W' || S[R] == 'B' && A_black < K)
            {
                if(doit(L, R - 1, B_black) == 0)
                {
                    return ret = 1;
                }
            }
            return ret = 0;
        };
        cout << (doit(0, N - 1, 0) ? "YES" : "NO") << '\n'; 
    }
    return 0; 
}