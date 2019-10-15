#include <iostream>

using namespace std;

constexpr int MAXN = 1000;
constexpr int MODULO = 1000000000;
constexpr bool LEFT = false;
constexpr bool RIGHT = true;

int last_right[MAXN][MAXN];
int last_left[MAXN][MAXN];
int a[MAXN];
int n;

long long ile_rec(int l, int p, bool side) {

    if (l == 0 && p == n - 1)
        return 1;

    if (side == RIGHT && last_right[l][p] != -1)
        return last_right[l][p];

    if (side == LEFT && last_left[l][p] != -1)
        return last_left[l][p];

    long long sol = 0;

    if (l > 0 && ((side == RIGHT && a[l - 1] < a[p]) || (side == LEFT && a[l - 1] < a[l])))
        sol += ile_rec(l-1, p, LEFT);

    if (p < n - 1 && ((side == RIGHT && a[p + 1] > a[p]) || (side == LEFT && a[p + 1] > a[l])))
        sol += ile_rec(l, p + 1, RIGHT);

    sol %= MODULO;

    if (side == RIGHT)
        last_right[l][p] = sol;

    else
        last_left[l][p] = sol;

    return sol;
}

long long ile() {

    long long sol = 0;

    for (int i = 0; i < n; i++)
        sol += ile_rec(i, i, LEFT);

    sol %= MODULO;

    return sol;
}

int main() {

    cin >>n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            last_right[i][j] = -1;
            last_left[i][j] = -1;
        }


    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << ile() << endl;

    return 0;
}