#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

constexpr int MAXN = (int)(1e5) + 1;
constexpr int MAXS = 18;
constexpr long long INF = LLONG_MAX;

int n, K, U;
long long remembered[MAXN][MAXS];
char path[MAXN];

long long fill_dp_table(long long curr_position, long long S) {

    if (curr_position == n) {
        remembered[curr_position][S] = 0;
        return 0;
    }

    if (curr_position > n)
        return INF;

    if (path[curr_position] == '*' && S < 17)
        S++;

    if (remembered[curr_position][S] != -1 && remembered[curr_position][S] != -2)
        return remembered[curr_position][S];

    switch (path[curr_position]) {

        case '.':
        case '*': {
            long long x = fill_dp_table(curr_position + (long long) pow(2, S), S);
            long long y = fill_dp_table(curr_position + 1, S);

            if (x == INF && y == INF)
                remembered[curr_position][S] = INF;
            else
                remembered[curr_position][S] = min(x, y) + 1;
            return remembered[curr_position][S];
        }
        case '>': {
            if (remembered[curr_position][S] == -2)
                return INF;

            remembered[curr_position][S] = -2;
            remembered[curr_position][S] = fill_dp_table(curr_position + K, S);

            return remembered[curr_position][S];
        }
        case '<': {
            if (remembered[curr_position][S] == -2)
                return INF;

            remembered[curr_position][S] = -2;
            remembered[curr_position][S] = fill_dp_table(curr_position - K, S);
            return remembered[curr_position][S];
        }
        case 'U': {
            long long x = fill_dp_table(curr_position + (long long) pow(2, S), S);
            long long y = fill_dp_table(curr_position + 1, S);

            if (x == INF && y == INF)
                remembered[curr_position][S] = INF;
            else
                remembered[curr_position][S] = min(x, y) + U + 1;

            return remembered[curr_position][S];
        }
        case '#': {
            return INF;
        }
    }
}

int main() {

    cin >> n;
    cin >> K;
    cin >> U;

    string a;
    cin >> a;

    for (int i = 1; i <= n; i++) {
        path[i] = a[i - 1];
        for (int j = 1; j <= 17; j++)
            remembered[i][j] = -1;
    }

    fill_dp_table(1, 1);

    cout << (remembered[1][1] == INF ? -1 : remembered[1][1]) << endl;
}