#include "diamond.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>

using namespace std;



DiamondBoard::DiamondBoard() : Board<char>(5, 5) {
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            board[r][c] = ' ';
}

bool DiamondBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;
    }
    board[r][c] = symbol;
    n_moves++;
    return true;
}


void DiamondBoard::display_board() {
    cout << "\n\n";
    cout << "        DIAMOND TIC-TAC-TOE\n";
    cout << "      -----------------------\n";

  
    for (int k = 0; k <= 8; ++k) {
        
        //  Padding to create the diamond shape
        int padding = abs(4 - k) * 3 + 4; 
        cout << string(padding, ' ');

        //  Iterate cells in this diagonal slice
        int r_start = (k < 5) ? k : 4; 
        int r_end   = (k < 5) ? 0 : k - 4;

        for (int r = r_start; r >= r_end; --r) {
            int c = k - r;
            char val = board[r][c];
            
   
            if (val == ' ') cout << "[.]   "; 
            else            cout << "[" << val << "]   ";
        }
        cout << "\n\n"; 
    }
    
    
    cout << "      Top:(0,0)  Left:(4,0)  Right:(0,4)  Btm:(4,4)\n\n";
}

int DiamondBoard::count_consecutive(int r, int c, int dr, int dc, char symbol) {
    int count = 1; 
    
    // Check Forward
    int next_r = r + dr;
    int next_c = c + dc;
    while (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < columns && board[next_r][next_c] == symbol) {
        count++;
        next_r += dr;
        next_c += dc;
    }
    // Check Backward
    next_r = r - dr;
    next_c = c - dc;
    while (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < columns && board[next_r][next_c] == symbol) {
        count++;
        next_r -= dr;
        next_c -= dc;
    }
    return count;
}

bool DiamondBoard::check_intersection_win(int r, int c, char symbol) {
 
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};
    int lengths[4];

    for (int i = 0; i < 4; ++i) {
        lengths[i] = count_consecutive(r, c, dr[i], dc[i], symbol);
    }

    bool has_3 = false;
    bool has_4 = false;

    for (int len : lengths) {
        if (len == 3) has_3 = true; 
        if (len == 4) has_4 = true; 
    }
    // Win if we have a line of 3 AND a line of 4 intersecting at this piece
    return (has_3 && has_4); 
}

bool DiamondBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (board[r][c] == symbol) {
                if (check_intersection_win(r, c, symbol)) return true;
            }
        }
    }
    return false;
}

bool DiamondBoard::is_draw(Player<char>* player) {
    return (n_moves == rows * columns) && !is_win(player);
}

bool DiamondBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


Move<char>* DiamondUI::get_move(Player<char>* p) {
    if (p->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = p->get_board_ptr();
        auto grid = board->get_board_matrix();
        vector<pair<int, int>> emptyCells;
        
        for (int r = 0; r < 5; ++r) {
            for (int c = 0; c < 5; ++c) {
                if (grid[r][c] == ' ') emptyCells.push_back({r, c});
            }
        }
        
        if (!emptyCells.empty()) {
            int idx = rand() % emptyCells.size();
            return new Move<char>(emptyCells[idx].first, emptyCells[idx].second, p->get_symbol());
        }
        return nullptr;
    }

    int r, c;
    cout << p->get_name() << " (" << p->get_symbol() << "), enter coordinate (row col): ";
    while (!(cin >> r >> c) || r < 0 || r > 4 || c < 0 || c > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter row 0-4 and col 0-4: ";
    }
    return new Move<char>(r, c, p->get_symbol());
}

Player<char>* DiamondUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}



void launchDiamondTTT() {
    cout << "\n=== Starting Diamond Tic-Tac-Toe ===\n";
    cout << "Win Condition: Form a line of 3 AND a line of 4 simultaneously.\n";
    
    DiamondBoard board;
    DiamondUI ui;
    Player<char>** players = ui.setup_players();
    
   
    
    players[0]->set_board_ptr(&board);
    players[1]->set_board_ptr(&board);

    board.display_board(); 

    bool gameRunning = true;
    while (gameRunning) {
        for (int i = 0; i < 2; ++i) {
            Player<char>* currentPlayer = players[i];
            
    
            Move<char>* move = ui.get_move(currentPlayer);
            while (!board.update_board(move)) {
                cout << "Invalid move (occupied or out of bounds). Try again.\n";
                delete move; 
                move = ui.get_move(currentPlayer);
            }
            delete move; 

    
            board.display_board();

            if (board.is_win(currentPlayer)) {
                cout << "\nCONGRATULATIONS! " << currentPlayer->get_name() << " WINS!\n";
                gameRunning = false;
                break;
            }
            if (board.is_draw(currentPlayer)) {
                cout << "\nIt's a DRAW!\n";
                gameRunning = false;
                break;
            }
        }
    }

    
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
}