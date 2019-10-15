#include <iostream>
#include <list>
#include <vector>

using namespace std;

constexpr int MAXN = (int)1e5;
constexpr int FIRST_LEAF = 131072;

struct Session {

    int x;
    int y;
    bool used;

    Session() {}

    Session(int a, int b) {
        x = a;
        y = b;
        used = false;
    }
};

vector<Session> sessions(1);
vector<list<int>> waitingListsMin(FIRST_LEAF + 10);
vector<list<int>> waitingListsMax(FIRST_LEAF + 10);

struct myComparatorMin {

    bool operator()(int session1, int session2) {

        if (session1 <= 0)
            return false;

        if (session2 <= 0)
            return true;

        return sessions[session1].y <= sessions[session2].y;
    }
} cmpMin;

struct myComparatorMax {

    bool operator()(int session1, int session2) {

        if (session1 <= 0)
            return false;

        if (session2 <= 0)
            return true;
        return sessions[session1].y >= sessions[session2].y;
    }
} cmpMax;

void sort_lists() {

    for (auto& list : waitingListsMin)
        list.sort(myComparatorMin());

    for (auto& list : waitingListsMax)
        list.sort(myComparatorMax());
}

class SegmentTreeMin {

public:
    vector<int> nodeValues;

    SegmentTreeMin() {
        this->nodeValues = vector<int>(2 * FIRST_LEAF + 10);
    }

    int leftSon(int node) { return node << 1; }
    int rightSon(int node) { return (node << 1) + 1; }
    int parent(int node) { return node >> 1; }

    void build() {

        for (int i = 1; i <= MAXN; i++) {
            int node = FIRST_LEAF + i - 1;
            if (!waitingListsMin[i].empty()) {
                nodeValues[node] = waitingListsMin[i].front();
                waitingListsMin[i].pop_front();
            }
            else {
                nodeValues[node] = -1;
            }
        }

        for (int i = FIRST_LEAF - 1; i >= 1; i--) {
            nodeValues[i] = cmpMin(nodeValues[rightSon(i)], nodeValues[leftSon(i)]) ? nodeValues[rightSon(i)] : nodeValues[leftSon(i)];
        }
    }

    void delete_session(int i) {

        sessions[i].used = true;
        int node = sessions[i].x + FIRST_LEAF - 1;
        int sessionStart = sessions[i].x;

        if (nodeValues[node] == i) {

            while (!waitingListsMin[sessionStart].empty() && sessions[waitingListsMin[sessionStart].front()].used) {
                waitingListsMin[sessionStart].pop_front();
            }

            if (!waitingListsMin[sessionStart].empty()) {
                nodeValues[node] = waitingListsMin[sessionStart].front();
                waitingListsMin[sessionStart].pop_front();
            }
            else {
                nodeValues[node] = -1;
            }

            node = parent(node);

            while (node != 0) {

                nodeValues[node] = cmpMin(nodeValues[rightSon(node)], nodeValues[leftSon(node)]) ? nodeValues[rightSon(
                        node)] : nodeValues[leftSon(
                        node)];
                node = parent(node);
            }

        }
    }

    bool is_in(int x, int y, int interval) {
        return interval > 0 && x <= sessions[interval].x && sessions[interval].y <= y;
    }

    int in(int x, int y) {

        int left = x + FIRST_LEAF - 1;
        int right = y + FIRST_LEAF - 1;
        int found = -1;

        while (left <= right) {

            if (left & 1) {
                if (cmpMin(nodeValues[left], found))
                    found = nodeValues[left];
                left++;
            }
            if (right & 0) {
                if (cmpMin(nodeValues[right], found))
                    found = nodeValues[right];
                right--;
            }
            left = left >> 1;
            right = right >> 1;
        }

        if (is_in(x, y, found)) {
            return found;
        }
        else {
            return -1;
        }
    }

    int none(int x, int y) {

        int ans = in(1, x - 1);
        if (ans == -1)
            ans = in(y + 1, MAXN);

        return ans;
    }
};

