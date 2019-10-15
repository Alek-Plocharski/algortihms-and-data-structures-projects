#include <iostream>

using namespace std;

int main() {

    int n;
    string s;

    cin >> s;
    n = (int)s.size();

    char lastLetter;
    bool oneOrNoLetters = true;
    int i = 0;

    while (i < n - 1 && s[i] == '*')
        i++;

    if (i == n || i == n - 1) {
        cout << "1" << endl;
    }

    else {

        lastLetter = s[i];
        i++;
        size_t minimalDistance = 1000000000000000;
        size_t distance = 0;

        while (i < n) {

            while (i < n && s[i] == '*') {
                distance++;
                i++;
            }

            if (i != n) {

                if (lastLetter != s[i]) {
                    oneOrNoLetters = false;
                    if (minimalDistance > distance)
                        minimalDistance = distance;
                }

                lastLetter = s[i];
                distance = 0;
                i++;
            }
        }

        if (oneOrNoLetters)
            cout << 1 << endl;

        else
        cout << n - minimalDistance << endl;
    }

    return 0;
}