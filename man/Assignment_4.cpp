#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    double g, h;
    Node* parent;

    Node(int x, int y, double g = 0, double h = 0, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    double f() const { return g + h; }
};

double heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);  // Manhattan distance
}

vector<pair<int, int>> getNeighbors(int x, int y) {
    vector<pair<int, int>> neighbors;
    neighbors.push_back(make_pair(x + 1, y));
    neighbors.push_back(make_pair(x - 1, y));
    neighbors.push_back(make_pair(x, y + 1));
    neighbors.push_back(make_pair(x, y - 1));
    return neighbors;
}

bool isValid(int x, int y, int rows, int cols, const vector<vector<int>>& grid) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
}

vector<pair<int, int>> reconstructPath(Node* node) {
    vector<pair<int, int>> path;
    while (node) {
        path.push_back(make_pair(node->x, node->y));
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> aStar(const vector<vector<int>>& grid,
                             pair<int, int> start,
                             pair<int, int> goal) {

    int rows = grid.size();
    int cols = grid[0].size();

    auto cmp = [](Node* a, Node* b) { return a->f() > b->f(); };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> openSet(cmp);

    unordered_map<int, Node*> visited;
    auto hash = [&](int x, int y) { return x * cols + y; };

    Node* startNode = new Node(start.first, start.second,
                               0, heuristic(start.first, start.second, goal.first, goal.second));
    openSet.push(startNode);
    visited[hash(start.first, start.second)] = startNode;

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->x == goal.first && current->y == goal.second)
            return reconstructPath(current);

        vector<pair<int, int>> neighbors = getNeighbors(current->x, current->y);
        for (size_t i = 0; i < neighbors.size(); i++) {
            int nx = neighbors[i].first;
            int ny = neighbors[i].second;

            if (!isValid(nx, ny, rows, cols, grid))
                continue;

            double tentativeG = current->g + 1;
            int id = hash(nx, ny);

            if (visited.find(id) == visited.end() || tentativeG < visited[id]->g) {
                Node* neighbor = new Node(nx, ny, tentativeG,
                                          heuristic(nx, ny, goal.first, goal.second), current);
                visited[id] = neighbor;
                openSet.push(neighbor);
            }
        }
    }
    return vector<pair<int, int>>(); // No path found
}

int main() {
    int rows, cols;
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols));
    cout << "Enter grid (0 = free, 1 = blocked):\n";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> grid[i][j];

    int sx, sy, gx, gy;
    cout << "Enter start (row col): ";
    cin >> sx >> sy;

    cout << "Enter goal (row col): ";
    cin >> gx >> gy;

    vector<pair<int, int>> path = aStar(grid, make_pair(sx, sy), make_pair(gx, gy));

    if (!path.empty()) {
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++)
            cout << "(" << path[i].first << "," << path[i].second << ") ";
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
