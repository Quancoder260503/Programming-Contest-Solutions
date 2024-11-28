#include "bits/stdc++.h"
using namespace std;
template <const int64_t mod, const int64_t maxf>
struct NTT
{
    NTT()
    {
        int64_t k = 0;
        while ((1 << k) < maxf)
            k++;
        bitrev[0] = 0;
        for (int64_t i = 1; i < maxf; i++)
        {
            bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (k - 1));
        }
        int64_t pw = fpow(prt(), (mod - 1) / maxf);
        rts[0] = 1;
        for (int64_t i = 1; i <= maxf; i++)
        {
            rts[i] = (long long)rts[i - 1] * pw % mod;
        }
        for (int64_t i = 1; i <= maxf; i <<= 1)
        {
            iv[i] = fpow(i, mod - 2);
        }
    }
    vector<int64_t> multiply(vector<int64_t> a, vector<int64_t> b)
    {
        static int64_t fa[maxf], fb[maxf], fc[maxf];
        int64_t na = a.size(), nb = b.size();
        for (int64_t i = 0; i < na; i++)
            fa[i] = a[i];
        for (int64_t i = 0; i < nb; i++)
            fb[i] = b[i];
        multiply(fa, fb, na, nb, fc);
        int64_t k = na + nb - 1;
        vector<int64_t> res(k);
        for (int64_t i = 0; i < k; i++)
            res[i] = fc[i];
        return res;
    }

private:
    int64_t rts[maxf + 1];
    int64_t bitrev[maxf];
    int64_t iv[maxf + 1];

    int64_t fpow(int64_t a, int64_t k)
    {
        if (!k)
            return 1;
        int64_t res = a, tmp = a;
        k--;
        while (k)
        {
            if (k & 1)
            {
                res = (long long)res * tmp % mod;
            }
            tmp = (long long)tmp * tmp % mod;
            k >>= 1;
        }
        return res;
    }
    int64_t prt()
    {
        vector<int64_t> dvs;
        for (int64_t i = 2; i * i < mod; i++)
        {
            if ((mod - 1) % i)
                continue;
            dvs.push_back(i);
            if (i * i != mod - 1)
                dvs.push_back((mod - 1) / i);
        }
        for (int64_t i = 2; i < mod; i++)
        {
            int64_t flag = 1;
            for (int64_t j = 0; j < (int64_t)dvs.size(); j++)
            {
                if (fpow(i, dvs[j]) == 1)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
                return i;
        }
        assert(0);
        return -1;
    }
    void dft(int64_t a[], int64_t n, int64_t sign)
    {
        int64_t d = 0;
        while ((1 << d) * n != maxf)
            d++;
        for (int64_t i = 0; i < n; i++)
        {
            if (i < (bitrev[i] >> d))
            {
                swap(a[i], a[bitrev[i] >> d]);
            }
        }
        for (int64_t len = 2; len <= n; len <<= 1)
        {
            int64_t delta = maxf / len * sign;
            for (int64_t i = 0; i < n; i += len)
            {
                int64_t *w = sign > 0 ? rts : rts + maxf;
                for (int64_t k = 0; k + k < len; k++)
                {
                    int64_t &a1 = a[i + k + (len >> 1)], &a2 = a[i + k];
                    int64_t t = (long long)*w * a1 % mod;
                    a1 = a2 - t;
                    a2 = a2 + t;
                    a1 += a1 < 0 ? mod : 0;
                    a2 -= a2 >= mod ? mod : 0;
                    w += delta;
                }
            }
        }
        if (sign < 0)
        {
            int64_t in = iv[n];
            for (int64_t i = 0; i < n; i++)
            {
                a[i] = (long long)a[i] * in % mod;
            }
        }
    }
    void multiply(int64_t a[], int64_t b[], int64_t na, int64_t nb, int64_t c[])
    {
        static int64_t fa[maxf], fb[maxf];
        int64_t n = na + nb - 1;
        while (n != (n & -n))
            n += n & -n;
        for (int64_t i = 0; i < n; i++)
            fa[i] = fb[i] = 0;
        for (int64_t i = 0; i < na; i++)
            fa[i] = a[i];
        for (int64_t i = 0; i < nb; i++)
            fb[i] = b[i];
        dft(fa, n, 1), dft(fb, n, 1);
        for (int64_t i = 0; i < n; i++)
            fa[i] = (long long)fa[i] * fb[i] % mod;
        dft(fa, n, -1);
        for (int64_t i = 0; i < n; i++)
            c[i] = fa[i];
    }
};
template <typename T>
struct CRT
{
    T res;

    CRT()
    {
        res = 0, prd = 1;
    }

