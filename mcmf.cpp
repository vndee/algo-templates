#include <bits/stdc++.h>

#define F_INF 1000111000LL
#define C_INF 1000111000LL
#define ll long long
#define Flow long long
#define Cost long long

using namespace std;

const int MAXE = 10000;
const int MAXV = 500;

typedef long long F;
typedef long long C;

int V,E;
F cap[MAXE];
C cost[MAXE],dist[MAXV],pot[MAXV];
int to[MAXE],previous[MAXE],last[MAXV],path[MAXV];
bool used[MAXV];
priority_queue <pair <C, int> > q;

class MinCostFlow{
public:
  MinCostFlow(int n){
    V = n; E = 0;
    for (int i = 0; i < V; i++) last[i] = -1;
  }

  void add_edge(int x, int y, F w, C c){
    cap[E] = w; cost[E] = c; to[E] = y; previous[E] = last[x]; last[x] = E; E++;
    cap[E] = 0; cost[E] = -c; to[E] = x; previous[E] = last[y]; last[y] = E; E++;
  }

  pair <F, C> search(int s, int t){
    F ansf = 0; C ansc = 0;
    for (int i = 0; i < V; i++)
      used[i] = false, dist[i] = C_INF;

    dist[s] = 0; path[s] = -1; q.push(make_pair(0,s));
    while (!q.empty()){
      int x = q.top().second; q.pop();
      if (used[x]) continue; used[x] = true;
      for (int e = last[x]; e >= 0; e = previous[e])
        if (cap[e] > 0) {
          C tmp = dist[x] + cost[e] + pot[x] - pot[to[e]];
          if (tmp < dist[to[e]] && !used[to[e]]){
            dist[to[e]] = tmp;
            path[to[e]] = e;
            q.push(make_pair(-dist[to[e]],to[e]));
          }
        }
      }

    for (int i = 0; i < V; i++) pot[i] += dist[i];

    if (used[t]){
      ansf = F_INF;
      for(int e=path[t];e>=0;e=path[to[e^1]]) ansf = min(ansf,cap[e]);
      for(int e=path[t];e>=0;e=path[to[e^1]]) {ansc += cost[e] * ansf; cap[e] -= ansf; cap[e^1] += ansf;}
    }

    return make_pair(ansf,ansc);
  }

  pair <F, C> mincostflow(int s, int t){
    F ansf=0; C ansc=0;
    while(1){
      pair <F, C> p = search(s,t);
      if(!used[t]) break;
      ansf += p.first; ansc += p.second;
    }
    return make_pair(ansf,ansc);
  }
};

int n, m, s, t;

int main() {
  cin >> n >> m >> s >> t;
  MinCostFlow mcf(2*n);
  for (int i = 0; i < m; i++) {
    int u, v, c, w;
    cin >> u >> v >> c >> w;
    mcf.add_edge(u, v, c, w);
  }

  pair <F, C> ans = mcf.mincostflow(s, t);
  cout << ans.first << " " << ans.second;
}
