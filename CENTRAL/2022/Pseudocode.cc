#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N, T;
    cin >> T; 
    while(T--)
    {
        cin >> N; 
        double ret = 1.0 / (N + 1) * 1e9; 
        cout << fixed << setprecision(12) << ret << '\n'; 
    }
    return 0;
}