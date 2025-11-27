#include <iostream>
#include <limits>
using namespace std;
#define PLAYER 'X'
#define OPPONENT 'O'
struct Move {
    int row, col;
};
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}
int evaluate(char b[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == PLAYER) return +10;
            else if (b[row][0] == OPPONENT) return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == PLAYER) return +10;
            else if (b[0][col] == OPPONENT) return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == PLAYER) return +10;
        else if (b[0][0] == OPPONENT) return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == PLAYER) return +10;
        else if (b[0][2] == OPPONENT) return -10;
    }

    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) return score - depth;  
    if (score == -10) return score + depth; 
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = PLAYER;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = OPPONENT;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}
Move findBestMove(char board[3][3]) {
    int bestVal = numeric_limits<int>::min();
    Move bestMove{-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = PLAYER;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '_';
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
int main() {
    char board[3][3] = {
        { 'X', 'O', 'X' },
        { 'O', 'O', 'X' },
        { '_', '_', '_' }
    };
    Move bestMove = findBestMove(board);
    cout << "The Optimal Move is :\n";
    cout << "ROW: " << bestMove.row << " COL: " << bestMove.col << endl;
    return 0;
}