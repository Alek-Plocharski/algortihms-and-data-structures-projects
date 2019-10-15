#include <iostream>
#include <vector>
#include <cmath>

constexpr int MAXN = 1e6 + 1;
constexpr int MAXM = 1e6 + 1;

int tree[4 * MAXN];
char lazy[4 * MAXN]; //B - biały, C - czarny, \0 - nic

using namespace std;

void update(int curr, int curr_left, int curr_right, int update_left, int update_right, char colour) {

    if (lazy[curr] != '\0') {

        if (lazy[curr] == 'B') {
            tree[curr] = curr_right - curr_left + 1;
        }
        else if (lazy[curr] == 'C') {
            tree[curr] = 0;
        }

        if (curr_left != curr_right) {
            lazy[curr * 2] = lazy[curr];
            lazy[curr * 2 + 1] = lazy[curr];
        }

        lazy[curr] = '\0';
    }

    if (curr_left > curr_right || curr_left > update_right || curr_right < update_left)
        return;

    if (curr_left >= update_left && curr_right <= update_right) {
        // Add the difference to current node
        if (colour == 'B') {
            tree[curr] = curr_right - curr_left + 1;
        }
        else if (colour == 'C') {
            tree[curr] = 0;
        }

        if (curr_left != curr_right) {
            lazy[curr * 2] = colour;
            lazy[curr * 2 + 1] = colour;
        }
        return;
    }

    update(curr * 2, curr_left, (curr_left + curr_right) / 2, update_left, update_right, colour);
    update(curr * 2 + 1, ((curr_left + curr_right) / 2) + 1, curr_right, update_left, update_right, colour);

    tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
}

int main() {

    int n, m, left, right;
    char colour;
    cin >> n;
    cin >> m;

    for (int i = 0; i < m; i++) {

        cin >> left;
        cin >> right;
        cin >> colour;

        update(1, 1, n, left, right, colour);

        cout << tree[1] << endl;
    }

    return 0;
}