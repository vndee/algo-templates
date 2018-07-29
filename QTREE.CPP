#include <bits/stdc++.h>

#define task "QTREE"
#define DEBUG

using namespace std;

const int N = 10001;
const int inf = 0x3f3f3f3f;

struct Edge {
    int u, v, cost;
    Edge() {}
    Edge(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {};
    int getNb(int V) { return V == v ? u : v; }
} ed[N];

vector <int> adj[N];
int n, LN, nChains, nBase;
int ChainInd[N], Base[N], posInBase[N], ChildSz[N], ChainHead[N];
int depth[N], par[N][32], d[N][32], it[4*N];

void enter() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, c;    scanf("%d %d %d", &u, &v, &c);
        adj[u].push_back(i-1);  adj[v].push_back(i-1);
        ed[i-1] = Edge(u, v, c);
    }
}

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;   par[u][0] = p;  ChildSz[u] = 1;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = ed[adj[u][i]].getNb(u);
        if (v == p) continue;
        dfs(v, u);
        ChildSz[u] += ChildSz[v];
    }
}

void HLD(int u, int _cost) {
    if (ChainHead[nChains] == 0) ChainHead[nChains] = u;
    ChainInd[u] = nChains;
    posInBase[u] = nBase;
    if (u) Base[nBase++] = _cost;

    int special = 0, w;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = ed[adj[u][i]].getNb(u);
        if (v == par[u][0]) continue;

        if (ChildSz[v] > ChildSz[special])
            special = v,
            w = ed[adj[u][i]].cost;
    }

    if (!special) return;
    HLD(special, w);

    for (int i = 0; i < adj[u].size(); i++) {
        int v = ed[adj[u][i]].getNb(u);
        if (v == special || v == par[u][0]) continue;

        ++nChains;
        HLD(v, ed[adj[u][i]].cost);
    }
}

void build(int id, int l, int r) {
    if (l == r) {
        it[id] = Base[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    it[id] = max(it[id << 1], it[id << 1 | 1]);
}

void update(int id, int l, int r, int pos) {
    if (l > pos || r < pos) return;
    if (l == pos && r == pos) {
        it[id] = Base[pos];
        return;
    }

    int mid = (l + r) >> 1;
    if (pos <= mid) update(id << 1, l, mid, pos);
    else update(id << 1 | 1, mid + 1, r, pos);
    it[id] = max(it[id << 1], it[id << 1 | 1]);
}

int query(int id, int l, int r, int u, int v) {
    if (l > v || u > r) return -1;
    if (l >= u && r <= v) return it[id];

    int mid = (l + r) >> 1;
    return max(query(id << 1, l, mid, u, v),
               query(id << 1 | 1, mid + 1, r, u, v));
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
        if ((delta >> i) & 1)
            u = par[u][i];

    if (u == v) return u;

    for (int i = LN; i >= 0; i--)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];

    return par[u][0];
}

int hld_query(int u, int v) {
    if (u == v) return 0;
    int ans = -1;

    while (true) {
        if (ChainInd[u] == ChainInd[v]) {
            if (posInBase[u] == posInBase[v]) return ans;
            return ans = max(ans, query(1, 0, nBase - 1, posInBase[v] + 1, posInBase[u]));
        } else {
            ans = max(ans, query(1, 0, nBase - 1, posInBase[ChainHead[ChainInd[u]]], posInBase[u]));
            u = par[ChainHead[ChainInd[u]]][0];
        }
    }
}

int query(int u, int v) {
    int _lca = LCA(u, v);
    return max(hld_query(u, _lca), hld_query(v, _lca));
}

void change(int id, int c) {
    Edge &e = ed[id - 1];
    e.cost = c;
    int child = (e.u == par[e.v][0] ? e.v : e.u);
    Base[posInBase[child]] = c;
    update(1, 0, nBase - 1, posInBase[child]);
}

void init() {
    dfs(1, 0);
    RMQ();
    nChains = nBase = 0;
    HLD(1, 0);
    build(1, 0, nBase - 1);
}

void reset() {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        ed[i] = Edge();
        ChildSz[i] = 0;
        ChainHead[i] = 0;
        ChainInd[i] = 0;
        posInBase[i] = 0;
        Base[i] = 0;
        depth[i] = 0;
        par[i][0] = 0;
    }
}

#ifdef DEBUG
    void generate_graph_random(int t, int v, int op) {
        ofstream out("QTREE.INP");
        out << t << endl;
        srand(time(NULL));
        int FROM = 4000, TO = 4001;
        for (int i = 0; i < t; i++) {
            out << v << endl;
            vector <int> used;
            used.reserve(v);
            used.push_back(1);
            for (int j = 2; j <= v; j++) {
                int cost = rand() % 100 + 5;
                int u = used[rand() % used.size()];
                used.push_back(j);
                out << u << " " << j << " " << cost << endl;
            }

            for (int j = 0; j < op; j++) {
                int M = rand() % 2;
                if (M == 0) {
                    // query
                    int A = rand() % v + 1;
                    int B = rand() % v + 1;
                    out << "QUERY " << A << " " << B << endl;
                } else {
                    // update
                    int A = rand() % (v - 1) + 1;
                    int B = rand() % 10000 + 5;
                    out << "CHANGE " << A << " " << B << endl;
                }
            }
            out << "DONE" << endl;
        }
        out.close();
    }

    int bruteforce_query(int u, int c, int p, int r) {
        if (u == r) {
            return c;
        }
        int res = 0;
        for (int i = 0; i < adj[u].size();i++) {
            int v = ed[adj[u][i]].getNb(u);
            if (p == v) continue;
            int q = bruteforce_query(v, ed[adj[u][i]].cost, u, r);
            if (q) q = max(q, ed[adj[u][i]].cost);
            res = max(res, q);
        }
        return res;
}

#endif // DEBUG

void process() {

    enter();
    init();

    while (true) {
        char buff[10];  scanf("%s", buff);
        if (*buff == 'D') break;
        if (*buff == 'Q') {
            int u, v;   scanf("%d %d", &u, &v);
            printf("%d\n", query(u, v));

            #ifdef DEBUG
                assert(query(u, v) == bruteforce_query(u, 0, 0, v));
            #endif // DEBUG
        } else {
            int u, v;   scanf("%d %d", &u, &v);
            change(u, v);
        }
    }

    reset();
}

int main() {
    #ifndef ONLINE_JUDGE
        assert(freopen(task".INP", "r", stdin));
        assert(freopen(task".OUT", "w", stdout));
    #endif // ONLINE_JUDGE

    #ifdef DEBUG
        generate_graph_random(10, 100, 10);
    #endif // DEBUG

    int Case;   scanf("%d", &Case);
    while (Case--) process();

    return 0;
}
