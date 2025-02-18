#include "bits/stdc++.h"
using namespace std;
const int M = 30;
template <typename T>
struct Matrix
{
    int n_row, n_col;
    vector<T> x;

    // accessors
    typename vector<T>::iterator operator[](int r)
    {
        return x.begin() + r * n_col;
    }
    inline T get(int i, int j) const { return x[i * n_col + j]; }
    vector<T> at(int r) const
    {
        return vector<T>{x.begin() + r * n_col, x.begin() + (r + 1) * n_col};
    }

    // constructors
    Matrix() = default;
    Matrix(int _n_row, int _n_col) : n_row(_n_row), n_col(_n_col), x(n_row * n_col) {}
    Matrix(const vector<vector<T>> &d) : n_row(d.size()), n_col(d.size() ? d[0].size() : 0)
    {
        for (auto &row : d)
            std::copy(row.begin(), row.end(), std::back_inserter(x));
    }

    // convert to 2d vec
    vector<vector<T>> vecvec() const
    {
        vector<vector<T>> ret(n_row);
        for (int i = 0; i < n_row; i++)
        {
            std::copy(x.begin() + i * n_col,
                      x.begin() + (i + 1) * n_col,
                      std::back_inserter(ret[i]));
        }
        return ret;
    }
    operator vector<vector<T>>() const { return vecvec(); }

    static Matrix identity(int n)
    {
        Matrix res(n, n);
        for (int i = 0; i < n; i++)
        {
            res[i][i] = 1;
        }
        return res;
    }

    Matrix transpose() const
    {
        Matrix res(n_col, n_row);
        for (int i = 0; i < n_row; i++)
        {
            for (int j = 0; j < n_col; j++)
            {
                res[j][i] = this->get(i, j);
            }
        }
        return res;
    }

    Matrix &operator*=(const Matrix &r) { return *this = *this * r; }
    Matrix operator*(const Matrix &r) const
    {
        assert(n_col == r.n_row);
        Matrix res(n_row, r.n_col);

        for (int i = 0; i < n_row; i++)
        {
            for (int k = 0; k < n_col; k++)
            {
                for (int j = 0; j < r.n_col; j++)
                {
                    res[i][j] += this->get(i, k) * r.get(k, j);
                }
            }
        }
        return res;
    }

