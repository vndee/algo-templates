// Tue 14 Jun, 2016 14:53
// Convex Hull [Graham - Andrew method, O(N log N)
#include <bits/stdc++.h>

#define sqr(x) ((x) * (x))

using namespace std;

const double pi = acos(-1.0);

struct point {
    double x, y;
};
int n;
vector <point> p, hull;
double ans;

bool cmp(point a, point b) {
    return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

bool eq(point a, point b) {
    return (a.x == b.x && a.y == b.y);
}

bool isCCW(point a, point b, point c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

void ConvexHull(vector <point> p, vector <point> &h) {
    sort(p.begin(), p.end(), cmp);
    p.erase(unique(p.begin(), p.end(), eq), p.end());

    vector <point> up, down;
    point head = p[0], tail = p.back();
    up.push_back(head);     down.push_back(head);

    for (int i = 1; i < (int) p.size(); i++) {
        if (i == (int) p.size() - 1 || !isCCW(tail, head, p[i])) {
            while ((int) up.size() >= 2 && isCCW(up[up.size()-2], up.back(), p[i]))
                up.pop_back();
            up.push_back(p[i]);
        }
        if (i == (int) p.size() - 1 || isCCW(tail, head, p[i])) {
            while ((int) down.size() >= 2 && !isCCW(down[down.size()-2], down.back(), p[i]))
                down.pop_back();
            down.push_back(p[i]);
        }
    }

    h.clear();
    for (int i = 0; i < (int) up.size(); i++) h.push_back(up[i]);
    for (int i = (int) down.size() - 2; i > 0; i--) h.push_back(down[i]);
}

double dist(point a, point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double Perimeter(vector <point> p) {
    double per = 0;
    for (int i = 1; i < (int) p.size(); i++)
        per += dist(p[i-1], p[i]);
    per += dist(p.back(), p[0]);
    return per;
}

double Area(vector <point> p) {
    double are = 0;
    for (int i = 1; i < (int) p.size(); i++)
        are += (p[i-1].x*p[i].y - p[i].x*p[i-1].y);
    return fabs(1.0 * are / 2);
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdin);

    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) {
        point temp;
        scanf("%lf %lf\n", &temp.x, &temp.y);
        p.push_back(temp);
    }

    ConvexHull(p, hull);
    for (int i = 0; i < (int) hull.size(); i++)
        printf("%lf %lf\n", hull[i].x, hull[i].y);
    printf("per = %.2lf\nare = %.2lf", Perimeter(hull), Area(hull));
    return 0;
}

