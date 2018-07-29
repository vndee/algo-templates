#include <bits/stdc++.h>

using namespace std;

const int N = 10001;
const int inf = 2000000000;

int dfs_num[N], dfs_low[N];
stack <int> st;
vector <int> adj[N];
int cnt = 0, nscc;

void dfs_tarjan(int u) {
    dfs_low[u] = dfs_num[u] = ++cnt;
    st.push(u);
    for (int j = 0; j < (int) adj[u].size(); j++) {
        int v = adj[u][j];
        if (dfs_num[v]) dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        else dfs_tarjan(v), dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if (dfs_num[u] == dfs_low[u]) {
        nscc++;
        int v;
        do {
            v = st.top();
            //scc[nscc].push_back(v);
            st.pop();
            dfs_num[v] = dfs_low[v] = inf;
        } while (v != u);
    }
}

int main() {
    //freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d\n", &u, &v);
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfs_num[i]) dfs_tarjan(i);
    printf("%d\n", nscc);
    //for (int i = 1; i <= nscc; i++) {
    //    for (int j = 0; j < scc[i].size(); j++)
    //        printf("%d ", scc[i][j]);
    //    printf("\n");
    //}
    return 0;
}
