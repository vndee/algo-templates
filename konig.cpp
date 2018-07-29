// minimum vertex cover
#include <bits/stdc++.h>

#define NIL 0

using namespace std;

const int N = 500001;
const int inf = numeric_limits<int>::max();

int n, m, p;
int match[N], d[N];
bool choosed[N];

vector <int> adj[N];

bool bfs() {
  queue <int> Q;
  for (int i = 1; i <= n; i++)
    if (match[i] == NIL) {
      d[i] = 0;
      Q.push(i);
    } else d[i] = inf;

  d[NIL] = inf;
  while (!Q.empty()) {
    int u = Q.front();  Q.pop();
    if (u == NIL) continue;

    for (auto v : adj[u])
      if (d[match[v]] == inf) {
        d[match[v]] = d[u] + 1;
        Q.push(match[v]);
      }
  }

  return d[NIL] != inf;
}

bool dfs(int u) {
  if (u == NIL) return true;

  for (auto v : adj[u])
    if (d[match[v]] == d[u] + 1)
      if (dfs(match[v])) {
        match[u] = v;
        match[v] = u;
        return true;
      }

  d[u] = inf;
  return false;
}

int hopcroft_karp() {
  int matching = 0;
  while (bfs())
    for (int i = 1; i <= n; i++)
      if (match[i] == NIL && dfs(i))
        matching++;
  return matching;
}

void konig() {
  queue <int> Q;
  for (int i = 1; i <= m + n; i++)
    if (!match[i]) Q.push(i);

  while (!Q.empty()) {
    int u = Q.front();  Q.pop();
    for (auto v : adj[u])
      if (!(choosed[v]++)) Q.push(match[v]);
  }

  for (int i = 1; i <= n; i++)
    if (match[i] && !choosed[i] && !choosed[match[i]])
      choosed[i] = true;

}

int main() {
  freopen("DBG.INP", "r", stdin);
  freopen("DBG.OUT", "w", stdout);

  cin >> n >> m >> p;
  for (int i = 1, u, v; i <= p; i++) {
    cin >> u >> v;
    v += n;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  cout << hopcroft_karp() << "\n";
  for (int i = 1; i <= n; i++)
    if (match[i]) cout << i << " " << match[i] - n << "\n";

  konig();

  for (int i = 1; i <= n + m; i++)
    if (choosed[i]) cout << (i > n ? i - n : i)  << " ";
}
