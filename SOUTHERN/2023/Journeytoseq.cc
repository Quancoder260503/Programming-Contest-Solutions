#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
// ModInt {{{
template <int MD>
struct ModInt
{
    using ll = long long;
    int x;

    constexpr ModInt() : x(0) {}
    constexpr ModInt(ll v) { _set(v % MD + MD); }
    constexpr static int mod() { return MD; }
    constexpr explicit operator bool() const { return x != 0; }

    constexpr ModInt operator+(const ModInt &a) const
    {
        return ModInt()._set((ll)x + a.x);
    }
    constexpr ModInt operator-(const ModInt &a) const
    {
        return ModInt()._set((ll)x - a.x + MD);
    }
    constexpr ModInt operator*(const ModInt &a) const
    {
        return ModInt()._set((ll)x * a.x % MD);
    }
    constexpr ModInt operator/(const ModInt &a) const
    {
        return ModInt()._set((ll)x * a.inv().x % MD);
    }
    constexpr ModInt operator-() const
    {
        return ModInt()._set(MD - x);
    }

    constexpr ModInt &operator+=(const ModInt &a) { return *this = *this + a; }
    constexpr ModInt &operator-=(const ModInt &a) { return *this = *this - a; }
    constexpr ModInt &operator*=(const ModInt &a) { return *this = *this * a; }
    constexpr ModInt &operator/=(const ModInt &a) { return *this = *this / a; }

