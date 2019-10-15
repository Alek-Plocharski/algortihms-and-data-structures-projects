#include <iostream>
#include <vector>

using namespace std;

constexpr long long MOD = 1000000000;

struct Tree {
    long long size;
    vector<long long> t;

    Tree(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        t.resize(2 * size);
        for (int i = 0; i < 2 * size; i++)
            t[i] = 0;
    }

    //we are adding y to x
    void update(long long x, long long y) {
        x += size - 1; //x-ty liść
        while(x > 0) {
            t[x] += y;//zwiększamy wartść
            t[x] %= MOD;
            x /= 2; //wchodzimy poziom wyrzej
        }
    }

    long long sum(int left, int right) {
        left += size - 1;
        right += size - 1;
        long long result = 0;
        while (left < right) {
            if (left & 1) {
                result += t[left++];
                result %= MOD;
            }
            if (!(right & 1)) {
                result += t[right--];
                result %= MOD;
            }
            left /= 2;
            right /= 2;
        }
        if (left == right)
            result += t[left];
        result %= MOD;
        return result;
    }
};

int main() {

    long long n, k, a;
    cin >> n;
    cin >> k;

    vector<Tree> trees;

    for (int i = 0; i < k; i++)
        trees.push_back(Tree(n));

    for (int i = 0; i < n; i++) {
        cin >> a;
        for (int j = 0; j < k; j++) {
            if (j == 0) {
                trees[j].update(a, 1);
            }
            else {
                trees[j].update(a, trees[j - 1].sum(a + 1, n));
            }
        }
    }

    cout << trees[k - 1].t[1] << endl;

    return 0;
}