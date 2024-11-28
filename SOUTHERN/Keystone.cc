#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N;
    while (cin >> N)
    {
        vector<int>H(N);
        for(int i = 0; i < N; i++) cin >> H[i]; 
        vector<int>L(N), R(N); 
        for(int i = 0; i < N; i++)      L[i] = min(H[i], (i          ? L[i - 1] : 0) + 1); 
        for(int i = N - 1; i >= 0; i--) R[i] = min(H[i], (i < N - 1  ? R[i + 1] : 0) + 1);
        int ret = 0; 
        for(int i = 0; i < N; i++) ret = max(ret, min(L[i], R[i])); 
        cout << ret << '\n';  
    }
    return 0;
}