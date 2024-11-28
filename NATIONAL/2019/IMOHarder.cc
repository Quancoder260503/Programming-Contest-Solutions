#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define double long double 

double Comb(int N, int K) { 
  if(N < K || K < 0) return 0; 
  double ret = 1; 
  for(int i = 0; i < K; i++) { 
    ret = ret * (N - i) / (i + 1); 
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S; 
  cin >> S;  
  int N = sz(S); 
  int unfilled = 0, head = 0;
  double sum_unfilled = 0, sum_head = 0, ret = 0; 
  for(int i = 0; i < N; i++) { 
    unfilled += (S[i] == '?');
    head     += (S[i] == 'H'); 
    sum_unfilled += (S[i] == '?') * (i + 1);  
    sum_head     += (S[i] == 'H') * (i + 1); 
  }
  /* 
  for(int fill_head = 0; fill_head <= unfilled; fill_head++) { 
    ret += (2 * sum_head * Comb(unfilled, fill_head) + Comb(unfilled - 1, fill_head - 1) * 2 * sum_unfilled - 
                           Comb(unfilled, fill_head) * (head + fill_head) * (head + fill_head)) / den;  
  }
  */ 
  ret += 2 * sum_head + sum_unfilled - 1.0 * head * head - 1.0 * head * unfilled - 
         1.0 * unfilled * unfilled / 2 + 1.0 * unfilled * (unfilled - 1) / 4; 
  cout << fixed << setprecision(10) << ret << '\n';
  return 0; 
}

/*
  This is just a naive program to check if the maths part is done correctly, 
  Other improvements may come later. 
*/
