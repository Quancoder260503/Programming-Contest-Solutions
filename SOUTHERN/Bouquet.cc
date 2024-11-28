#include "bits/stdc++.h"
using namespace std;
int main(void)
{ 
    int N, K; 
    while(cin >> N >> K)
    {
        vector<int>ret;  
        for(int digit = 9; digit > 1; digit--)
        {
            while(N % digit == 0) 
            {
                ret.push_back(digit); 
                N = N / digit; 
            }
        }
        if(ret.size() > K  || N > 1) 
        {
            cout << "-1" << '\n'; 
            continue; 
        }
        while(ret.size() < K) ret.push_back(1); 
        reverse(ret.begin(), ret.end()); 
        for(auto it : ret) cout << it; 
        cout << '\n'; 
    }
    return 0; 
}