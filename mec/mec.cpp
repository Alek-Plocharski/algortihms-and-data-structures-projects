#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

vector<long long> v (0, 40010);

bool unique(vector<long long> v) {

    sort(v.begin(), v.end());

    for (int i = 1; i < v.size(); i++)
        if (v[i] == v[i - 1])
            return false;

    return true;
}

int main() {

    int n, m, tmp;

    cin >> n;
    cin >> m;

    v.resize(n);

    for (int i = 0; i < n; i++)
        v[i] = 1;

    for (int i = 0; i < m; i++) {

        for (int j = 0; j < n / 2; j++) {
            cin >> tmp;
            v[tmp - 1] *= 2;
        }

        for (int j = n / 2; j < n; j++) {
            cin >> tmp;
            v[tmp - 1] *= 2;
            v[tmp - 1]++;
        }
    }

    if (unique(v))
        cout << "TAK" << endl;

    else
        cout << "NIE" << endl;

    return 0;
}