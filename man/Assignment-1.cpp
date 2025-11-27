#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> state;
    Node* parent;
    int blankPos;

    Node(vector<int> s, Node* p, int b) : state(s), parent(p), blankPos(b) {}
};

bool isGoalState(const vector<int>& state) {
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    return state == goal;
}

void printSolution(Node* node) {
    if (node == nullptr) return;
    printSolution(node->parent);
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) cout << endl;
        cout << node->state[i] << " ";
    }
    cout << endl;
}

vector<Node*> getSuccessors(Node* node) {
    vector<Node*> successors;
    vector<int> moves = {-1, 1, -3, 3}; // Left, Right, Up, Down
    int blank = node->blankPos;

    for (int move : moves) {
        int newBlank = blank + move;
        if ((move == -1 && blank % 3 == 0) || (move == 1 && blank % 3 == 2)) continue;
        if (newBlank < 0 || newBlank >= 9) continue;

        vector<int> newState = node->state;
        swap(newState[blank], newState[newBlank]);
        successors.push_back(new Node(newState, node, newBlank));
    }
    return successors;
}

void BFS(vector<int> startState) {
    queue<Node*> frontier;
    map<vector<int>, bool> visited;

    Node* root = new Node(startState, nullptr, find(startState.begin(), startState.end(), 0) - startState.begin());
    frontier.push(root);
    visited[startState] = true;

    while (!frontier.empty()) {
        Node* current = frontier.front();
        frontier.pop();

        if (isGoalState(current->state)) {
            cout << "BFS Solution:" << endl;
            printSolution(current);
            return;
        }

        for (Node* successor : getSuccessors(current)) {
            if (!visited[successor->state]) {
                visited[successor->state] = true;
                frontier.push(successor);
            }
        }
    }
    cout << "No solution found with BFS." << endl;
}

void DFS(vector<int> startState) {
    stack<Node*> frontier;
    map<vector<int>, bool> visited;

    Node* root = new Node(startState, nullptr, find(startState.begin(), startState.end(), 0) - startState.begin());
    frontier.push(root);
    visited[startState] = true;

    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();

        if (isGoalState(current->state)) {
            cout << "DFS Solution:" << endl;
            printSolution(current);
            return;
        }

        for (Node* successor : getSuccessors(current)) {
            if (!visited[successor->state]) {
                visited[successor->state] = true;
                frontier.push(successor);
            }
        }
    }
    cout << "No solution found with DFS." << endl;
}

int main() {
    vector<int> startState = {1, 2, 3, 4, 5, 6, 0, 7, 8}; // Example start state

    cout << "Starting BFS..." << endl;
    BFS(startState);

    cout << "Starting DFS..." << endl;
    DFS(startState);

    return 0;
}