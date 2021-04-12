#include <iostream>
#include <vector>
#include <tuple>
#include <stdbool.h>
using namespace std;
const int INF = (int)1e9 + 7;

vector<int> knapsack(const vector<int> a, const vector<int> b, int k) {
    int n = a.size();
    int m = b.size();
    vector<int> c(n+m-1, -INF);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) c[i+j] = max(c[i+j], a[i] + b[j]);
    }
    if (c.size() > k) c.resize(k);
    return c;
}

pair<vector<int>, vector<int>> dfs(int i, int p, int k, const vector<vector<int>>& g) {
    vector<int> dp0 = {0, 0};
    vector<int> dp1 = {-INF, (int)g[i].size() - (p != -1)};
    for (auto t : g[i]) {
        if (t == p) continue;
        vector<int> dp0_t, dp1_t;
        tie(dp0_t, dp1_t) = dfs(t, i, k, g);
        int m = dp0_t.size();

        vector<int> off0(m), off1(m);
        for (int j = 0; j < m; ++j) off0[j] = max(dp0_t[j], dp1_t[j] + 1);
        for (int j = 0; j < m; ++j) off1[j] = max(dp0_t[j], dp1_t[j]);
        dp0 = knapsack(dp0, off0, k+1);
        dp1 = knapsack(dp1, off1, k+1);
    }
    return {dp0, dp1};
}

int minCover(int k, const vector<vector<int>>& g) {
    vector<int> dp0, dp1;
    tie(dp0, dp1) = dfs(0, -1, k, g);
    int result;
    for (int i = 0;; ++i) {
    		result = max(dp0[i], dp1[i]);
    		cout <<result<<endl;
        if (result>= k) return i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int t = minCover(k, g);
    cout << t << '\n';
}
