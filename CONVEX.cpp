#include <bits/stdc++.h>

using namespace std;

struct point {
    int x, y;
    bool operator < (const point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

typedef long long ll;
typedef vector<point> vp;

int N;
vp P, result;

ll cross(const point &O, const point &A, const point &B) {
    return (A.x - O.x)*(B.y - O.y) - (A.y - O.y)*(B.x - O.x);
}

vp convex_hull(vp P) {
    int n = P.size(), k = 0;
    vp H(2*n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        point temp;
        cin >> temp.x >> temp.y;
        P.push_back(temp);
    }
    result = convex_hull(P);
    for (int i = 0; i < result.size(); i++)
        cout << result[i].x << " " << result[i].y << endl;
    return 0;
}
