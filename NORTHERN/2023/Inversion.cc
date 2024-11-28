#include "bits/stdc++.h"
using namespace std;
const int MAX = 202;
const int M = 200; 
const int64_t INF = 1e18; 
int64_t dyn[MAX][MAX * MAX]; 
void pre_calc(int N = M, int K = M * M) 
{ 
    dyn[0][0] = 1;
    for (int i = 1; i <= N; i++)
    {
        int inv = i * (i - 1) / 2;
        dyn[i][0] = dyn[i][inv] = 1;
        for (int j = 1; j <= inv / 2; j++)
        {
            dyn[i][j] = dyn[i - 1][j] + dyn[i][j - 1];
            if (j >= i) dyn[i][j] = dyn[i][j] - dyn[i - 1][j - i];
            if(dyn[i][j] >= INF) dyn[i][j] = INF; 
        }
        for (int j = inv / 2 + 1; j < inv; j++)
        {
            dyn[i][j] = dyn[i][inv - j];
        }
    }
}
int main(void)
{
    int64_t N, M, K;
    pre_calc(); 
    while(cin >> N >> M >> K)
    {
        vector<int>digit(N); 
        iota(digit.begin(), digit.end(), 1);
        if(dyn[N][M] < K)
        {
            puts("-1"); 
            continue; 
        }
        vector<int>ret; 
        for(int i = 0; i < N; i++)
        {
            int64_t ctr = 0; 
            for(int j = 0; j < (int) digit.size(); j++) 
            {
                if(dyn[N - i - 1][M - j] + ctr >= K)
                {
                    ret.push_back(digit[j]); 
                    digit.erase(digit.begin() + j); 
                    K = K - ctr; 
                    M = M - j; 
                    break; 
                } 
                ctr += dyn[N - i - 1][M - j]; 
            }
        }
        for(auto it : ret) cout << it << " "; 
        cout << '\n';
    }
    return 0;
}