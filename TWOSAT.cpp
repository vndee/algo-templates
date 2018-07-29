//LA 3211 2-sat
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int MAX_V = 5000;

int V;                                                    
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];

int t[8000];

void add_edge(int from, int to){
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(int v){
    used[v] = true;
    for (int i = 0; i < G[v].size(); i ++){
        if (!used[G[v][i]]) dfs(G[v][i]);
        }
    vs.push_back(v);
}

void rdfs(int v, int k){
    used[v] = true;
    cmp[v] = k;
    for (int i = 0; i < rG[v].size(); i ++){
        if (!used[rG[v][i]]) rdfs(rG[v][i], k);
        }
}

int scc(){
    vs.clear();
    for (int v = 0; v < 2 * V; v ++){
        if (!used[v]) dfs(v);
        }
    memset(used, 0, sizeof(used));
    int k = 0;
    for (int i = vs.size() - 1; i >= 0; i --){
        if (!used[vs[i]]) rdfs(vs[i], k ++);
        }
    return k;
}

int rev(int c){
    if (c < V) return c + V;
        else   return c - V;
}

bool test(int diff){
    for (int i = 0; i < 2 * V; i ++){
        G[i].clear();
        rG[i].clear();
        }
    for (int i = 0; i < 2 * V; i ++)
        for (int j = i + 1; j < 2 * V; j ++)
            if (abs(t[i] - t[j]) < diff) {
                                add_edge(i, rev(j));
                                add_edge(j, rev(i));
                                }
    scc();
    for (int i = 0; i < V; i ++){
        if (cmp[i] == cmp[i + V]) return false;
        }
    return true;
}

int main(){
    while (scanf("%d", &V) != EOF){
        int L = 0, R = 0;
        for (int i = 0; i < V; i ++){
            scanf("%d%d", &t[i], &t[i + V]);
            R = max(R, t[i]);
            R = max(R, t[i + V]);
            }

        while (L < R){
            int M = L + (R - L + 1) / 2;
            if (test(M)) L = M;
                    else R = M - 1;
            }
        printf("%d\n", L);
        }

    return 0;
}
