#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

constexpr int MAXN = 2e5;
constexpr ll INF = 9223372036854775807;

struct Island {

    ll number;
    ll x;
    ll y;

    Island() : number(0), x(0), y(0) {}

    Island(ll number, ll x, ll y) : number(number), x(x), y(y) {}

};

struct cmpX {
    bool operator()(const Island &a, const Island &b) {
        return a.x < b.x;
    }
};

struct cmpY {
    bool operator()(const Island &a, const Island &b) {
        return a.y < b.y;
    }
};

struct Graph {

    ll numberOfIslands;

    vector<list<pair<ll, ll>>> neighbours; //no pair needed if neighbour x,y public?

    Graph(ll numberOfIslands) : numberOfIslands(numberOfIslands) {
        this->neighbours.resize(numberOfIslands + 1);
    }

    void addEdge(Island v1, Island v2) {

        neighbours[v1.number].push_back(make_pair(v2.number, min(abs(v1.x - v2.x), abs(v1.y - v2.y))));
//        neighbours[v2.number].push_back(make_pair(v1.number, min(abs(v1.x - v2.x), abs(v1.y - v2.y))));
    }

    void shortestPath(ll source) {

        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pQueue;

        vector<ll> distance(numberOfIslands + 1, INF);

        pQueue.push(make_pair(0, source));
        distance[source] = 0;

        while (!pQueue.empty()) {

            ll u = pQueue.top().second;
            pQueue.pop();

            for (auto i = neighbours[u].begin(); i != neighbours[u].end(); i++) {
                
                ll v = (*i).first;
                ll weight = (*i).second;
                
                if (distance[v] > distance[u] + weight) {
                    
                    distance[v] = distance[u] + weight;
                    pQueue.push(make_pair(distance[v], v));
                }
            }
        }

        cout << distance[numberOfIslands] << endl;

    }

    void printGraph() {

        for (int i = 1; i <= numberOfIslands; i++) {

            cout << i << ": ";
            for (auto &p : neighbours[i]) {

                cout << "(" << p.first << ", " << p.second << ") ";
            }
            cout << endl;
        }
    }

};

int main() {

    int n;
    cin >> n;

    Graph graph(n);
    vector<Island> islands(n);

    for (int i = 0; i < n; i++) {
        cin >> islands[i].x >> islands[i].y;
        islands[i].number = i + 1;
    }

    sort(islands.begin(), islands.end(), cmpX());

    for (int i = 0; i < n; i++) {
        if (i - 1 >= 0) {
            graph.addEdge(islands[i-1], islands[i]);
        }
        if (i + 1 < n) {
            graph.addEdge(islands[i + 1], islands[i]);
        }
    }

    sort(islands.begin(), islands.end(), cmpY());

    for (int i = 0; i < n; i++) {
        if (i - 1 >= 0) {
            graph.addEdge(islands[i - 1], islands[i]);
        }
        if (i + 1 < n) {
            graph.addEdge(islands[i + 1], islands[i]);
        }
    }

    graph.shortestPath(1);

    return 0;
}