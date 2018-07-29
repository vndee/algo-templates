#include <bits/stdc++.h>
 
#define X(x) x + 0
#define Y(y) y + n
 
#define DEBUG
 
using namespace std;
 
const int N = 301;
const int inf = 0x3f3f3f3f;
 
int n, m, cnt;
int source, sink;
int c[N][N], f[N][N];
int x[N], y[N], vis[N], level[N];
 
vector <int> adj[N];
 
void AddEdge(int u, int v, int cap) {
  adj[u].push_back(v);
  adj[v].push_back(u);
  c[u][v] = c[v][u] = cap;
}
 
void Make_graph(int source, int sink) {
  for (int i = 1; i <= n; i++) AddEdge(source, X(i), 1);
  for (int i = 1; i <= m; i++) AddEdge(sink, Y(i), 1);
}
 
bool bfs(int source, int sink) {
  memset(level, 0, sizeof level);
  queue <int> q;  q.push(source);
  level[source] = 1;
 
  while (!q.empty()) {
    int u = q.front();  q.pop();
    if (u == sink) return true;
 
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      if (!level[v] && f[u][v] < c[u][v]) {
        level[v] = level[u] + 1;
        q.push(v);
      }
    }
  }
 
  return 0;
}
 
int dfs(int u, int sink, int delta) {
  if (u == sink) return delta;
  if (vis[u] != cnt) vis[u] = cnt;
  else return 0;
 
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (f[u][v] < c[u][v])
      if (!vis[v] != cnt && level[v] == level[u] + 1)
        if (int x = dfs(v, sink, min(delta, c[u][v] - f[u][v]))) {
          f[u][v] += x, f[v][u] -= x;
          return x;
        }
  }
 
  return 0;
}
 
int Dinitz(int source, int sink) {
  int flow = 0;
  while (bfs(source, sink))
    if (int x = (cnt++, dfs(source, sink, inf))) flow += x;
  return flow;
}
 
void Print(int source, int sink) {
  cout << Dinitz(source, sink) << endl;
  for (int i = 1; i <= n; i++)
    for (int j = n; j <= n + m; j++) {
      if (f[i][j] == 1) cout << i << " " << j - n  << endl;
    }
}
 
#ifdef DEBUG
  vector <int> a[N];
  int t, visited[N], assigned[N];
 
  bool visit(int u) {
    if (visited[u] != t) visited[u] = t;
    else return false;
 
    for (int i = 0; i < a[u].size(); i++) {
      int v = a[u][i];
      if (!assigned[v] || visit(assigned[v])) {
        assigned[v] = u;
        return true;
      }
    }
 
    return false;
  }
 
  int Run() {
    int Count = 0;
    for (int i = 1; i <= n; i++) {
      t++;
      Count += visit(i);
    }
 
    cout << Count << endl;
    for (int i = 1; i <= m; i++)
      if (int j = assigned[i]) cout << j << " " << i << endl;
  }
#endif // DEBUG
 
int main() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif // ONLINE_JUDGE
 
  cin >> n >> m;
  int x, y;
  while ((cin >> x >> y) > 0) {
    //AddEdge(X(x), Y(y), 1);
    #ifdef DEBUG
      a[x].push_back(y);
    #endif // DEBUG
  }
 
  //source = 0, sink = n + m + 1;
  //Make_graph(source, sink);
 
  //Print(source, sink);
  #ifdef DEBUG
    Run();
  #endif // DEBUG
 
  return 0;
}