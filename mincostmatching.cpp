#include <bits/stdc++.h>

#define st first
#define nd second
#define sz(x) (int) s.size()
#define all(x) x.begin(), x.end()
#define memset(a, b) memset(a, b, sizeof a)

#define Exit(x) { cout << x; exit(0); }
#define rand(l, h) l + rand() % (h - l + 1)
#define what_is(x) cerr << #x" = " << x << '\n';
#define view(x) \
  cerr << #x" = ";\
  for (auto i : x) cerr << i << ' ';\
  cerr << '\n';\

#define openFiles(FileName) I_File(FileName); O_File(FileName)
#define I_File(FileName) freopen((FileName + ".INP").c_str(), "r", stdin)
#define O_File(FileName) freopen((FileName + ".OUT").c_str(), "w", stdout)

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector <ii> vii;
typedef long long ll;

const int upper_inf = numeric_limits<int>::max();
const int lower_inf = numeric_limits<int>::min();

/*** ---------------------------- DUY HUYNH ------------------------------***/


const string task = "DBG";
const int N = 1e6 + 9;
const int M = 1e9 + 7;

void init();
void reset();
void input();
void solve();
void ouput();
int tester(int nT);

int main() { // main program here
#ifndef DEBUG
  init();
  reset();
  input();
  solve();
  ouput();

  return 0;
#elif DEBUG
  return tester(10);
#endif // DEBUG
}

void init() { // initialize something
  #ifndef ONLINE_JUDGE
    openFiles(task);
  #endif // ONLINE_JUDGE
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);  cout.tie(NULL);
}

void reset() { // reset something

}

#define F_INF 1000111000LL
#define C_INF 1000111000LL

const int MAXE = 100000;
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
    for (int i = 0; i < V; i++)
      last[i] = -1;
    memset(cap, 0);
    memset(cost, 0);
    memset(dist, 0);
    memset(pot, 0);
    memset(to, 0);
    memset(previous, 0);
    memset(path, 0);
    memset(used, false);
    while (!q.empty()) q.pop();
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

void input() { // read data input

}

int n;

void solve() { // main solution
  n;  cin >> n;
  int s = 0, t = 2*n + 1;

  MinCostFlow mcf(2*n + 2);
  for (int i = 1; i <= n; i++) {
    mcf.add_edge(s, i, 1, 0);
    mcf.add_edge(n + i, t, 1, 0);
  }

  int u, v, c;
  while (cin >> u >> v >> c) {
    mcf.add_edge(u, v + n, 1, c);
  }

  cout << mcf.mincostflow(s, t).second << endl;
}

void ouput() { // write data output
  for (int i = 1; i <= n; i++) {
    for (int e = last[i]; e >= 0; e = previous[e]) {
      if (cap[e] == 0) cout << i << " " << to[e] - n << endl;
    }
  }
}

void gen() { // generate random test case
  srand(time(NULL));
  ofstream fi((task + ".INP").c_str());

  fi.close();
}

int checker() { // checker
  return 0;
}

int tester(int nT) { // excute nT random test case
  for (int iT = 1; iT <= nT; iT++) {
    cerr << "Test " << iT << ": ";
    gen();
    clock_t t0 = clock();
    init();
    reset();
    input();
    solve();
    clock_t t1 = clock();

    int ans;
    int temp = checker();
    if (temp == ans) cerr << "Passed";
    else
      return cerr << "Wrong, answer must be " << temp << ", not " << ans, 1;
    fprintf(stderr, " - %.4lfs.\n", (double) (t1 - t0) / 1000);
  }
  return 0;
}

