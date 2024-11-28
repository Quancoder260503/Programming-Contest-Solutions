#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);  
  string s;
  while(cin >> s) { 
    if(s == "$") break; 
    int N = sz(s); 
    vector<vector<int64_t>>dp(N, vector<int64_t>(4)); 
    for(int i = 0; i < N; i++) { 
      dp[i][0] = (i ? dp[i - 1][0] : 0) + (s[i] == 'I'); 
    }
    for(int i = 2; i < N; i++) { 
      dp[i][1] = dp[i - 1][1] + (s[i] == 'C') * dp[i - 2][0]; 
    }
    for(int i = 2; i < N; i++) { 
      dp[i][2] = dp[i - 1][2] + (s[i] == 'P') * dp[i - 2][1]; 
    }
    for(int i = 2; i < N; i++) { 
      dp[i][3] = dp[i - 1][3] + (s[i] == 'C') * dp[i - 2][2]; 
    }
    cout << dp[N - 1][3] << '\n'; 
  }  
  return 0; 
}