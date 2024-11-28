#include "bits/stdc++.h"
using namespace std;
struct fenwick
{
    int N;
    vector<int64_t> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    int64_t sum(int i)
    {
        int64_t c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T, N, M;
    cin >> T;
    while (T--)
    {
        cin >> N >> M;
        vector<int> a(N), b(M);
        for (int i = 0; i < N; i++)
            cin >> a[i];
        for (int i = 0; i < M; i++)
            cin >> b[i];
        sort(b.begin(), b.end());
        vector<int> p(M);
        function<void(int, int, int, int)> doit;
        doit = [&](int la, int ra, int lb, int rb) -> void
        {
            if (lb > rb)
                return;
            int mid = (lb + rb) / 2;
            int64_t invL = 0;
            int64_t invR = 0;
            for (int i = la; i < ra; i++) invL += (a[i] > b[mid]);
            pair<int64_t, int> opt = {invL + invR, ra};
            for (int i = ra - 1; i >= la; i--)
            {
                invL = invL - (a[i] > b[mid]);
                invR = invR + (a[i] < b[mid]);
                opt = min(opt, {invL + invR, i});
            }
            p[mid] = opt.second;
            doit(la, opt.second, lb, mid - 1);
            doit(opt.second, ra, mid + 1, rb);
        };
        doit(0, N, 0, M - 1);
        vector<int> ret;
        int ptr = 0;
        for (int i = 0; i < M; i++)
        {
            while (ptr < p[i])
            {
                ret.push_back(a[ptr++]);
            }
            ret.push_back(b[i]);
        }
        while(ptr < N) ret.push_back(a[ptr++]); 
        vector<int> rx;
        for (auto it : ret) rx.push_back(it);
        sort(rx.begin(), rx.end());
        rx.erase(unique(rx.begin(), rx.end()), rx.end());
        int64_t res = 0;
        fenwick fenw;
        fenw.init(rx.size() + 2);
        for (int i = ret.size() - 1; i >= 0; i--)
        {
            int pos = lower_bound(rx.begin(), rx.end(), ret[i]) - rx.begin();
            res += fenw.sum(pos);
            fenw.upd(pos + 1, 1);
        }
        cout << res << '\n';
    }
    return 0;
}