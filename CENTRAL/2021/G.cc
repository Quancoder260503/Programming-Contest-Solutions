#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    string S; 
    int Q; 
    while(cin >> S >> Q)
    {
        int N = S.length(); 
        vector<int>sweep(N + 1, 0); 
        for(int i = 0; i < Q; i++)
        {
            int k, u, v;
            cin >> k >> u >> v; 
            --u, --v;
            sweep[u] += k; 
            sweep[v + 1] -= k; 
        }
        string ret; 
        for(int i = 0; i < N; i++)
        {
            ret += (char)((S[i] - 'A' + sweep[i]) % 26 + 'A');  
            sweep[i + 1] += sweep[i]; 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}