    Matrix pow(long long n) const
    {
        assert(n_row == n_col);
        Matrix res = identity(n_row);
        if (n == 0)
            return res;

        bool res_is_id = true;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--)
        {
            if (!res_is_id)
                res *= res;
            if ((n >> i) & 1)
                res *= (*this), res_is_id = false;
        }
        return res;
    }

    // Gauss
    template <typename T2, typename std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept
    {
        int piv = -1;
        for (int j = h; j < mtr.n_row; j++)
        {
            if (mtr.get(j, c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))
                piv = j;
        }
        return piv;
    }
    template <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept
    {
        for (int j = h; j < mtr.n_row; j++)
        {
            if (mtr.get(j, c) != T(0))
                return j;
        }
        return -1;
    }

    // return upper triangle matrix
    [[nodiscard]] Matrix gauss() const
    {
        int c = 0;
        Matrix mtr(*this);
        vector<int> ws;
        ws.reserve(n_col);

        for (int h = 0; h < n_row; h++)
        {
            if (c == n_col)
                break;
            int piv = choose_pivot(mtr, h, c);
            if (piv == -1)
            {
                c++;
                h--;
                continue;
            }
            if (h != piv)
            {
                for (int w = 0; w < n_col; w++)
                {
                    swap(mtr[piv][w], mtr[h][w]);
                    mtr[piv][w] *= -1; // for determinant
                }
            }
            ws.clear();
            for (int w = c; w < n_col; w++)
            {
                if (mtr[h][w] != 0)
                    ws.emplace_back(w);
            }
            const T hcinv = T(1) / mtr[h][c];
            for (int hh = 0; hh < n_row; hh++)
            {
                if (hh != h)
                {
                    const T coeff = mtr[hh][c] * hcinv;
                    for (auto w : ws)
                        mtr[hh][w] -= mtr[h][w] * coeff;
                    mtr[hh][c] = 0;
                }
            }
            c++;
        }
        return mtr;
    }

    // For upper triangle matrix
    T det() const
    {
        T ret = 1;
        for (int i = 0; i < n_row; i++)
        {
            ret *= get(i, i);
        }
        return ret;
    }

    // return rank of inverse matrix. If rank < n -> not invertible
    int inverse()
    {
        assert(n_row == n_col);
        vector<vector<T>> ret = identity(n_row), tmp = *this;
        int rank = 0;

        for (int i = 0; i < n_row; i++)
        {
            int ti = i;
            while (ti < n_row && tmp[ti][i] == 0)
                ++ti;
            if (ti == n_row)
                continue;
            else
                ++rank;

            ret[i].swap(ret[ti]);
            tmp[i].swap(tmp[ti]);

            T inv = T(1) / tmp[i][i];
            for (int j = 0; j < n_col; j++)
                ret[i][j] *= inv;
            for (int j = i + 1; j < n_col; j++)
                tmp[i][j] *= inv;

            for (int h = 0; h < n_row; h++)
            {
                if (i == h)
                    continue;
                const T c = -tmp[h][i];
                for (int j = 0; j < n_col; j++)
                    ret[h][j] += ret[i][j] * c;
                for (int j = i + 1; j < n_col; j++)
                    tmp[h][j] += tmp[i][j] * c;
            }
        }

        *this = ret;
        return rank;
    }

    // sum of all elements in this matrix
    T sum_all()
    {
        return submatrix_sum(0, 0, n_row, n_col);
    }

    // sum of [r1, r2) x [c1, c2)
    T submatrix_sum(int r1, int c1, int r2, int c2)
    {
        T res{0};
        for (int r = r1; r < r2; ++r)
        {
            res += std::accumulate(
                x.begin() + r * n_col + c1,
                x.begin() + r * n_col + c2,
                T{0});
        }
        return res;
    }
};
template <typename T>
ostream &operator<<(ostream &cout, const Matrix<T> &m)
{
    cout << m.n_row << ' ' << m.n_col << endl;
    for (int i = 0; i < m.n_row; ++i)
    {
        cout << "row [" << i << "] = " << m.at(i) << endl;
    }
    return cout;
}
signed main(void)
{
    int T;
    string S;
    cin >> T;
    while (T--)
    {
        cin >> S;
        int N = S.length();
        Matrix<double> markov(N + 1, N + 2);
        for (int i = 0; i <= N; i++)
        {
            markov[i][i] = 1.0;
            markov[i][N + 1] = (i != N) * 1.0;
        }
        for (int i = 0; i < N; i++)
        {
            string prefix = S.substr(0, i);
            for (char k = '0'; k <= '1'; k++)
            {
                string prefix_ = prefix + k;
                for (int j = i + 1; j >= 0; j--)
                {
                    string suffix = S.substr(0, j);
                    if (prefix_.ends_with(suffix))
                    {
                        markov[i][j] -= 0.5;
                        break; 
                    }
                }
            }
        }
        auto ret = markov.gauss();
        auto back_sub = [&] (void)
        {
            vector<double>res(N + 1); 
            res[N] = ret[N][N + 1] / ret[N][N];
            for (int i = N - 1; i >= 0; i--)
            {
                for (int j = i + 1; j <= N; j++)
                {
                    ret[i][N + 1] = ret[i][N + 1] - ret[j][N + 1] * ret[i][j];
                }
                res[i] = ret[i][N + 1] / ret[i][i];
            }
            return res; 
        };
        auto res = back_sub(); 
        cout << fixed << setprecision(12) << res[0] << '\n'; 
    }
    return 0;
}