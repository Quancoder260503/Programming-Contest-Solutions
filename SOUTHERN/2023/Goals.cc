#include "bits/stdc++.h"
using namespace std; 
#define double long double
const int MAXN = 200; 
double dyn[MAXN][MAXN][MAXN]; 
double memo(int n, int m, int k)
{
    if(n <= 0 || m <= 0) return 0; 
    if(dyn[n][m][k] != -1) return dyn[n][m][k]; 
    double p = n / (1.0 * (m + n)); 
    dyn[n][m][k] = p * memo(n - 1, m, max(0, k - 1)) + (1 - p) * memo(n, m - 1, k + 1); 
    if(!k) dyn[n][m][k] += p * n; 
    return dyn[n][m][k]; 
}
int main(void)
{
    int N; 
    while(cin >> N)
    {
        for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) for (int k = 0; k < MAXN; k++)
        {
           dyn[i][j][k] = -1.0;
        }
        cout << fixed << setprecision(6) << memo(N, N, 0) <<'\n'; 
    }
    return 0; 
}