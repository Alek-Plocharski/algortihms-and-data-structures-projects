#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAXN = 2e5 + 10;

struct Project {

    uint64_t start;
    uint64_t end;
    uint64_t value;
    int first_after;
};

struct CmpFirst {
    bool operator()(const Project &a, const Project &b) {
        return (a.start == b.start ? a.end < b.end : a.start < b.start);
    }
};

struct {
    bool operator()(const Project a, const Project b) {
        return a.end < b.end;
    }
} customSecond;

vector<uint64_t> dp(MAXN);
vector<Project> projects(MAXN);

int bs(int l, int p, uint64_t after) {

    int s;

    while (l < p) {
        s = (l + p) / 2;

        if (projects[s].start <= after) {
            l = s + 1;
        }
        else {
            p = s;
        }
    }

    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    projects.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> projects[i].start;
        cin >> projects[i].end;
        cin >> projects[i].value;
        //dp[i] = projects[i].value; //TODO potrzebne?
    }
    projects[n].start = 1000000009;
    projects[n].end = 1000000009;
    projects[n].value = 0;
    dp[n] = 0;

    sort(projects.begin(), projects.end(), CmpFirst());

    for (int i = 0; i < n; i++) {
        projects[i].first_after = bs(0, n, projects[i].end);
        //cout << projects[i].start << " " << projects[i].end << " " << projects[i].value << " " << projects[i].first_after << " " << dp[i] << endl;
    }

    for (int i = n - 1; i >= 0; i--) {

        if (projects[i].end < projects[i + 1].start) { // nie ma kolizji
            dp[i] = dp[i + 1] + projects[i].value;
        }
        else { // jest kolizja
            if (projects[i].value + dp[projects[i].first_after] > dp[i + 1]) {
                dp[i] = projects[i].value + dp[projects[i].first_after];
            }
            else {
                dp[i] = dp[i + 1];
            }
        }
    }
//    for (int i = 0; i < n; i++) {
//        cout << projects[i].start << " " << projects[i].end << " " << projects[i].value << " " << projects[i].first_after << " " << dp[i] << endl;
//    }

    cout << dp[0] << endl;

    return 0;
}