#include <bits/stdc++.h>

#define st first
#define nd second
#define sz(x) (int) x.size()
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

ll ans = 0;

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

const int maxv = 1000;
const int maxe = 50000;

struct EdmondsLawler {
  int n, E, start, finish, newRoot, qsize, adj[maxe], next[maxe], last[maxv], mat[maxv], que[maxv], dad[maxv], root[maxv];
  bool inque[maxv], inpath[maxv], inblossom[maxv];

  void init(int _n) {
    n = _n;   E = 0;
    for (int x = 1; x <= n; x++)
      last[x] = -1, mat[x] = 0;
  }

  void add(int u, int v) {
    adj[E] = v;
    next[E] = last[u];
    last[u] = E++;
  }

  int lca(int u, int v) {
    for (int x = 1; x <= n; x++)
      inpath[x] = false;
    while (true) {
      u = root[u];
      inpath[u] = true;
      if (u == start) break;
      u = dad[mat[u]];
    }

    while (true) {
      v = root[v];
      if (inpath[v]) break;
      v = dad[mat[v]];
    }

    return v;
  }

  void trace(int u) {
    while (root[u] != newRoot) {
      int v = mat[u];
      inblossom[root[u]] = true;
      inblossom[root[v]] = true;

      u = dad[v];
      if (root[u] != newRoot) dad[u] = v;
    }
  }

  void blossom(int u, int v) {
    for (int x = 1; x <= n; x++)
      inblossom[x] = false;

    newRoot = lca(u, v);
    trace(u); trace(v);

    for (int x = 1; x <= n; x++)
      if (inblossom[root[x]]) {
        root[x] = newRoot;
        if (!inque[x]) {
          inque[x] = true;
          que[qsize++] = x;
        }
      }
  }

  bool bfs() {
    for (int x = 1; x <= n; x++) {
      inque[x] = false;
      dad[x] = 0;
      root[x] = x;
    }

    qsize = 0;
    que[qsize++] = start;
    inque[start] = true;
    finish = 0;

    for (int i = 0; i < qsize; i++) {
      int u = que[i];
      for (int e = last[u]; e != -1; e = next[e]) {
        int v = adj[e];
        if (root[v] != root[u] && v != mat[u]) {
          if (v == start || (mat[v] > 0 && dad[mat[v]] > 0)) blossom(u, v);
          else if (dad[v] == 0) {
            dad[v] = u;
            if (mat[v] > 0) que[qsize++] = mat[v];
            else {
              finish = v;
              return true;
            }
          }
        }
      }
    }

    return false;
  }

  void enlarge() {
    int u = finish;
    while (u > 0) {
      int v = dad[u], x = mat[v];
      mat[v] = u;
      mat[u] = v;
      u = x;
    }
  }

  int maxmat() {
    for (int x = 1; x <= n; x++)
      if (mat[x] == 0) {
        start = x;
        if (bfs()) enlarge();
      }

    int ret = 0;
    for (int x = 1; x <= n; x++)
      if (mat[x] > x) ++ret;
    return ret;
  }

  void print() {
    int cnt = 0;
    cout << maxmat() << "\n";
    for (int x = 1; x <= n; x++)
      if (mat[x] > x) cout << ++cnt << ") " << x << " " << mat[x] << "\n";
  }

} edmonds;

int n, m;

void input() { // read data input
  cin >> n >> m;
  edmonds.init(n);
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    edmonds.add(u, v);
  }
}

void solve() { // main solution

}

void ouput() { // write data output
  edmonds.print();
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

    int temp = checker();
    if (temp == ans) cerr << "Passed";
    else
      return cerr << "Wrong, answer must be " << temp << ", not " << ans, 1;
    fprintf(stderr, " - %.4lfs.\n", (double) (t1 - t0) / 1000);
  }
  return 0;
}

