#include <bits/stdc++.h> 

using namespace std; 

int main(void) { 
  string s; 
  int k;
  cin >> s >> k; 
  pair<char, char> opt = {'z' + 1, 'z' + 1}; 
  for(int i = 0; i < s.size(); i++) { 
    if(i > 0) opt = min(opt, {s[i], s[i - 1]}); 
    if(i + 1 < s.size()) opt = min(opt, {s[i], s[i + 1]}); 
  } 
  for(int i = 0; i < k; i++) { 
    cout << (i % 2 == 0 ? opt.first : opt.second); 
  } 
  cout << '\n'; 
} 