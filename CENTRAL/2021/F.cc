#include "bits/stdc++.h"
using namespace std;
#define Lint long long
signed main(void)
{
    int T;
    cin >> T;
    while (T--)
    {
        string S;
        cin >> S;
        int N = S.length();
        vector<vector<int>> pos(26);
        for (int i = 0; i < N; i++)
        {
            pos[S[i] - 'a'].push_back(i);
        }
        Lint ret = 0;
        for (int ch = 0; ch < 26; ch++)
        {
            for (int i = 0; i < pos[ch].size(); i++)
            {
                int totL = pos[ch][i] - (i ? pos[ch][i - 1] : -1);
                int totR = (i + 1 < (int)pos[ch].size() ? pos[ch][i + 1] : N) - pos[ch][i];
                ret += totL * totR ; 
            }
        }
        cout << ret << '\n';
    }
    return 0;
}