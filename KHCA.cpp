#include <cstdio>
#include <iostream>
#include <vector>
 
using namespace std;
 
const int max_size = 10001;
 
int N, M, Time;
int dfs_low[max_size], dfs_num[max_size];
 
int ArticulationPoint[max_size], nBridge;
 
vector <int> adj[max_size];
 
void dfs(int u, int p) {
        int nChild = 0;
        dfs_num[u] = dfs_low[u] = ++Time;
 
        for (int j = 0; j < adj[u].size(); j++) {
                int v = adj[u][j];
                if (v != p) {
                        if (dfs_num[v]) dfs_low[u] = min(dfs_num[v], dfs_low[u]);
                        else {
                                dfs(v, u);
                                nChild++;
                                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
                                if (dfs_low[v] >= dfs_num[v]) nBridge++;
                                if (u == p) {
                                        if (nChild > 1) ArticulationPoint[u] = 1;
                                } else if (dfs_low[v] >= dfs_num[u]) ArticulationPoint[u] = 1;
                        }
                }
        }
}
 
int main() {
        #ifndef ONLINE_JUDGE
                freopen("debug.txt", "r", stdin);
        #endif
 
        cin >> N >> M;
        for (int i = 1; i <= M; i++) {
                int x, y;
                cin >> x >> y;
				adj[x].push_back(y);
                adj[y].push_back(x);
        }
 
        for (int i = 1; i <= N; i++)
                if (!dfs_num[i]) dfs(i, i);
 
        int ans = 0;
        for (int i = 1; i <= N; i++)
                if (ArticulationPoint[i]) ans++;
 
        cout << ans << " " << nBridge << endl;
}