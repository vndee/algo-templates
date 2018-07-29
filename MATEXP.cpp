#include <bits/stdc++.h>

using namespace std;

long long N, M;

class Matrix {
public:
    long long Val[4][4];

public:
    Matrix() { memset(Val, 0, sizeof Val); }

    Matrix operator * (const Matrix &x) {
        Matrix ans;

        for (int i = 1; i < 4; i++)
            for (int j = 1; j < 4; j++)
                for (int k = 1; k < 4; k++)
                    ans.Val[i][j] = (ans.Val[i][j] + (long long) Val[i][k] * x.Val[k][j]) % M;

        return ans;
    }
} A;

Matrix Pow(Matrix C, long long K) {
    Matrix C1;

    if (K == 1) return C;
    C1 = Pow(C, K/2);
    C1 = C1 * C1;

    if (K % 2) C1 = C1 * C;
    return C1;
}

int main() {
    ios_base::sync_with_stdio(0);   cin.tie(NULL);
    freopen("loco.inp", "r", stdin);
    freopen("loco.out", "w", stdout);

    cin >> N >> M;

    switch (N) {
        case 0:
            cout << 1;
            return 0;
        case 1:
            cout << 1;
            return 0;
        case 2:
            cout << 2 % M;
            return 0;
        case 3:
            cout << 4 % M;
            return 0;
        default:
            A.Val[1][1] = 0;    A.Val[1][2] = 1;    A.Val[1][3] = 0;
            A.Val[2][1] = 0;    A.Val[2][2] = 0;    A.Val[2][3] = 1;
            A.Val[3][1] = 1;    A.Val[3][2] = 1;    A.Val[3][3] = 1;

            A = Pow(A, N-1);

            cout << (A.Val[1][1] + A.Val[1][2]*2 + A.Val[1][3]*4) % M;
    }

    return 0;
}
