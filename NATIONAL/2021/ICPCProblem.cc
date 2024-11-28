#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

const int maxf = 52;
const int maxb = 16;

int64_t dyn[maxf][maxb][maxb][maxb][maxb][maxb];
vector<string>cc = {"dp", "graph", "mathgeo", "ds", "adhoc"}; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N;
  cin >> N;
  vector<int>a(N + 1); 
  string s; 
  for (int i = 1, x; i <= N; i++) {
    cin >> x;
    for (int j = 0, pos; j < x; j++) {
      cin >> s;
      for(pos = 0; pos < sz(cc); pos++) if(s == cc[pos]) { 
        break; 
      }
      a[i] |= (1 << pos); 
    }
  }
  vector<pair<int, int>>Query(5); 
  int opt = 0;
  for(int i = 0; i < 5; i++) { 
    cin >> Query[i].first >> Query[i].second; 
    opt = max(opt, Query[i].first); 
  }
  dyn[0][0][0][0][0][0] = 1;
  for (int i = 1; i <= N; i++) {
    for (int dp_prob = 0; dp_prob < maxb; dp_prob++) {
      for (int graph_prob = 0; graph_prob < maxb; graph_prob++) {
        for (int geo_prob = 0; geo_prob < maxb; geo_prob++) {
          for (int ds_prob = 0; ds_prob < maxb; ds_prob++) {
            for (int adhoc_prob = 0; adhoc_prob < maxb; adhoc_prob++) {
              dyn[i][dp_prob][graph_prob][geo_prob][ds_prob][adhoc_prob] += 
              dyn[i - 1][dp_prob][graph_prob][geo_prob][ds_prob][adhoc_prob]; 
              int pre_dp_prob    = dp_prob    - ((a[i] & (1 << 0)) > 0); 
              int pre_graph_prob = graph_prob - ((a[i] & (1 << 1)) > 0); 
              int pre_geo_prob   = geo_prob   - ((a[i] & (1 << 2)) > 0); 
              int pre_ds_prob    = ds_prob    - ((a[i] & (1 << 3)) > 0);
              int pre_adhoc_prob = adhoc_prob - ((a[i] & (1 << 4)) > 0); 
              if(pre_dp_prob >= 0 && pre_graph_prob >= 0 && pre_geo_prob >= 0 && pre_ds_prob >= 0 && pre_adhoc_prob >= 0) { 
                dyn[i][dp_prob][graph_prob][geo_prob][ds_prob][adhoc_prob] += 
                dyn[i - 1][pre_dp_prob][pre_graph_prob][pre_geo_prob][pre_ds_prob][pre_adhoc_prob]; 
              }
            }
          }
        }
      }
    }
  }
  int64_t ret = 0; 
  for (int dp_prob = Query[0].first; dp_prob <= Query[0].second; dp_prob++) {
    for (int graph_prob = Query[1].first; graph_prob <= Query[1].second; graph_prob++) {
      for (int geo_prob = Query[2].first; geo_prob <= Query[2].second; geo_prob++) {
        for (int ds_prob = Query[3].first; ds_prob <= Query[3].second; ds_prob++) {
          for (int adhoc_prob = Query[4].first; adhoc_prob <= Query[4].second; adhoc_prob++) {
            ret += dyn[N][dp_prob][graph_prob][geo_prob][ds_prob][adhoc_prob]; 
          }
        }
      }
    }
  }
  cout << ret - (opt == 0) << '\n'; 
  return 0;
}
