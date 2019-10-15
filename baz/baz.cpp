#include <iostream>

using namespace std;

constexpr int MAXN = 1000000;

typedef long long ll;

ll table[MAXN];
int a[MAXN];

int main() {

    int n, m;

    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> a[i];

    int smallestUsedEven = -1;
    int smallestUsedOdd = -1;
    int nextUnusedEvenIndex = -2;
    int nextUnusedOddIndex = -2;
    ll sum = 0;

    for (int i = n - 1; i >= 0; i--) {

        sum += a[i];

        if (a[i] % 2 == 0) {

            if (smallestUsedEven == -1)
                smallestUsedEven = a[i];

            else if (a[i] < smallestUsedEven)
                smallestUsedEven = a[i];
        }

        else {
            
            if (smallestUsedOdd == -1)
                smallestUsedOdd = a[i];

            else if (a[i] < smallestUsedOdd)
                smallestUsedOdd = a[i];
        }

        if (nextUnusedEvenIndex >= i || nextUnusedEvenIndex == -2) {
            nextUnusedEvenIndex = -1;
            for (int j = i - 1; j >= 0; j--)
                if (a[j] % 2 == 0) {
                    nextUnusedEvenIndex = j;
                    break;
                }
        }

        if (nextUnusedOddIndex >= i || nextUnusedOddIndex == -2) {
            nextUnusedOddIndex = -1;
            for (int j = i - 1; j >= 0; j--)
                if (a[j] % 2 == 1) {
                    nextUnusedOddIndex = j;
                    break;
                }
        }

        if (sum % 2 == 1) { //suma jest nieparzysta i możemy ją zpisać
            table[n - i - 1] = sum;
        }

        else { //suma jest parzysta i musimy spróbować zmienić parzystość

            table[n - i - 1] = sum;

            if (nextUnusedOddIndex >= 0 && smallestUsedEven >= 0 && nextUnusedEvenIndex >= 0 && smallestUsedOdd >= 0) {
                int x = a[nextUnusedOddIndex] - smallestUsedEven;
                int y  = a[nextUnusedEvenIndex] - smallestUsedOdd;
                table[n - i - 1] += ((x > y) ? x : y);
            }

            else if (nextUnusedOddIndex >= 0 && smallestUsedEven >= 0) {
                table[n - i - 1] += (a[nextUnusedOddIndex] - smallestUsedEven);
            }

            else if (nextUnusedEvenIndex >= 0 && smallestUsedOdd >= 0) {
                table[n - i - 1] += (a[nextUnusedEvenIndex] - smallestUsedOdd);
            }

            else {
                table[n - i - 1] = -1;
            }
        }
    }

    cin >> m;
    int numberOfItems;
    for (int i = 0; i < m; i++) {
        cin >> numberOfItems;
        cout << table[numberOfItems - 1] << endl;
    }

    return 0;
}