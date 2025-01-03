#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;

// Structure for a Node in Binary Tree
struct Node {
    vector<char> board;
    char player;
    Node* left;
    Node* right;
};

// Structure for representing game state
struct GameState {
    vector<char> board;
    char currentPlayer;
};

// Hash function for game state
struct HashState {
    size_t operator()(const GameState& state) const {
        size_t hash = 17;
        for (char c : state.board) {
            hash = hash * 31 + c;
        }
        hash = hash * 31 + state.currentPlayer;
        return hash;
    }
};

// Function to create a new Node
Node* createNode(const vector<char>& board, char player) {
    Node* newNode = new Node();
    newNode->board = board;
    newNode->player = player;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to check if a player has won
bool checkWin(const vector<char>& board, char player) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i*3] == player && board[i*3 + 1] == player && board[i*3 + 2] == player)
            return true;
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
            return true;
    }
    // Check diagonals
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player))
        return true;
    return false;
}

// Function to check if the board is full
bool isBoardFull(const vector<char>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O')
            return false;
    }
    return true;
}

// Function to get possible moves from a board state
vector<vector<char>> getPossibleMoves(const vector<char>& board, char currentPlayer) {
    vector<vector<char>> possibleMoves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            vector<char> newBoard = board;
            newBoard[i] = currentPlayer;
            possibleMoves.push_back(newBoard);
        }
    }
    return possibleMoves;
}

// Function to perform BFS traversal
void bfsTraversal(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // Process current node
        cout << "Player " << current->player << "'s turn:" << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << current->board[i * 3 + j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

// Function to perform DFS traversal
void dfsTraversal(Node* root) {
    if (!root) return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        // Process current node
        cout << "Player " << current->player << "'s turn:" << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << current->board[i * 3 + j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
}

// Function to save game state to a file
void saveGameState(const vector<char>& board, char currentPlayer, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << currentPlayer << "\n";
        for (char cell : board) {
            file << cell << " ";
        }
        file.close();
        cout << "Game state saved successfully to " << filename << endl;
    } else {
        cout << "Unable to open file for saving game state." << endl;
    }
}

// Function to load game state from a file
GameState loadGameState(const string& filename) {
    ifstream file(filename);
    GameState gameState;
    if (file.is_open()) {
        file >> gameState.currentPlayer;
        char cell;
        while (file >> cell) {
            gameState.board.push_back(cell);
        }
        file.close();
    } else {
        cout << "Unable to open file for loading game state." << endl;
    }
    return gameState;
}

// Function to display the game board
void displayBoard(const vector<char>& board) {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "| ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i * 3 + j] << " | ";
        }
        cout << endl;
        cout << "-------------" << endl;
    }
}

// Function to get user input for move
int getUserMove(const vector<char>& board) {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> move;
        if (move < 1 || move > 9 || board[move - 1] != '-') {
            cout << "Invalid move! Try again." << endl;
        } else {
            break;
        }
    }
    return move;
}

// Function to play Tic Tac Toe
void playTicTacToe(vector<char>& board, char& currentPlayer) {
    int moves = 0;

    while (moves < 9) {
        // Display current board state
        cout << "Current Board:" << endl;
        displayBoard(board);

        // Prompt user for move
        int move = getUserMove(board);

        // Update board
        board[move - 1] = currentPlayer;

        // Check for win
        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins!" << endl;
            return;
        }

        // Check for draw
        if (isBoardFull(board)) {
            cout << "It's a draw!" << endl;
            return;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        moves++;
    }
}

// Function to redirect code to filename given
void redirectToFile(const string& filename) {
    GameState gameState = loadGameState(filename);
    if (!gameState.board.empty()) {
        cout << "Game state loaded from " << filename << endl;
        vector<char> board = gameState.board; // Update board
        char currentPlayer = gameState.currentPlayer; // Update currentPlayer
        playTicTacToe(board, currentPlayer);
    } else {
        cout << "No valid game state found in " << filename << ". Starting new game." << endl;
    }
}

int main() {
    char choice;
    const string filename = "game_state.txt"; // File name added here
    vector<char> board(9, '-');
    char currentPlayer = 'X';
    do {
        cout << "Menu:" << endl;
        cout << "1. Play Tic Tac Toe" << endl;
        cout << "2. Load Game from File" << endl; // Added option to load game from file
        cout << "3. Save Game" << endl; // Added option to save the game
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                playTicTacToe(board, currentPlayer);
                break;
            case '2':
                redirectToFile(filename);
                break;
            case '3':
                saveGameState(board, currentPlayer, filename); // Save the game state
                break;
            case '4':
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
                break;
        }
    } while (choice != '4');

    return 0;
}
