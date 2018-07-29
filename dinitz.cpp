
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1003;
const int inf = 0x3f3f3f3f;
 
int source, sink;
int n, m, vis[N], cnt = 0;
int d[N], f[N][N], c[N][N];
 
vector <int> adj[N];
 
bool bfs(int source, int sink) {
  memset(d, 0, sizeof d);
  queue <int> q;  q.push(source);
  d[source] = 1;
  while (!q.empty()) {
    int u = q.front();  q.pop();
    if (u == sink) return true;
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (!d[v] && f[u][v] < c[u][v]) {
        d[v] = d[u] + 1;
        q.push(v);
      }
    }
  }
  return false;
}
 
int dfs(int u, int delta) {
  if (u == sink) return delta;
  if (vis[u] != cnt) vis[u] = cnt;
  else return 0;
 
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (f[u][v] < c[u][v])
      if (vis[v] != cnt && d[v] == d[u] + 1)
        if (int x = dfs(v, min(delta, c[u][v] - f[u][v]))) {
          f[u][v] += x; f[v][u] -= x;
          return x;
      }
  }
  return 0;
}
 
int dinitz(int source, int sink) {
  int FLOW = 0;
  while (bfs(source, sink)) {
    while (int x = (cnt++, dfs(source, inf))) FLOW += x;
  }
  return FLOW;
}
 
int main() {
  /*
    Look at my code,
    It's so amazing.
   */
  //freopen("in.txt", "r", stdin);
  scanf("%d %d %d %d\n", &n, &m, &source, &sink);
  for (int i = 0; i < m; i++) {
    int u, v, k;
    scanf("%d %d %d", &u, &v, &k);
    adj[u].push_back(v);
    adj[v].push_back(u);
    c[u][v] += k;
  }
 
  printf("%d\n", dinitz(source, sink));
 
  return 0;
}