class SegmentTreeMax {

public:
    vector<int> nodeValues;

    int leftSon(int node) { return node << 1; }
    int rightSon(int node) { return (node << 1) + 1; }
    int parent(int node) { return node >> 1; }

    SegmentTreeMax() {
        this->nodeValues = vector<int>(2 * FIRST_LEAF + 10);
    }

    void build() {

        for (int i = 1; i <= MAXN; i++) {
            int node = FIRST_LEAF + i - 1;
            if (!waitingListsMax[i].empty()) {
                nodeValues[node] = waitingListsMax[i].front();
                waitingListsMax[i].pop_front();
            }
            else {
                nodeValues[node] = -1;
            }
        }

        for (int i = FIRST_LEAF - 1; i >= 1; i--) {
            nodeValues[i] = cmpMax(nodeValues[rightSon(i)], nodeValues[leftSon(i)]) ? nodeValues[rightSon(i)] : nodeValues[leftSon(i)];
        }
    }

    void delete_session(int i) {

        sessions[i].used = true;
        int node = sessions[i].x + FIRST_LEAF - 1;
        int sessionStart = sessions[i].x;

        if (nodeValues[node] == i) {

            while (!waitingListsMax[sessionStart].empty() && sessions[waitingListsMax[sessionStart].front()].used) {
                waitingListsMax[sessionStart].pop_front();
            }

            if (!waitingListsMax[sessionStart].empty()) {
                nodeValues[node] = waitingListsMax[sessionStart].front();
                waitingListsMax[sessionStart].pop_front();
            }
            else {
                nodeValues[node] = -1;
            }

            node = parent(node);

            while (node != 0) {

                nodeValues[node] = cmpMax(nodeValues[rightSon(node)], nodeValues[leftSon(node)]) ? nodeValues[rightSon(
                        node)] : nodeValues[leftSon(
                        node)];
                node = parent(node);
            }
        }
    }

    bool is_over(int x, int y, int interval) {
        return interval > 0 && sessions[interval].x <= x && y <= sessions[interval].y;
    }

    int over(int x, int y) {

        int left = x + FIRST_LEAF - 1;
        int found = -1;

        while (left != 0 && (left & (left - 1)) != 0) {

            if (is_over(x, y, nodeValues[left])) {
                found = nodeValues[left];
                break;
            }

            left = ((left & 1) == 0) ? parent(left) - 1 : parent(left);
        }

        if ((left & (left - 1)) == 0) {
            if (is_over(x, y, nodeValues[left])) {
                found = nodeValues[left];
            }
        }

        return found;
    }
};

int main() {

    ios_base::sync_with_stdio(false);

    int n, q, ai, bi, xi, yi, found;
    string query;

    cin >> n;

    for (int i = 1; i <= n; i++) {

        cin >> ai >> bi;
        sessions.emplace_back(ai, bi);
        waitingListsMax[ai].push_back(i);
        waitingListsMin[ai].push_back(i);
    }

    sort_lists();

    SegmentTreeMin minSTree = SegmentTreeMin();
    SegmentTreeMax maxSTree = SegmentTreeMax();
    minSTree.build();
    maxSTree.build();

    cin >> q;

    for (int i = 1; i <= q; i++) {

        cin >> query >> xi >> yi;

        if (query == "in") {

            found = minSTree.in(xi, yi);
        }
        else if (query == "none") {

            found = minSTree.none(xi, yi);
        }
        else if (query == "over") {

            found = maxSTree.over(xi, yi);
        }
        else { //query == "some"

            found = maxSTree.over(xi, xi);
            if (found == -1) {
                found = maxSTree.over(yi, yi);
                if (found == -1) {
                    found = minSTree.in(xi, yi);
                }
            }
        }

        if (found != -1) {
            minSTree.delete_session(found);
            maxSTree.delete_session(found);
        }

        cout << found << " ";
    }

    cout << endl;

    return 0;
}