    friend constexpr ModInt operator+(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD + b.x);
    }
    friend constexpr ModInt operator-(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD - b.x + MD);
    }
    friend constexpr ModInt operator*(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.x % MD);
    }
    friend constexpr ModInt operator/(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.inv().x % MD);
    }

    constexpr bool operator==(const ModInt &a) const { return x == a.x; }
    constexpr bool operator!=(const ModInt &a) const { return x != a.x; }

    friend std::istream &operator>>(std::istream &is, ModInt &other)
    {
        ll val;
        is >> val;
        other = ModInt(val);
        return is;
    }
    constexpr friend std::ostream &operator<<(std::ostream &os, const ModInt &other)
    {
        return os << other.x;
    }

    constexpr ModInt pow(ll k) const
    {
        ModInt ans = 1, tmp = x;
        while (k)
        {
            if (k & 1)
                ans *= tmp;
            tmp *= tmp;
            k >>= 1;
        }
        return ans;
    }

    constexpr ModInt inv() const
    {
        if (x < 1000111)
        {
            _precalc(1000111);
            return invs[x];
        }
        int a = x, b = MD, ax = 1, bx = 0;
        while (b)
        {
            int q = a / b, t = a % b;
            a = b;
            b = t;
            t = ax - bx * q;
            ax = bx;
            bx = t;
        }
        assert(a == 1);
        if (ax < 0)
            ax += MD;
        return ax;
    }

    static std::vector<ModInt> factorials, inv_factorials, invs;
    constexpr static void _precalc(int n)
    {
        if (factorials.empty())
        {
            factorials = {1};
            inv_factorials = {1};
            invs = {0};
        }
        if (n > MD)
            n = MD;
        int old_sz = factorials.size();
        if (n <= old_sz)
            return;

        factorials.resize(n);
        inv_factorials.resize(n);
        invs.resize(n);

        for (int i = old_sz; i < n; ++i)
            factorials[i] = factorials[i - 1] * i;
        inv_factorials[n - 1] = factorials.back().pow(MD - 2);
        for (int i = n - 2; i >= old_sz; --i)
            inv_factorials[i] = inv_factorials[i + 1] * (i + 1);
        for (int i = n - 1; i >= old_sz; --i)
            invs[i] = inv_factorials[i] * factorials[i - 1];
    }

    static int get_primitive_root()
    {
        static int primitive_root = 0;
        if (!primitive_root)
        {
            primitive_root = [&]()
            {
                std::set<int> fac;
                int v = MD - 1;
                for (ll i = 2; i * i <= v; i++)
                    while (v % i == 0)
                        fac.insert(i), v /= i;
                if (v > 1)
                    fac.insert(v);
                for (int g = 1; g < MD; g++)
                {
                    bool ok = true;
                    for (auto i : fac)
                        if (ModInt(g).pow((MD - 1) / i) == 1)
                        {
                            ok = false;
                            break;
                        }
                    if (ok)
                        return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }

    static ModInt C(int n, int k)
    {
        _precalc(n + 1);
        return factorials[n] * inv_factorials[k] * inv_factorials[n - k];
    }

private:
    // Internal, DO NOT USE.
    // val must be in [0, 2*MD)
    constexpr inline __attribute__((always_inline)) ModInt &_set(ll v)
    {
        x = v >= MD ? v - MD : v;
        return *this;
    }
};
template <int MD>
std::vector<ModInt<MD>> ModInt<MD>::factorials = {1};
template <int MD>
std::vector<ModInt<MD>> ModInt<MD>::inv_factorials = {1};
template <int MD>
std::vector<ModInt<MD>> ModInt<MD>::invs = {0};
// }}}
using mint = ModInt<mod>; 
/* Source code from RR*/
template <typename T>
vector<T> berlekampMassey(vector<T> s)
{
    if (s.empty())
        return {};

    int n = s.size(), L = 0, m = 0; // m = i - f
    vector<T> C(n), D(n), oldC;
    C[0] = D[0] = 1;
    T df1 = 1; // d(f+1)
    for (int i = 0; i < n; i++)
    {
        ++m;
        // check if C(i) == a(i)
        // delta = s_i - sum( cj * s(i-j) ) = d(f+1)?
        T delta = s[i];
        for (int j = 1; j <= L; j++)
        {
            delta += C[j] * s[i - j]; // C(j) is already multiplied by -1
        }
        if (delta == 0)
            continue; // C(i) is correct

        // Update c = c + d
        oldC = C;
        T coeff = delta * df1.inv();
        for (int j = m; j < n; j++)
        {
            C[j] -= coeff * D[j - m]; // prepend D with m zeroes, multiply by coeff and add to C
        }
        if (2 * L > i)
            continue;
        L = i + 1 - L, D = oldC, df1 = delta, m = 0;
    }
    C.resize(L + 1);
    C.erase(C.begin());
    for (auto &x : C)
        x = -x;
    return C;
}

// Helper function
template <typename T>
vector<T> mul(const vector<T> &a, const vector<T> &b, const vector<T> &c)
{
    vector<T> ret(a.size() + b.size() - 1);
    // ret = a * b
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            ret[i + j] += a[i] * b[j];

    int n = c.size();
    // reducing ret mod f(x)
    for (int i = (int)ret.size() - 1; i >= n; i--)
        for (int j = n - 1; j >= 0; j--)
            ret[i - j - 1] += ret[i] * c[j];
    ret.resize(min((int)ret.size(), n));
    return ret;
}

// Find k-th element in linear recurrence: O(d^2 * logn)
// Need faster code? See https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
//   (but usually not needed since bottleneck is BerlekampMassey
//
// Params:
// - c: as returned by berlekampMassey
// - s: s0, s1, ..., s(N-1)
// Returns: s(k)
template <typename T>
T solve(const vector<T> &c, const vector<T> &s, long long k)
{
    int n = (int)c.size();
    assert(c.size() <= s.size());

    vector<T> a = n == 1 ? vector<T>{c[0]} : vector<T>{0, 1}, x{1};
    for (; k > 0; k /= 2)
    {
        if (k % 2) x = mul(x, a, c); // mul(a, b) computes a(x) * b(x) mod f(x)
        a = mul(a, a, c);
    }
    x.resize(n);

    T ret = 0;
    for (int i = 0; i < n; i++) ret += x[i] * s[i];
    return ret;
}
// }}}
const int M = 3000; 
int main(void)
{
    int T; 
    cin >> T;
    int64_t N, K, R;
    while(T--)
    {
        cin >> K >> N >> R; 
        vector<mint> s(M);
        s[0] = 0;
        for (int i = 1; i < M; i++)
        {
            s[i] = s[i - 1] + mint(i).pow(K) * mint(R).pow(i); 
        }
        auto c = berlekampMassey<mint>(s); 
        auto ret = solve<mint>(c, s, N); 
        cout << ret << '\n'; 
    }
    return 0; 
}