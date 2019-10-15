#include <iostream>
#include <queue>
#include <list>
#include <vector>

constexpr int MAXN = 1e5 + 50;

using namespace std;

vector<list<int>> graph(MAXN);
vector<int> in_degree(MAXN);
vector<long long> number_of_employees(MAXN);

struct My_cmp {
    bool operator()(int a, int b) {
        return number_of_employees[a] > number_of_employees[b];
    }
};

int main() {

    ios::sync_with_stdio(false);

    int n, m, k, a, b;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        cin >> number_of_employees[i];
    }

    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        graph[b].push_back(a);
        in_degree[a]++;
    }

    priority_queue<int, vector<int>, My_cmp> q;

    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0)
            q.push(i);
    }

    int result;
    int i = 0;

    while (!q.empty()) {
        int v = q.top();
        q.pop();
        i++;
        if (i == k) {
            result = number_of_employees[v];
            break;
        }

        for (int next : graph[v]) {
            in_degree[next]--;
            if (number_of_employees[next] < number_of_employees[v])
                number_of_employees[next] = number_of_employees[v];
            if (in_degree[next] == 0)
                q.push(next);
        }
    }

    cout << result << endl;

    return 0;
}