#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int mod = 1e9 + 7;
const int base1 = 31;
const int base2 = 37;
template <typename Container>
std::vector<int> prefix_function(const Container &s)
{
    int n = s.size();
    std::vector<int> pi(n);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}
std::vector<int> kmp(const std::string &pat, const std::string &text)
{
    auto pi = prefix_function(pat + '\0' + text);
    std::vector<int> res;
    for (size_t i = pi.size() - text.size(); i < pi.size(); ++i)
    {
        if (pi[i] == (int)pat.size())
        {
            res.push_back(i - 2 * pat.size());
        }
    }
    return res;
}
std::vector<int> prefix_occurrences(const string &s)
{
    int n = s.size();
    auto pi = prefix_function(s);
    std::vector<int> res(n + 1);
    for (int i = 0; i < n; ++i)
        res[pi[i]]++;
    for (int i = n - 1; i > 0; --i)
        res[pi[i - 1]] += res[i];
    for (int i = 0; i <= n; ++i)
        res[i]++;
    return res;
}
// }}}
signed main(void)
{
    string S;
    int Q;  
    while(cin >> S >> Q)
    {
        int N = S.length();
        vector<int>ret = prefix_occurrences(S);
        vector<Lint>p1(N + 1, 0); 
        vector<Lint>p2(N + 1, 0);
        p1[0] = p2[0] = 1; 
        for (int i = 1; i <= N; i++)
        {
            p1[i] = p1[i - 1] % mod * base1 % mod;
            p2[i] = p2[i - 1] % mod * base2 % mod;
        }
        Lint ph1, ph2, sh1, sh2; 
        ph1 = ph2 = sh1 = sh2 = 0;
        vector<Lint>vis(N); 
        for (int i = 0; i < N; i++)
        {
            int l = S[i] - 'a' + 1;
            int r = S[N - 1 - i] - 'a' + 1;
            ph1 = (ph1 + p1[i] % mod * l % mod + mod) % mod;
            ph2 = (ph2 + p2[i] % mod * l % mod + mod) % mod;
            sh1 = (sh1 % mod * base1 % mod + r + mod) % mod;
            sh2 = (sh2 % mod * base2 % mod + r + mod) % mod;
            if (sh1 == ph1 && sh2 == ph2)
            {
                vis[i] = 1; 
            }
        }
        for(int i = 0; i < Q; i++)
        {
            int at; 
            cin >> at; 
            if(vis[at - 1] && ret[at] > 2)
            {
               cout << "YES" << " " << ret[at] << '\n'; 
            }
            else 
            {
               cout << "NO" << '\n'; 
            }
        } 
    }
    return 0; 
}