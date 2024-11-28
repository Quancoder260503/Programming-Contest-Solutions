#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define double long double
const int M = 100;
const lint INF = 1e18;
signed main(void)
{
    int T;
    vector<lint>fib(M);
    cin >> T;
    fib[0] = fib[1] = 1; 
    int N = 0;
    for(N = 2; N < M; N++)
    {
        fib[N] = fib[N - 1] + fib[N - 2];
        if(fib[N] > INF) break;
    }
    for(int _ = 0; _ < T; _++)
    {
        map<lint, lint>dyn[N]; 
        function<lint(lint, int)>doit; 
        doit = [&](lint num, int at) -> lint
        {
            if(num == 1 && at == 1) return 1;
            if(num >  1 && at == 1) return 0; 
            if(dyn[at].count(num)) return dyn[at][num]; 
            lint curr = 1; 
            while(curr <= num)
            {
                if(num % curr == 0) dyn[at][num] += doit(num / curr, at - 1);
                else break;
                if (log10(curr) + log10(fib[at]) > 18) break;
                curr = 1LL * curr * fib[at];
            }
            return dyn[at][num]; 
        }; 
        lint num; 
        cin >> num; 
        cout << doit(num, N - 1) << '\n'; 
    }
    return 0; 
}