    // Add condition: res % p == r
    void add(T p, T r)
    {
        res += mul(r - res % p + p, euclid(prd, p).first + p, p) * prd;
        prd *= p;
        if (res >= prd)
            res -= prd;
    }

private:
    T prd;
    T mul(T a, T b, T p)
    {
        a %= p, b %= p;
        T q = (T)((long double)a * b / p);
        T r = a * b - q * p;
        while (r < 0)
            r += p;
        while (r >= p)
            r -= p;
        return r;
    }
    pair<T, T> euclid(T a, T b)
    {
        if (!b)
            return make_pair(1, 0);
        pair<T, T> r = euclid(b, a % b);
        return make_pair(r.second, r.first - a / b * r.second);
    }
};
const int64_t MOD0 = 1004535809; // 2^21 * 479 + 1
const int64_t MOD1 = 1012924417; // 2^21 * 483 + 1
const int64_t MOD2 = 998244353;  // 2^20 * 476 + 1
NTT<MOD0, 1 << 21> NTTA;
NTT<MOD1, 1 << 21> NTTB;
signed main(void)
{
    clock_t tStart = clock();
    int64_t N, M, X, Y;
    while (cin >> N >> M >> X >> Y)
    {
        int64_t H = (X + 1) / 2 - 1;
        int64_t W = (Y + 1) / 2 - 1;
        vector<vector<int64_t>> g;
        vector<vector<int64_t>> image(X, vector<int64_t>(Y));
        vector<int64_t> zeros(2 * W + M);
        for (int64_t i = 0; i < H; i++)
        {
            g.push_back(zeros);
        }
        for (int64_t i = 0; i < N; i++)
        {
            vector<int64_t> Line;
            for (int64_t j = 0; j < W; j++)
            {
                Line.push_back(0);
            }
            for (int64_t j = 0; j < M; j++)
            {
                int64_t x;
                cin >> x;
                Line.push_back(x);
            }
            for (int64_t j = 0; j < W; j++)
            {
                Line.push_back(0);
            }
            g.push_back(Line);
        }
        for (int64_t i = 0; i < H; i++)
        {
            g.push_back(zeros);
        }
        for (int64_t i = 0; i < X; i++)
        {
            for (int64_t j = 0; j < Y; j++)
            {
                cin >> image[i][j];
            }
        }
        int64_t R = g.size();
        int64_t C = g[0].size();
        if (R <= C)
        {
            for (int64_t i = 0; i < X; i++)
            {
                reverse(image[i].begin(), image[i].end());
            }
            vector<int64_t> ret;
            for (int64_t k = 0; k <= R; k++)
            {
                vector<int64_t> get_ret(C);
                for (int64_t i = k; i < min(k + X, R); i++)
                {
                    auto polyA = NTTA.multiply(image[i - k], g[i]);
                    auto polyB = NTTB.multiply(image[i - k], g[i]);
                    for (int64_t j = 0; j < C; j++)
                    {
                        CRT<int64_t> crt;
                        crt.add(MOD0, polyA[j + Y - 1]);
                        crt.add(MOD1, polyB[j + Y - 1]);
                        get_ret[j] += crt.res;
                    }
                }
                for (int64_t i = 0; i < C - Y + 1; i++)
                {
                    ret.push_back(get_ret[i]);
                }
            }
            for (int64_t i = 0; i < N; i++)
            {
                for (int64_t j = 0; j < M; j++)
                {
                    cout << ret[i * M + j] << " ";
                }
                cout << '\n';
            }
        }
        else
        {
            vector<vector<int64_t>> rg(C, vector<int64_t>(R, 0));
            vector<vector<int64_t>> rimage(Y, vector<int64_t>(X, 0));
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    rg[j][i] = g[i][j];
                }
            }
            for (int i = 0; i < X; i++)
            {
                for (int j = 0; j < Y; j++)
                {
                    rimage[j][i] = image[i][j];
                }
            }
            for (int64_t i = 0; i < Y; i++)
            {
                reverse(rimage[i].begin(), rimage[i].end());
            }
            vector<int64_t> ret;
            for (int64_t k = 0; k <= C; k++)
            {
                vector<int64_t> get_ret(R);
                for (int64_t i = k; i < min(k + Y, C); i++)
                {
                    auto polyA = NTTA.multiply(rimage[i - k], rg[i]);
                    auto polyB = NTTB.multiply(rimage[i - k], rg[i]);
                    for (int64_t j = 0; j < R; j++)
                    {
                        CRT<int64_t> crt;
                        crt.add(MOD0, polyA[j + X - 1]);
                        crt.add(MOD1, polyB[j + X - 1]);
                        get_ret[j] += crt.res;
                    }
                }
                for (int64_t i = 0; i < R - X + 1; i++)
                {
                    ret.push_back(get_ret[i]);
                }
            }
            vector<vector<int64_t>> rret(M, vector<int64_t>(N));
            for (int64_t i = 0; i < M; i++)
            {
                for (int64_t j = 0; j < N; j++)
                {
                    rret[i][j] = ret[i * N + j];
                }
            }
            for (int64_t i = 0; i < N; i++)
            {
                for (int64_t j = 0; j < M; j++)
                {
                    cout << rret[j][i] << ' ';
                }
                cout << '\n';
            }
        }
        printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    }
    // This should work but the NTT template is not working well as expected
    // Complexity : O(H * W + sqrt(min(H, W)) * max(H,W) * log(max(H, W)))
    return 0;
}
/*
1280 2020 2410 2800 1840
2760 4110 4560 5010 3180
4410 6360 6810 7260 4530
6060 8610 9060 9510 5880
3200 4360 4570 4780 2800

94 154 106
186 285 186
285 420 267
384 555 348
202 280 166

*/