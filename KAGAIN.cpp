#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stack>

using namespace std;

const int maxN = 30001;

int N, A[maxN], L[maxN], R[maxN];

int main() {
    #ifndef ONLINE_JUDGE
        freopen("kagain.inp", "r", stdin);
        freopen("kagain.out", "w", stdout);
    #endif // ONLINE_JUDGE

    int Case;
    cin >> Case;
    while (Case--) {
        memset(A, 0, sizeof (A));
        cin >> N;
        for (int i = 1; i <= N; i++) cin >> A[i];

        stack < pair<int,int> > st;
        st.push(make_pair(0, 0));
        for (int i = 1; i <= N; i++) {
            if (A[i] > st.top().first) L[i] = st.top().second + 1, st.push(make_pair(A[i], i));
            else {
                while (!st.empty() && st.top().first >= A[i]) st.pop();
                L[i] = st.top().second + 1; st.push(make_pair(A[i], i));
            }
        }

        while (!st.empty()) st.pop();
        st.push(make_pair(0, N+1));
        for (int i = N; i; i--) {
            if (A[i] > st.top().first) R[i] = st.top().second - 1, st.push(make_pair(A[i], i));
            else {
                while (!st.empty() && st.top().first >= A[i]) st.pop();
                R[i] = st.top().second - 1; st.push(make_pair(A[i], i));
            }
        }

        pair <int, pair < int, int> > ans;
        for (int i = 1; i <= N; i++)
            if (ans.first < A[i]*(R[i] - L[i] + 1))
                ans.first = A[i]*(R[i] - L[i] + 1),
                ans.second.first = L[i],
                ans.second.second = R[i];

        cout << ans.first << " " << ans.second.first << " " << ans.second.second << endl;
    }

    return 0;
}
