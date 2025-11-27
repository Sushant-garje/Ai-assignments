#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> state;
    Node* parent;
    int blankPos;

    Node(vector<int> s, Node* p, int b) : state(s), parent(p), blankPos(b) {}
};

vector<int> goal = {1,2,3,4,5,6,7,8,0};

bool isGoalState(const vector<int>& state) {
    return state == goal;
}

// Print the solution path
void printSolution(Node* node) {
    vector<Node*> path;
    while (node != nullptr) {
        path.push_back(node);
        node = node->parent;
    }
    reverse(path.begin(), path.end());

    cout << "\nSolution Path (" << path.size()-1 << " moves):\n";
    for (Node* n : path) {
        for (int i = 0; i < 9; i++) {
            cout << n->state[i] << " ";
            if (i % 3 == 2) cout << endl;
        }
        cout << endl;
    }
}

// Generate all valid successors
vector<Node*> getSuccessors(Node* node) {
    vector<Node*> successors;
    vector<int> moves = {-1,1,-3,3};
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

// BFS search
void BFS(vector<int> startState) {
    queue<Node*> q;
    set<vector<int>> visited;

    int blankPos = find(startState.begin(), startState.end(), 0) - startState.begin();
    Node* root = new Node(startState, nullptr, blankPos);

    q.push(root);
    visited.insert(startState);

    while (!q.empty()) {
        Node* current = q.front(); q.pop();

        if (isGoalState(current->state)) {
            printSolution(current);
            return;
        }

        for (Node* successor : getSuccessors(current)) {
            if (!visited.count(successor->state)) {
                visited.insert(successor->state);
                q.push(successor);
            }
        }
    }
    cout << "No solution found!" << endl;
}

int main() {
    vector<int> startState(9);
    cout << "Enter the 8-puzzle initial state (0 for blank) in 3x3 format:\n";
    for (int i = 0; i < 9; i++) cin >> startState[i];

    BFS(startState);

    return 0;
}
