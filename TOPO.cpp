#include <bits/stdc++.h>

#define DFS_WHITE 0  // UNVISITED
#define DFS_BLACK 1  // EXPLORED
#define DFS_GRAY 2   // VISITED BUT NOT EXPLORED

using namespace std;

const int N = 100001;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

bool cycle = false;
int dfs_num[N];
vi topo_list, adj[N];

void dfs_topo(int u) {
    dfs_num[u] = DFS_GRAY;
    for (int j = 0; j < (int) adj[u].size(); j++) {
        int v = adj[u][j];
        if (dfs_num[v] == DFS_WHITE) dfs_topo(v);
        else if (dfs_num[v] == DFS_GRAY) cycle = true;
    }
    topo_list.push_back(u);
    dfs_num[u] = DFS_BLACK;
}

int main() {
    freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d\n", &u, &v);
        adj[u].push_back(v);
    }
    memset(dfs_num, 0, sizeof dfs_num);
    for (int i = 0; i <= n; i++)
        if (dfs_num[i] == DFS_WHITE) dfs_topo(i);
    reverse(topo_list.begin(), topo_list.end());
    for (int i = 0; i < (int) topo_list.size(); i++)
        printf("%d ", topo_list[i]);
    return 0;
}
