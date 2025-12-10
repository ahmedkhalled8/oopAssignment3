#include "Tic5x5.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;



TicTacToe5x5Board::TicTacToe5x5Board() : Board<char>(5, 5) {
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            board[r][c] = ' ';
}

void TicTacToe5x5Board::display_board() {
    cout << "\n   | 0 | 1 | 2 | 3 | 4 |\n";
    cout << " --+---+---+---+---+---+\n";
    for (int r = 0; r < rows; r++) {
        cout << " " << r << " |";
        for (int c = 0; c < columns; c++) {
            cout << " " << board[r][c] << " |";
        }
        cout << "\n --+---+---+---+---+---+\n";
    }
    cout << " Score: P1(X): " << p1_score << " | P2(O): " << p2_score << "\n";
}

bool TicTacToe5x5Board::check_three(int r, int c, int dr, int dc, char symbol) {

    int r2 = r + dr;
    int c2 = c + dc;
    int r3 = r + 2 * dr;
    int c3 = c + 2 * dc;
    
    if (r >= 0 && r < rows && c >= 0 && c < columns &&
        r2 >= 0 && r2 < rows && c2 >= 0 && c2 < columns &&
        r3 >= 0 && r3 < rows && c3 >= 0 && c3 < columns) {
        
        return (board[r][c] == symbol && board[r2][c2] == symbol && board[r3][c3] == symbol);
    }
    return false;
}

void TicTacToe5x5Board::update_score(char symbol, int row, int col) {
    int new_lines = 0;
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (int i = 0; i < 4; ++i) {
        int dr = directions[i][0];
        int dc = directions[i][1];
        
        for (int j = -2; j <= 0; ++j) {
            if (check_three(row + j * dr, col + j * dc, dr, dc, symbol)) {
                new_lines++;
            }
        }
    }

    if (symbol == 'X') {
        p1_score += new_lines;
    } else if (symbol == 'O') {
        p2_score += new_lines;
    }
}

bool TicTacToe5x5Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;
    }
    
    board[r][c] = symbol;
    n_moves++;
    
    
    update_score(symbol, r, c);
    
    return true;
}

bool TicTacToe5x5Board::is_win(Player<char>* player) {

    return false; 
}

bool TicTacToe5x5Board::is_draw(Player<char>* player) {
    if (n_moves == (rows * columns) - 1) { // 24 moves logic
        cout << "\n--- GAME ENDED: 24 MOVES REACHED ---\n";
        
        if (p1_score > p2_score) {
            cout << "PLAYER 1 (X) WINS with " << p1_score << " lines!\n";
        } else if (p2_score > p1_score) {
            cout << "PLAYER 2 (O) WINS with " << p2_score << " lines!\n";
        } else {
            cout << "It's a TIE! Both players scored " << p1_score << " lines.\n";
        }
        return true;
    }
    return false;
}



Move<char>* TicTacToe5x5UI::get_move(Player<char>* p) {
    // 1. Check if the player is a Computer
    if (p->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = p->get_board_ptr();
        int rows = board->get_rows();
        int cols = board->get_columns();
        vector<vector<char>> grid = board->get_board_matrix();
        
        // Find all empty cells 
        vector<pair<int, int>> emptyCells;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == ' ') {
                    emptyCells.push_back({r, c});
                }
            }
        }

        // Pick a random empty cell
        if (!emptyCells.empty()) {
            int index = rand() % emptyCells.size();
            int r = emptyCells[index].first;
            int c = emptyCells[index].second;
            
            cout << p->get_name() << " (" << p->get_symbol() << ") chooses (" << r << ", " << c << ")\n";
            return new Move<char>(r, c, p->get_symbol());
        } else {
           
            return new Move<char>(-1, -1, p->get_symbol());
        }
    }

    int r, c;
    cout << p->get_name() << " (" << p->get_symbol() << "), enter row and column (0-4): ";
    
    // Input validation loop
    while (!(cin >> r >> c) || r < 0 || r > 4 || c < 0 || c > 4) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter row and column (0-4): ";
    }
    
    return new Move<char>(r, c, p->get_symbol());
}

Player<char>* TicTacToe5x5UI::create_player(string& name, char symbol, PlayerType type) {
    
    char actualSymbol = 'X';
    if (symbol == '2') actualSymbol = 'O';
    
    return new Player<char>(name, actualSymbol, type);
}


void launchTicTacToe5x5() {
    cout << "\n=== Starting 5x5 Tic-Tac-Toe ===\n";
    TicTacToe5x5Board board;
    TicTacToe5x5UI ui;
    Player<char>** players = ui.setup_players();
    GameManager<char> manager(&board, players, &ui);
    manager.run();
    
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
}