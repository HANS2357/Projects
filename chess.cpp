#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a chess piece
struct Piece {
    char symbol;
    bool isWhite;
};

// Function to initialize the chessboard
vector<vector<Piece>> initializeBoard() {
    vector<vector<Piece>> board(8, vector<Piece>(8));

    // Initialize pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = {'P', false}; // Black pawns
        board[6][i] = {'P', true};  // White pawns
    }

    // Initialize other pieces
    board[0][0] = {'R', false}; // Black rook
    board[0][7] = {'R', false}; // Black rook
    board[7][0] = {'R', true};  // White rook
    board[7][7] = {'R', true};  // White rook

    board[0][1] = {'N', false}; // Black knight
    board[0][6] = {'N', false}; // Black knight
    board[7][1] = {'N', true};  // White knight
    board[7][6] = {'N', true};  // White knight

    board[0][2] = {'B', false}; // Black bishop
    board[0][5] = {'B', false}; // Black bishop
    board[7][2] = {'B', true};  // White bishop
    board[7][5] = {'B', true};  // White bishop

    board[0][3] = {'Q', false}; // Black queen
    board[7][3] = {'Q', true};  // White queen

    board[0][4] = {'K', false}; // Black king
    board[7][4] = {'K', true};  // White king

    return board;
}

// Function to render the chessboard
void renderBoard(const vector<vector<Piece>>& board) {
    cout << "  a b c d e f g h" << endl;
    cout << " -----------------" << endl;

    for (int i = 0; i < 8; ++i) {
        cout << 8 - i << "|";
        for (int j = 0; j < 8; ++j) {
            if (board[i][j].symbol != '\0') {
                cout << board[i][j].symbol << "|";
            } else {
                cout << " |";
            }
        }
        cout << " " << 8 - i << endl;
    }

    cout << " -----------------" << endl;
    cout << "  a b c d e f g h" << endl;
}

// Function to convert the user's input to board coordinates
pair<int, int> parseMove(const string& move) {
    int row = 8 - (move[1] - '0');
    int col = move[0] - 'a';
    return make_pair(row, col);
}

// Function to validate the user's move
bool isValidMove(const vector<vector<Piece>>& board, const pair<int, int>& from, const pair<int, int>& to) {
    Piece piece = board[from.first][from.second];

    // Check if the piece exists and it's the player's turn
    if (piece.symbol == '\0' || piece.isWhite != (from.first > 3)) {
        return false;
    }

    // Implement move validation logic based on chess rules
    // This example only allows moving one square in any direction

    int rowDiff = abs(to.first - from.first);
    int colDiff = abs(to.second - from.second);

    if (rowDiff > 1 || colDiff > 1 || (rowDiff == 0 && colDiff == 0)) {
        return false;
    }

    return true;
}

int main() {
    vector<vector<Piece>> board = initializeBoard();
    renderBoard(board);

    bool isWhiteTurn = true;
    string move;

    while (true) {
        if (isWhiteTurn) {
            cout << "White's move: ";
        } else {
            cout << "Black's move: ";
        }

        cin >> move;

        pair<int, int> from = parseMove(move.substr(0, 2));
        pair<int, int> to = parseMove(move.substr(2, 2));

        if (isValidMove(board, from, to)) {
            // Make the move
            board[to.first][to.second] = board[from.first][from.second];
            board[from.first][from.second] = {'\0', false};

            renderBoard(board);

            // Switch turns
            isWhiteTurn = !isWhiteTurn;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }

    return 0;
}
