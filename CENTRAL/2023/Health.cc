#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N, K; 
    cin >> N >> K; 
    vector<int>a(N); 
    for(int i = 0; i < N; i++) cin >> a[i];
    sort(a.begin(), a.end()); 
    int ret = -1; 
    for(int _ = 0; _ < K; _++)
    {
        int idx = -1, idy = 0; 
        int x, y, z;
        cin >> x >> y >> z;
        int curr = 0, res = N; 
        for(int i = 0; i < N; i++)
        {
            while(idx + 1 < N && a[i] - a[idx + 1] >= x) idx++; 
            while(a[i] - a[idy] > y) idy++;
            if(idx >= idy) curr += idx - idy + 1; 
            if(curr >= z)
            {
                res = i; 
                break; 
            }
        }
        ret = max(ret, res); 
    }
    if(ret == N) cout << -1 << '\n'; 
    else if(ret == -1) cout << 0 << '\n'; 
    else cout << a[ret] << '\n'; 
    return 0; 
}