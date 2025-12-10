#include "Obstacles.h"
#include <iostream>
#include <ctime>

using namespace std;



ObstaclesBoard::ObstaclesBoard() : Board<char>(6, 6) {
    // Initialize the board with empty spaces
    for (auto& row : board) {
        fill(row.begin(), row.end(), ' ');
    }
}

bool ObstaclesBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    
    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;
    }

    board[r][c] = move->get_symbol();
    n_moves++;
    return true;
}

bool ObstaclesBoard::is_win(Player<char>* p) {
    char s = p->get_symbol();
    
    // Check Horizontal
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] == s && board[i][j + 1] == s && 
                board[i][j + 2] == s && board[i][j + 3] == s) return true;
        }
    }

    // Check Vertical
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == s && board[i + 1][j] == s && 
                board[i + 2][j] == s && board[i + 3][j] == s) return true;
        }
    }

    // Check Diagonal 
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] == s && board[i + 1][j + 1] == s && 
                board[i + 2][j + 2] == s && board[i + 3][j + 3] == s) return true;
        }
    }

    // Check Diagonal (Down-Left)
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 3; j < columns; ++j) {
            if (board[i][j] == s && board[i + 1][j - 1] == s && 
                board[i + 2][j - 2] == s && board[i + 3][j - 3] == s) return true;
        }
    }

    return false;
}

bool ObstaclesBoard::is_draw(Player<char>* p) {
   
    return (n_moves == rows * columns) && !is_win(p);
}

bool ObstaclesBoard::is_lose(Player<char>* p) {
    
    return false;
}

bool ObstaclesBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

void ObstaclesBoard::add_two_obstacles() {
    vector<pair<int, int>> empty_cells;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == ' ') {
                empty_cells.push_back({ i, j });
            }
        }
    }

    if (empty_cells.empty()) return;

 
    
    for (int k = 0; k < 2 && !empty_cells.empty(); ++k) {
   
        int idx = rand() % empty_cells.size();
        
        pair<int, int> p = empty_cells[idx];
        board[p.first][p.second] = OBSTACLE;
        n_moves++;

        empty_cells.erase(empty_cells.begin() + idx);
    }
}


ObstaclesUI::ObstaclesUI() : UI<char>("Obstacles Tic-Tac-Toe (Connect 4)", 3) {
}

Move<char>* ObstaclesUI::get_move(Player<char>* p) {
    int x, y;
    if (p->get_type() == PlayerType::COMPUTER) {

        x = rand() % 6;
        y = rand() % 6;
    }
    else {
        cout << p->get_name() << " (" << p->get_symbol() << "), enter row and column (e.g., 0 1): ";
        cin >> x >> y;
        while (cin.fail() || x < 0 || x > 5 || y < 0 || y > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid. Enter row and column (0-5): ";
            cin >> x >> y;
        }
    }
    return new Move<char>(x, y, p->get_symbol());
}

Player<char>* ObstaclesUI::create_player(string& name, char symbol, PlayerType type) {

    char actualSymbol = symbol;
    if (symbol == '1') actualSymbol = 'X';
    else if (symbol == '2') actualSymbol = 'O';

    return new Player<char>(name, actualSymbol, type);
}


void launchObstacles(){ 
     cout << "\n=== Obstacles Tic-Tac-Toe (6x6) ===\n";
    cout << "First to connect 4 wins! After every full round, 2 obstacles appear!\n\n";

    ObstaclesBoard board;
    ObstaclesUI ui;

    Player<char>** players = ui.setup_players();

    ui.display_board_matrix(board.get_board_matrix());

    int turn = 0; 

    while (!board.game_is_over(players[0]) && !board.game_is_over(players[1])) {
        Player<char>* current = players[turn];

        // Get Move
        Move<char>* move = ui.get_move(current);
        while (!board.update_board(move)) {
            ui.display_message("Invalid Move! Try again.");
            delete move;
            move = ui.get_move(current);
        }
        delete move;

        ui.display_board_matrix(board.get_board_matrix());

       
        if (board.is_win(current)) {
            ui.display_message(current->get_name() + " WINS!");
            break;
        }
        if (board.is_draw(current)) {
            ui.display_message("DRAW!");
            break;
        }

      
        if (turn == 1) {
            ui.display_message("--- Adding 2 Obstacles! ---");
            board.add_two_obstacles();
            ui.display_board_matrix(board.get_board_matrix());
            
            // Check draw again in case obstacles filled the board
             if (board.is_draw(current)) {
                ui.display_message("DRAW (Board Full)!");
                break;
            }
        }

        turn = 1 - turn;
    }

    delete players[0];
    delete players[1];
    delete[] players;

}