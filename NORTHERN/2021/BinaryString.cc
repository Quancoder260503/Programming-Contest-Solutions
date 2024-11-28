#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e7; 

void solve() { 
 string S; 
 cin >> S; 
 int N = sz(S); 
 vector<int>dp(N + 1, oo); 
 dp[0] = 0; 
 for(int i = 1; i <= N; i++) { 
  if(S[i - 1] == '0') { 
    dp[i] = dp[i - 1]; 
    if(i >= 2 && S[i - 2] == '1') dp[i] = min(dp[i], dp[i - 2]); 
  } 
  else { 
    dp[i] = dp[i - 1] + 1; 
    if(i >= 2 && S[i - 2] == '0') dp[i] = min(dp[i], dp[i - 2]); 
  } 
 }
 cout << dp[N] << '\n'; 
 return; 
} 

int main() {
 int T; 
 for(cin >> T; T--; ) {
  solve(); 
 } 
 return 0; 
}