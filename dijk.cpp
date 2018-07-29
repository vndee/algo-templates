#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>

#define maxN 1000001
#define maxC 9223372036854775807

using namespace std;

long long D[maxN];
int N, M;
vector < pair<int, long long> > A[maxN];

struct comp {
    bool operator() (pair<int, long long> p, pair<int, long long> q) {
        return p.second > q.second;
    }
};

void Enter() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j < M; j++) {
            long long k;
            int u = M * (i-1) + j, v = M * (i-1) + j + 1;
            cin >> k;
            A[u].push_back(make_pair(v, k));
            A[v].push_back(make_pair(u, k));
        }
    for (int i = 1; i < N; i++)
        for (int j = 1; j <= M; j++) {
            long long k;
            int u = M * (i-1) + j, v = M * i + j;
            cin >> k;
            A[u].push_back(make_pair(v, k));
            A[v].push_back(make_pair(u, k));
        }
}

void Dijkstra_Heap(int x, int y) {
    priority_queue < pair<int, long long>, vector < pair<int, long long> >, comp > Heap;
    for (int i = 1; i <= y; i++) D[i] = maxC;
    Heap.push(make_pair(x, 0));
    D[x] = 0;
    while (!Heap.empty()) {
        int u = Heap.top().first;
        long long w = Heap.top().second;
        Heap.pop();
        if (w > D[u]) continue;
        if (u == y) break;
        for (int i = 0; i < A[u].size(); i++) {
            int v = A[u][i].first;
            if (D[v] > w + A[u][i].second) D[v] = w + A[u][i].second, Heap.push(make_pair(v, D[v]));
        }
    }
    cout << D[y] << endl;
}

void Debug() {
    ///*** for debug purposes
    for (int i = 1; i <= N * (N-1) + M; i++) {
        cout << i << ": ";
        for (int j = 0; j < A[i].size(); j++) cout << "(" << A[i][j].first << ", " << A[i][j].second << ")";
        cout << endl;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("MARIO.INP", "r", stdin);
        freopen("MARIO.OUT", "w", stdout);
    #endif // ONLINE_JUDGE
    Enter();
    Dijkstra_Heap(1, M * (N-1) + M);
    return 0;
}