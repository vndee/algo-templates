#include <bits/stdc++.h>

#define task "main"
#define val first
#define idx second

//#define DEBUG

using namespace std;

const int N = 100001;
const int inf = 0x3f3f3f;

int n, q, nChains, nBase;
int Base[N], posInBase[N], ChainHead[N];
int ChainInd[N], depth[N], par[N][17];
int ChildSz[N], leaf[N], nodeID[N];

pair<int, int> it[4*N];
vector <int> adj[N];

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    ChildSz[u] = 1;
    par[u][0] = p;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == p) continue;
        dfs(v, u);
        ChildSz[u] += ChildSz[v];
    }
}

void HLD(int u) {
    if (ChainHead[nChains] == 0) ChainHead[nChains] = u;
    ChainInd[u] = nChains;
    posInBase[u] = nBase;
    nodeID[posInBase[u]] = u;
    if (u) Base[nBase++] = inf;

    int heavy = 0;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == par[u][0]) continue;

        if (ChildSz[v] > ChildSz[heavy])
            heavy = v;
    }

    if (heavy == 0) return;
    HLD(heavy);

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v == par[u][0] || v == heavy) continue;

        nChains++;
        HLD(v);
    }
}

void build(int id, int l, int r) {
    if (l == r) {
        it[id] = make_pair(Base[l], l);
        leaf[l] = id;
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    it[id] = min(it[id << 1], it[id << 1 | 1]);
}

void update(int id, int l, int r, int pos, int val) {
    if (l > pos || r < pos) return;
    if (l == pos && r == pos) {
        it[id].val = val;
        return;
    }

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, pos, val);
    update(id << 1 | 1, mid + 1, r, pos, val);
    it[id] = min(it[id << 1], it[id << 1 | 1]);
}

pair<int, int> query(int id, int l, int r, int u, int v) {
    if (l > v || r < u) return make_pair(inf, 0);
    if (l >= u && r <= v) return it[id];

    int mid = (l + r) >> 1;
    return min(query(id << 1, l, mid, u, v),
               query(id << 1 | 1, mid + 1, r, u, v));
}

void update(int pos) {
    int _pos = leaf[posInBase[pos]];
    if (it[_pos].val == inf) {
        Base[posInBase[pos]] = depth[pos];
        update(1, 0, nBase - 1, posInBase[pos], depth[pos]);
    } else {
        Base[posInBase[pos]] = inf;
        update(1, 0, nBase - 1, posInBase[pos], inf);
    }
}

pair<int, int> hld_query(int u, int v) {
    if (u == v) return make_pair(Base[posInBase[u]], posInBase[u]);
    pair<int, int> ans = make_pair(inf, 0);

    while (true) {
        if (ChainInd[u] == ChainInd[v]) {
            if (posInBase[u] == posInBase[v]) return min(ans, make_pair(Base[posInBase[u]], posInBase[u]));
            return ans = min(ans,
                             query(1, 0, nBase - 1, posInBase[v], posInBase[u]));
        } else {
            ans = min(ans, query(1, 0, nBase - 1, posInBase[ChainHead[ChainInd[u]]], posInBase[u]));
            u = par[ChainHead[ChainInd[u]]][0];
        }
    }
}

int ask(int pos) {
    pair<int, int> res = hld_query(pos, 1);
    return res.val == inf ? -1 : nodeID[res.idx];
}
#ifdef DEBUG
    int color[N];

    void generate_random_graph(int _v, int _op) {
        ofstream out("main.inp");
        srand(time(NULL));
        int v = rand() % _v + 1, op = rand() % _op + 1;
        out << v << " " << op << endl;

        vector <int> used;  used.reserve(v);    used.push_back(1);
        for (int j = 2; j <= v; j++) {
            int u = used[rand() % used.size()];
            used.push_back(j);
            out << u << " " << j << endl;
        }

        for (int i = 0; i < op; i++) {
            int M = rand() % 2;
            int A = rand() % v + 1;
            out << M << " " << A << endl;
        }
        out.close();
    }

    void slow_upd(int u) {
        color[u] = 1 - color[u];
    }

    int fr[N];
    int slow_answer(int target) {
        queue <int> q;  q.push(1);
        memset(fr, 0, sizeof fr);
        fr[1] = -1;

        while (!q.empty()) {
            int u = q.front();  q.pop();
            if (u == target) break;

            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                if (fr[v]) continue;
                fr[v] = u;
                q.push(v);
            }
        }

        if (fr[target] == 0) return -1;

        vector <int> path;
        while (fr[target] != -1) path.push_back(target), target = fr[target];
        path.push_back(1);
        for (int i = path.size() - 1; i >= 0; i--)
            if (color[path[i]]) return path[i];
        return -1;
    }
#endif // DEBUG

int main() {
    #ifndef ONLINE_JUDGE
        assert(freopen(task".inp", "r", stdin));
        assert(freopen(task".out", "w", stdout));
    #endif // ONLINE_JUDGE

    #ifdef DEBUG
        generate_random_graph(6, 6);
    #endif // DEBUG

    scanf("%d %d\n", &n, &q);
    for (int i = 1; i < n; i++) {
        int u, v;   scanf("%d %d\n", &u, &v);
        adj[u].push_back(v);    adj[v].push_back(u);
    }

    dfs(1, 0);
    HLD(1);
    build(1, 0, nBase - 1);

    while (q--) {
        int u, v;   scanf("%d %d\n", &u, &v);
        if (u == 0) {
            update(v);

            #ifdef DEBUG
                slow_upd(v);
            #endif // DEBUG
        }
        else {
            printf("%d\n", ask(v));

            #ifdef DEBUG
                assert(slow_answer(v) == ask(v));
            #endif // DEBUG
        }
    }

    return 0;
}
