/**
 * @file PuzzlePieces.cc
 * @author Minh Quan Le
 * @brief Problem D
 * @version 0.1
 * @date 2024-10-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "bits/stdc++.h"

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 
const int maxf = 302; 

int64_t dp[2][maxf][maxf << 1][2], dyn[2][maxf][maxf << 1][2]; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, L;
  cin >> N >> L;
  // 0 for none, 1 for in, 2 for out
  vector<tuple<int, int, int>> piece, nonHead;
  for (int i = 0, len; i < N; i++) {
    string uIn, vIn;
    cin >> len >> uIn >> vIn;
    int u = uIn == "none" ? 0 : (uIn == "in" ? 1 : 2); 
    int v = vIn == "none" ? 0 : (vIn == "in" ? 1 : 2); 
    if (u == 0 || v == 0) {
      nonHead.push_back({len, u, v});
    } else {
      piece.push_back({u, v, len});
    }
  }
  int64_t ret = 0; 
  int offset = sz(piece) + 1; 
  dyn[0][0][offset][0] = dp[0][0][offset][0] = 1;
  sort(piece.rbegin(), piece.rend()); 
  for(int pos = 0; pos < sz(piece); pos++) { 
    auto [head, tail, pieceLength] = piece[pos];
    for(int i = 0; i < maxf; i++) { 
     for(int j = 0; j < maxf * 2; j++) { 
      for(int k = 0; k < 2; k++) { 
        dyn[(pos + 1) & 1][i][j][k] = dp[(pos + 1) & 1][i][j][k] = 0; 
      }
     }
    }
    for(int len = 0; len <= L; len++) { 
     for(int diff = -pos; diff <= pos; diff++) { 
      for(int containOut = 0; containOut < 2; containOut++) { 
        (dyn[(pos + 1) & 1][len][offset + diff][containOut] += dyn[pos & 1][len][offset + diff][containOut]) %= MOD; 
        (dp[(pos + 1) & 1][len][offset + diff][containOut] += dp[pos & 1][len][offset + diff][containOut]) %= MOD; 
        if(len + pieceLength <= L) { 
          if(head == 2 && tail == 2) {
            (dyn[(pos + 1) & 1][len + pieceLength][offset + diff - 1][true] += dyn[pos & 1][len][offset + diff][containOut]) %= MOD; 
          }
          else if(head == 1 && tail == 1) { 
            (dyn[(pos + 1) & 1][len + pieceLength][offset + diff + 1][containOut] += dyn[pos & 1][len][offset + diff][containOut]) %= MOD; 
          }
          else if (containOut) { 
            (dyn[(pos + 1) & 1][len + pieceLength][offset + diff][containOut] += dyn[pos & 1][len][offset + diff][containOut]) %= MOD; 
          }
          if(head == 2 && tail == 2) {
            (dp[(pos + 1) & 1][len + pieceLength][offset + diff - 1][true] += dp[pos & 1][len][offset + diff][containOut]) %= MOD; 
          }
          else if(head == 1 && tail == 1) { 
            (dp[(pos + 1) & 1][len + pieceLength][offset + diff + 1][containOut] += dp[pos & 1][len][offset + diff][containOut]) %= MOD; 
          }
          else if((head == 2 && tail == 1) || containOut) { 
            (dp[(pos + 1) & 1][len + pieceLength][offset + diff][containOut] += dp[pos & 1][len][offset + diff][containOut]) %= MOD; 
          }
        }
      }
     }
    }
  } 
  for (int i = 0; i < sz(nonHead); i++) {
    auto [pieceLengthA, headA, tailA] = nonHead[i];
    if (headA == 0 && tailA == 1) {
      for (int j = 0; j < sz(nonHead); j++) {
        auto [pieceLengthB, headB, tailB] = nonHead[j];
        if (headB == 1 && tailB == 0 && pieceLengthA + pieceLengthB <= L) {
          (ret += dyn[sz(piece) & 1][L - pieceLengthA - pieceLengthB][offset - 1][1]) %= MOD;
        }
        if(headB == 2 && tailB == 0 && pieceLengthA + pieceLengthB <= L) { 
          (ret += dp[sz(piece) & 1][L - pieceLengthA - pieceLengthB][offset][0] + 
                  dp[sz(piece) & 1][L - pieceLengthA - pieceLengthB][offset][1]) %= MOD; 
        }
      }
    }
  }
  sort(piece.begin(), piece.end()); 
  memset(dp, 0, sizeof(dp)); 
  memset(dyn, 0, sizeof(dyn)); 
  dyn[0][0][offset][0] = dp[0][0][offset][0] = 1; 
  for(int pos = 0; pos < sz(piece); pos++) { 
    auto [head, tail, pieceLength] = piece[pos];
    for(int i = 0; i < maxf; i++) { 
     for(int j = 0; j < maxf * 2; j++) { 
      for(int k = 0; k < 2; k++) { 
        dyn[(pos + 1) & 1][i][j][k] = dp[(pos + 1) & 1][i][j][k] = 0; 
      }
     }
    }
    for(int len = 0; len <= L; len++) { 
     for(int diff = -pos; diff <= pos; diff++) { 
      for(int containIn = 0; containIn < 2; containIn++) { 
        (dyn[(pos + 1) & 1][len][offset + diff][containIn] += dyn[pos & 1][len][offset + diff][containIn]) %= MOD; 
        (dp[(pos + 1) & 1][len][offset + diff][containIn] += dp[pos & 1][len][offset + diff][containIn]) %= MOD; 
        if(len + pieceLength <= L) { 
          if(head == 2 && tail == 2) {
            (dp[(pos + 1) & 1][len + pieceLength][offset + diff - 1][containIn] += dp[pos & 1][len][offset + diff][containIn]) %= MOD; 
          }
          else if(head == 1 && tail == 1) { 
            (dp[(pos + 1) & 1][len + pieceLength][offset + diff + 1][true] += dp[pos & 1][len][offset + diff][containIn]) %= MOD; 
          }
          else if((head == 1 && tail == 2) || containIn) { 
            (dp[(pos + 1) & 1][len + pieceLength][offset + diff][containIn] += dp[pos & 1][len][offset + diff][containIn]) %= MOD; 
          }
          if(head == 2 && tail == 2) {
            (dyn[(pos + 1) & 1][len + pieceLength][offset + diff - 1][containIn] += dyn[pos & 1][len][offset + diff][containIn]) %= MOD; 
          }
          else if(head == 1 && tail == 1) { 
            (dyn[(pos + 1) & 1][len + pieceLength][offset + diff + 1][true]      += dyn[pos & 1][len][offset + diff][containIn]) %= MOD; 
          }
          else if(containIn) { 
            (dyn[(pos + 1) & 1][len + pieceLength][offset + diff][containIn]     += dyn[pos & 1][len][offset + diff][containIn]) %= MOD; 
          }
        }
      }
     }
    }
  }
  for (int i = 0; i < sz(nonHead); i++) {
    auto [pieceLengthA, headA, tailA] = nonHead[i];
    if (headA == 0 && tailA == 2) {
      for (int j = 0; j < sz(nonHead); j++) {
        auto [pieceLengthB, headB, tailB] = nonHead[j];
        if( headB == 1  && tailB == 0 && pieceLengthA + pieceLengthB <= L) { 
          (ret += dp[sz(piece) & 1][L - pieceLengthA - pieceLengthB][offset][0] + 
                  dp[sz(piece) & 1][L - pieceLengthA - pieceLengthB][offset][1]) %= MOD; 
        }
        if (headB == 2 && tailB == 0 && pieceLengthA + pieceLengthB <= L) {
          (ret += dyn[sz(piece) & 1][L - pieceLengthA - pieceLengthB][offset + 1][1]) %= MOD;
        }
      }
    }
    if(headA == 0 && tailA == 0 && pieceLengthA == L) { 
      ret++; 
    }
  }
  ret %= MOD; 
  cout << ret << '\n';
  return 0;
}

/**
 * (out, out) = (out, in) (out, out) 
 * (out, out) = (out, out) (in, in) (out, out) (in, in) (out, out) // This mainly lies on the fact that the difference of (in, in) has to be 1. 
 * (out, out) = (out, in) (out, in), (out, in) (out, out) (in, out)....(in, out)...(in, out) (in, in)
 * (in, in) = (in, out) (in, out) (in, out)... (in, in) ... (out, in) (out, in) (out, in)... 
 * (in, in) = (in, in) (out, out)
 */