#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int A, B, C, D; 
    while(cin >> A >> B >> C >> D)
    {
        vector<int>div; 
        for(int i = 2; i * i <= C; i++) if(C % i == 0)
        {
            div.push_back(i); 
            if(i * i != C) div.push_back(C / i); 
        }
        sort(div.begin(), div.end()); 
        for(auto d : div)
        {
            if(d % A == 0 && d % B && D % d)
            {
                cout << d << '\n';
                goto done; 
            }
        }
        cout << -1 << '\n'; 
    done: 
        continue;
    }
    return 0; 
}