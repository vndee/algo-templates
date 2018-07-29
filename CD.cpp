#include <bits/stdc++.h>

//#define DEBUG

using namespace std;

const int N = 100001;
const int inf = 0x3f3f3f3f;

set <int> adj[N];
int n, m, total, LN;
int dad[N], par[N][20], ChildSz[N], depth[N], ans[N];

void dfs(int u, int p) {
    par[u][0] = p;  depth[u] = depth[p] + 1;

    for (set <int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (v == p) continue;
        dfs(v, u);
    }
}

void RMQ() {
    LN = trunc(log(n)/log(2)) + 1;
    for (int j = 1; j <= LN; j++)
        for (int i = 1; i <= n; i++)
            par[i][j] = par[par[i][j-1]][j-1];
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int delta = depth[u] - depth[v];

    for (int i = LN; i >= 0; i--)
        if ((delta >> i) & 1) u = par[u][i];

    if (u == v) return u;

    for (int i = LN; i >= 0; i--)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];

    return par[u][0];
}

int dist(int u, int v) {
    return depth[u] + depth[v] - 2*depth[LCA(u, v)];
}

int find_centroid(int u, int p) {
    for (set <int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (v != p && ChildSz[v] > total / 2)
            return find_centroid(v, u);
    }
    return u;
}

void dfs_subtree(int u, int p) {
    ChildSz[u] = 1;     total++;

    for (set <int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (v == p) continue;

        dfs_subtree(v, u);
        ChildSz[u] += ChildSz[v];
    }
}

void Centroid_decompose(int u, int p) {
    total = 0;
    dfs_subtree(u, u);

    int centroid = find_centroid(u, u);
    if (p == 0) p = centroid;

    dad[centroid] = p;
    for (set <int>::iterator it = adj[centroid].begin(); it != adj[centroid].end(); it++) {
        int v = *it;
        adj[v].erase(centroid);
        Centroid_decompose(v, centroid);
    }
    adj[centroid].clear();
}

void update(int u) {
    int x = u;
    while (true) {
        ans[x] = min(ans[x], dist(x, u));
        if (x == dad[x]) break;
        x = dad[x];
    }
}

int query(int u) {
    int x = u, res = inf;
    while (true) {
        res = min(res, dist(u, x) + ans[x]);
        if (x == dad[x]) break;
        x = dad[x];
    }
    return res;
}

#ifdef DEBUG
    set <int> slow_adj[N];
    int color[N], d[N];

    void generate_random_graph(int _n, int _m) {
        srand(time(NULL));
        int n = rand() % _n + 1, m = rand() % _m + 1;
        ofstream out("main.inp");
        out << n << " " << m << endl;

        vector <int> used;  used.reserve(n);
        used.push_back(1);
        for (int j = 2; j <= n; j++) {
            int u = used[rand() % used.size()];
            used.push_back(j);
            out << u << " " << j << endl;
        }

        for (int i = 1; i <= m; i++) {
            int t = rand() % 2 + 1;
            int v = rand() % n + 1;
            out << t << " " << v << endl;
        }
        out.close();
    }

    void slow_update(int v) {
        color[v] = 1;
    }

    int slow_query(int v) {
        memset(d, 0, sizeof d);
        queue <int> q;  q.push(v);

        while (!q.empty()) {
            int u = q.front();  q.pop();

            if (color[u]) return d[u];

            for (set <int>::iterator it = slow_adj[u].begin(); it != slow_adj[u].end(); it++) {
                int v = *it;
                if (d[v]) continue;

                d[v] = d[u] + 1;
                q.push(v);
            }
        }

        return 0;
    }
#endif // DEBUG

int main() {
    #ifndef ONLINE_JUDGE
        assert(freopen("main.inp", "r", stdin));
        assert(freopen("main.out", "w", stdout));
    #endif // ONLINE_JUDGE

    #ifdef DEBUG
        generate_random_graph(100, 100);
    #endif // DEBUG

    scanf("%d %d\n", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;   scanf("%d %d\n", &u, &v);
        adj[u].insert(v);   adj[v].insert(u);

        #ifdef DEBUG
            slow_adj[u].insert(v);
            slow_adj[v].insert(u);
        #endif // DEBUG
    }

    dfs(1, 0);
    RMQ();
    Centroid_decompose(1, 0);
    for (int i = 1; i <= n; i++) ans[i] = inf;
    update(1);

    #ifdef DEBUG
        slow_update(1);
    #endif // DEBUG

    while (m--) {
        int t, v;   scanf("%d %d\n", &t, &v);
        if (t == 1) {
            update(v);

            #ifdef DEBUG
                slow_update(v);
            #endif // DEBUG
        }
        else {
            printf("%d\n", query(v));


            #ifdef DEBUG
                assert(query(v) == slow_query(v));
            #endif // DEBUG
        }
    }

    return 0;
}