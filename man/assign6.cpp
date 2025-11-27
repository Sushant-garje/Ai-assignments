#include <iostream>
#include <vector>
using namespace std;
#define N 8
void printBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}
bool isSafe(vector<vector<int>> &board, int row, int col) {
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }
    return true;
}
bool solveNQueens(vector<vector<int>> &board, int col) {
    if (col >= N) return true;
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            if (solveNQueens(board, col + 1)) return true;
            board[i][col] = 0;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (solveNQueens(board, 0)) {
        printBoard(board);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}