#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    double g, h;
    Node* parent;

    Node(int x, int y, double g = 0, double h = 0, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    double f() const {
        return g + h;
    }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

double heuristic(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

vector<pair<int, int>> getNeighbors(int x, int y) {
    return {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
}

bool isValid(int x, int y, int rows, int cols, const vector<vector<int>>& grid) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
}

vector<pair<int, int>> reconstructPath(Node* node) {
    vector<pair<int, int>> path;
    while (node) {
        path.emplace_back(node->x, node->y);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> aStar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size(), cols = grid[0].size();
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    unordered_map<int, Node*> allNodes;

    auto hash = [&](int x, int y) { return x * cols + y; };

    Node* startNode = new Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));
    openSet.push(*startNode);
    allNodes[hash(start.first, start.second)] = startNode;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.x == goal.first && current.y == goal.second) {
            return reconstructPath(&current);
        }

        for (auto [nx, ny] : getNeighbors(current.x, current.y)) {
            if (!isValid(nx, ny, rows, cols, grid)) continue;

            double tentativeG = current.g + 1;
            int neighborHash = hash(nx, ny);

            if (allNodes.find(neighborHash) == allNodes.end() || tentativeG < allNodes[neighborHash]->g) {
                Node* neighbor = new Node(nx, ny, tentativeG, heuristic(nx, ny, goal.first, goal.second), allNodes[hash(current.x, current.y)]);
                openSet.push(*neighbor);
                allNodes[neighborHash] = neighbor;
            }
        }
    }

    return {}; // No path found
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    vector<pair<int, int>> path = aStar(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (auto [x, y] : path) {
            cout << "(" << x << ", " << y << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}