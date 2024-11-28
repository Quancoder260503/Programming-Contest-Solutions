#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T, N;
    cin >> T;
    while(T--)
    {
        cin >> N;
        vector<int>a(N); 
        for(int i = 0; i < N; i++) cin >> a[i]; 
        sort(a.begin(), a.end());
        if(a.size() == 1)
        {
            cout << (a[0] == 1 ? "RR" : "Hieu") << '\n'; 
        }
        else 
        {
            int ret = (a[a.size() - 1] - a[a.size() - 2] == 1) &&  (a[a.size() - 1] % 2 == N % 2);
            cout << (ret ? "RR" : "Hieu") << '\n';  
        }
    }
    return 0; 
}