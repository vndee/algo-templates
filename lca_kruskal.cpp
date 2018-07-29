#include <bits/stdc++.h>

#define ver first
#define len second

using namespace std;

typedef long long ll;
typedef pair<int, ll> ii;
typedef vector<ii> vi;

const int N = 100001;
const ll inf = 100000001;

struct pack {
    int u, v;
    ll w;
    bool mark;
} a[N];

vi adj[N];
int n, m, k, par[N][20];
int p[N], tr[N], H[N], rank[N];
ll d[N][20];

bool cmp(pack a, pack b) {
    return a.w > b.w;
}

int findset(int x) {
    return p[x] == 0 ? x : p[x] = findset(p[x]);
}

void join(int x, int y) {
    if (rank[x] > rank[y])
        rank[x] += rank[y],
        p[y] = x;
    else
        rank[y] += rank[x],
        p[x] = y;
}

void kruskal() {
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= n; i++) p[i] = 0, rank[i] = 1;

    for (int i = 1; i <= m; i++) {
        int r1 = findset(a[i].u);
        int r2 = findset(a[i].v);
        if (r1 == r2) continue;
        a[i].mark = true;
        join(r1, r2);
    }
}

void bfs() {
    queue<int> q;   q.push(1);
    H[1] = 0;   tr[1] = 1;
    while (!q.empty()) {
        int u = q.front();  q.pop();
        for (int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j].ver;
            if (tr[v]) continue;
            tr[v] = 1;
            H[v] = H[u] + 1;
            par[v][0] = u;
            d[v][0] = adj[u][j].len;
            q.push(v);
        }
    }
}

void rmq() {
    for (int j = 1; j <= k; j++)
        for (int i = 1; i <= n; i++) {
            par[i][j] = par[par[i][j-1]][j-1];
            if (par[i][j] != 0) d[i][j] = min(d[i][j-1], d[par[i][j-1]][j-1]);
            else d[i][j] = inf;
        }
}

ll lca(int u, int v) {
    if (H[u] < H[v]) swap(u, v);
    ll res = inf;
    int delta = H[u] - H[v];
    for (int i = k; i >= 0; i--)
        if ((delta >> i) & 1)
            res = min(res, d[u][i]),
            u = par[u][i];

    if (u == v) return res;
    for (int i = k; i >= 0; i--)
        if (par[u][i] != par[v][i])
            res = min(res, min(d[u][i], d[v][i])),
            u = par[u][i],  v = par[v][i];

    res = min(res, min(d[u][0], d[v][0]));
    return res;
}

int main() {
 	ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i].u >> a[i].v >> a[i].w;
    }

    kruskal();

    ll ans = 0; k = trunc(log(n)/log(2));
    for (int i = 1; i <= m; i++) {
        if (!a[i].mark) continue;
        adj[a[i].u].push_back(ii(a[i].v, a[i].w));
        adj[a[i].v].push_back(ii(a[i].u, a[i].w));
    }

    bfs();  rmq();

    for (int i = 1; i <= m; i++) {
        if (a[i].mark) continue;
        ans += lca(a[i].u, a[i].v) - a[i].w;
    }

    cout << ans << endl;

    return 0;
}
