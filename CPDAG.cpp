#include <bits/stdc++.h>

using namespace std;

const int N = 100001;
const int M = 1000000007;

int n, m, f[N], deg[N];
vector<int> adj[N];

int main() {
    ios_base::sync_with_stdio(0);   cin.tie(NULL);
    freopen("cpdag.inp", "r", stdin);
    freopen("cpdag.out", "w", stdout);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;   cin >> u >> v;
        adj[u].push_back(v);
        deg[v]++;
    }

    queue <int> q;
    for (int i = 1; i <= n; i++)
        if (!deg[i]) q.push(i);

    for (int i = 1; i <= n; i++) f[i] = 1;
    while (!q.empty()) {
        int u = q.front();    q.pop();
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            f[v] = (f[u] % M + f[v] % M) % M;
            deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans % M + f[i] % M) % M;

    cout << ans - n << endl;

    return 0;
}
