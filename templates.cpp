#include <bits/stdc++.h>

#define st first
#define nd second
#define sz(x) (int) s.size()
#define all(x) x.begin(), x.end()
#define reset(a, b) memset(a, b, sizeof a)

#define rand(l, h) l + rand() % (h - l + 1)
#define what_is(x) cerr << #x" = " << x << '\n';
#define view(x) \
  for (auto i : x) cerr << i << ' ';\
  cerr << '\n';\

#define openFiles(FileName) I_File(FileName); O_File(FileName)
#define I_File(FileName) freopen((FileName + ".INP").c_str(), "r", stdin)
#define O_File(FileName) freopen((FileName + ".OUT").c_str(), "w", stdout)

using namespace std;

void init();
void input();
void solve();
void ouput();
void tester(int nT);

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector <ii> vii;
typedef long long ll;

const int upper_inf = numeric_limits<int>::max();
const int lower_inf = numeric_limits<int>::min();


/*** ---------------------------- DUY HUYNH ------------------------------***/


const string task = "DBG";
const int N = 1e6;
const int M = 1e9 + 7;

auto ans = 0;

int main() { // main program here
  init();
  input();
  solve();
  ouput();

  return tester(0), 0;
}

void init() { // initialize something
  #ifndef ONLINE_JUDGE
    openFiles(task);
  #endif // ONLINE_JUDGE
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);  cout.tie(NULL);
}

void input() { // read data input

}

void solve() { // main solution

}

void ouput() { // write data output

}

void gen() { // random test case
  srand(time(NULL));
}

int checker() { // checker
  return 0;
}

void tester(int nT) { // test nT random case
  for (int iT = 1; iT <= nT; iT++) {
    cerr << "Test " << iT << ": ";
    gen();
    init();
    input();
    solve();

    int temp = checker();
    if (temp == ans) cerr << "Accepted";
    else cerr << "Wrong, answer must be " << temp << ", not " << ans;
    cerr << ".\n";
  }
}

