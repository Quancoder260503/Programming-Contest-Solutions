#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e4 + 10;
#define f first
#define s second
struct DirectedDfs
{
    vector<vector<int>> g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector<vector<int>> scc;

    DirectedDfs(const vector<vector<int>> &_g) : g(_g), n(g.size()),
                                                 num(n, -1), low(n, 0), current(n, 0), counter(0), comp_ids(n, -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (num[i] == -1)
                dfs(i);
        }
    }

    void dfs(int u)
    {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (auto v : g[u])
        {
            if (num[v] == -1)
                dfs(v);
            if (current[v])
                low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u])
        {
            scc.push_back(vector<int>());
            while (1)
            {
                int v = S.back();
                S.pop_back();
                current[v] = 0;
                scc.back().push_back(v);
                comp_ids[v] = ((int)scc.size()) - 1;
                if (u == v)
                    break;
            }
        }
    }

    // build DAG of strongly connected components
    // Returns: adjacency list of DAG
    std::vector<std::vector<int>> build_scc_dag()
    {
        std::vector<std::vector<int>> dag(scc.size());
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    dag[x].push_back(y);
                }
            }
        }
        return dag;
    }
};
struct TwoSatSolver
{
    TwoSatSolver(int _n_vars) : n_vars(_n_vars), g(2 * n_vars) {}
    void x_or_y_constraint(bool is_x_true, int x, bool is_y_true, int y)
    {
        assert(x >= 0 && x < n_vars);
        assert(y >= 0 && y < n_vars);
        if (!is_x_true)
            x += n_vars;
        if (!is_y_true)
            y += n_vars;
        // x || y
        // !x -> y
        // !y -> x
        g[(x + n_vars) % (2 * n_vars)].push_back(y);
        g[(y + n_vars) % (2 * n_vars)].push_back(x);
    }
    // Returns:
    // If no solution -> returns {false, {}}
    // If has solution -> returns {true, solution}
    //    where |solution| = n_vars, solution = true / false
    bool solve()
    {
        DirectedDfs tree(g);
        for (int i = 0; i < n_vars; i++)
        {
            if (tree.comp_ids[i] == tree.comp_ids[i + n_vars])
            {
                return false;
            }
        }
        return true;
    }
    void remove_edge(bool is_x_true, int x, bool is_y_true, int y)
    {
        assert(x >= 0 && x < n_vars);
        assert(y >= 0 && y < n_vars);
        if (!is_x_true)
            x += n_vars;
        if (!is_y_true)
            y += n_vars;
        g[(x + n_vars) % (2 * n_vars)].pop_back(); 
        g[(y + n_vars) % (2 * n_vars)].pop_back(); 
    }
    // number of variables
    int n_vars;
    // vertex 0 -> n_vars - 1: Ai is true
    // vertex n_vars -> 2*n_vars - 1: Ai is false
    vector<vector<int>> g;
};
int n;
using Point = pair<int, int>;
struct rec
{
    double xa, ya, xb, yb;
};
bool chk(const rec &a, const rec &b)
{
    if (a.xb <= b.xa)
        return true;
    if (a.yb <= b.ya)
        return true;
    if (b.xb <= a.xa)
        return true;
    if (b.yb <= a.ya)
        return true;
    return false;
}
signed main(void)
{
    cin >> n;
    vector<rec> srec;
    for (int i = 0; i < n; i++)
    {
        double x, y, w, h;
        cin >> x >> y >> w >> h;
        srec.push_back({x - w / 2.0, y - h / 2.0, x + w / 2.0, y + h / 2.0});
        srec.push_back({x - h / 2.0, y - w / 2.0, x + h / 2.0, y + w / 2.0});
    }
    string ret;
    TwoSatSolver tsat(n);
    for (int i = 0; i < srec.size(); i++)
    {
        for (int j = i + 1; j < srec.size(); j++)
        {
            if (!chk(srec[i], srec[j]))
            {
                int u = (i - (i & 1)) / 2;
                int v = (j - (j & 1)) / 2;
                int verdictu = (i & 1) xor 1;
                int verdictv = (j & 1) xor 1;
                tsat.x_or_y_constraint(verdictu, u, verdictv, v);
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        tsat.x_or_y_constraint(false, i, false, i);
        if(tsat.solve())
        {
            ret += 'K'; 
        }
        else 
        {
            ret += 'Q'; 
            tsat.remove_edge(false, i, false, i); 
            tsat.x_or_y_constraint(true, i, true, i); 
        }
    }
    bool res = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            res = res & (chk(srec[2 * i + (ret[i] == 'Q')], srec[2 * j + (ret[j] == 'Q')]));
        }
    }
    if (res)
    {
        cout << "Yes" << '\n'
             << ret << '\n';
    }
    else
    {
        cout << "No" << '\n';
    }
    return 0;
}