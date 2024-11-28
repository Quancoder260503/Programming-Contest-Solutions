#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N; 
  cin >> N; 
  vector<int>a(N); 
  int64_t sum = 0; 
  map<int, int>even, odd; 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
    (a[i] % 2 == 0 ? even : odd)[a[i]]++; 
    sum += a[i]; 
  } 
  string s; 
  cin >> s; 
  for(int i = 0; i < sz(s); i++) { 
    if(s[i] == '0' && sz(even) == 0) { 
      cout << sum << '\n'; 
      continue; 
    } 
    if(s[i] == '1' && sz(odd)  == 0) { 
      cout << sum << '\n'; 
      continue; 
    } 
    map<int, int>nMap; 
    if(s[i] == '0') { 
      for(auto [u, v] : even) { 
        ((u / 2) % 2 == 0 ? nMap : odd)[u / 2] += v; 
        sum = sum - 1LL * v * u;
        sum = sum + 1LL * v * u / 2; 
      } 
      even = nMap; 
    }
    else {
      for(auto [u, v] : odd) { 
        if(u == 1) { 
          sum -= v; 
          continue;
        }
        even[u - 1] += v; 
        sum = sum - 1LL * v * u; 
        sum = sum + 1LL * v * (u - 1); 
      } 
      odd.clear(); 
    }
    cout << sum << '\n'; 
  } 
  return 0; 
}
