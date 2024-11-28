#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N;
    while(cin >> N)
    {
        int ret = 0;  
        for(int i = 0; i < N; i++)
        {
            int x; 
            cin >> x; 
            int num = (x % 4 == 0 ? x - 1 : (x % 4 == 3 ? x + 1 : x));
            ret = ret xor num;   
        }
        cout << (ret ? "Alice" : "Bob") << '\n'; 
    }
    return 0; 
}