#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;

constexpr ll MAXN = 3e5;
constexpr ll MAXM = 3e5;
constexpr ll PRIME = 1e9 + 7;
constexpr ll BASE = 654321;

string word;
vector<ll> prefixHashes(MAXN);
ll basePowers[MAXN];
ll n, m;

ll moduloAddition(ll a, ll b) {
    return ((a )) + (b) % PRIME;
}

ll moduloMultiplication(ll a, ll b) {
    return ((a )) * (b) % PRIME;
}

void calculatePrefixHashes() {

    prefixHashes[0] = word[0];

    for (int i = 1; i < n; i++) {
        prefixHashes[i] = moduloAddition(moduloMultiplication(prefixHashes[i - 1], BASE), word[i]);
    }
}

ll getHash(int a, int b) {

    ll result = prefixHashes[b];
    ll tmp = (a - 1 < 0) ? 0 : prefixHashes[a - 1];

    ll power = b - a + 1;
//    for (int i = 0; i < power; i++)
//        tmp = moduloMultiplication(tmp, BASE);

    tmp = moduloMultiplication(tmp, basePowers[power]);

    result = moduloAddition(result, -1 * tmp);

    return (result > 0 ? result : PRIME + result);
}

ll findFirstDiffernet(int a, int b, int c, int d) {

    if (getHash(a, b) == getHash(c, d))
        return 0;

    int l = 0;
    int p = min(b - a, d - c);

    if (getHash(l + a, p + a) == getHash(l + c, p + c))
        return ((b - a) > (d - c) ? 1 : -1);

    while (l < p) {

        int s = (l + p) / 2;

        if (getHash(l + a, s + a) == getHash(l + c, s + c)) {
            l = s + 1;
        }
        else {
            p = s;
        }
    }

    if (word[l + a] < word[l + c])
        return -1;

    return 1;
}

int main() {

    int a, b, c, d;

    cin >> n >> m >> word;

    //basePowers.resize(n);

    basePowers[0] = 1;
    for (int i = 1; i < n; i ++) {
        basePowers[i] = moduloMultiplication(basePowers[i - 1], BASE);
    }

    calculatePrefixHashes();

//    for (int i = 0; i < n; i++)
//        cout << prefixHashes[i] << endl;

    for (int i = 0; i < m; i++) {

        cin >> a >> b >> c >> d;

        //cout << getHash(a-1,b-1) << "    " << getHash(c-1,d-1) << endl;

        switch (findFirstDiffernet(a -1, b - 1, c - 1, d - 1)) {
            case 0:
                cout << "=" << endl;
                break;
            case -1:
                cout << "<" << endl;
                break;
            case 1:
                cout << ">" << endl;
                break;
        }
    }

    return 0;
}