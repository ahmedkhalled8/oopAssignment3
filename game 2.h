#include "FourInARow.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

FourInARow_Board::FourInARow_Board() : Board(6, 7) {
    col_heights.resize(7, 0);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = ' ';
        }
    }
}

bool FourInARow_Board::valid_col(int col) const {
    return (col >= 0 && col < 7 && col_heights[col] < 6);
}

int FourInARow_Board::get_row(int col) const {
    return 5 - col_heights[col];
}

bool FourInARow_Board::update_board(int x, int y, char mark) {
    int col = y;
    if (!valid_col(col)) return false;
    int row = get_row(col);
    board[row][col] = mark;
    col_heights[col]++;
    n_moves++;
    return true;
}

bool FourInARow_Board::update_board(Move<char>* move) {
    return update_board(move->get_x(), move->get_y(), move->get_symbol());
}

void FourInARow_Board::display_board() {
    cout << "\n  1   2   3   4   5   6   7\n";
    cout << "-----------------------------\n";
    
    for (int i = 0; i < 6; i++) {
        cout << "|";
        for (int j = 0; j < 7; j++) {
            cout << " " << board[i][j] << " |";
        }
        cout << endl;
        cout << "-----------------------------\n";
    }
    cout << endl;
}

bool FourInARow_Board::is_winner(Player<char>* player) {
    char sym = player->get_symbol();
    
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == sym && board[r][c+1] == sym &&
                board[r][c+2] == sym && board[r][c+3] == sym) return true;
        }
    }
    
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 7; c++) {
            if (board[r][c] == sym && board[r+1][c] == sym &&
                board[r+2][c] == sym && board[r+3][c] == sym) return true;
        }
    }
    
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == sym && board[r+1][c+1] == sym &&
                board[r+2][c+2] == sym && board[r+3][c+3] == sym) return true;
        }
    }
    
    for (int r = 0; r < 3; r++) {
        for (int c = 3; c < 7; c++) {
            if (board[r][c] == sym && board[r+1][c-1] == sym &&
                board[r+2][c-2] == sym && board[r+3][c-3] == sym) return true;
        }
    }
    
    return false;
}

bool FourInARow_Board::is_lose(Player<char>* player) {
    return false;
}

bool FourInARow_Board::is_draw(Player<char>* player) {
    if (n_moves >= 42) return !is_winner(player);
    return false;
}

bool FourInARow_Board::game_is_over(Player<char>* player) {
    return is_winner(player) || is_draw(player);
}

FourInARow_UI::FourInARow_UI() : UI("Four in a Row", 3) {}

Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    int col;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter column (1-7): ";
        while (!(cin >> col) || col < 1 || col > 7) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Bad input. Enter 1-7: ";
        }
        col--;
    } else {
        col = dynamic_cast<FourInARow_ComputerPlayer*>(player)->generate_move()->get_y();
        cout << player->get_name() << " picks column " << (col + 1) << endl;
    }
    
    return new Move<char>(0, col, player->get_symbol());
}

Player<char>* FourInARow_UI::setup_player() {
    return nullptr;
}

Player<char>* FourInARow_UI::create_player(string name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        return new FourInARow_ComputerPlayer(symbol, nullptr);
    }
    return new Player<char>(name, symbol, type);
}

void FourInARow_UI::display_message(string message) {
    cout << message << endl;
}

FourInARow_ComputerPlayer::FourInARow_ComputerPlayer(char symbol, Board<char>* boardPtr)
    : Player<char>("Computer", symbol, PlayerType::COMPUTER) {
    set_board_ptr(boardPtr);
    srand(time(0));
}

Move<char>* FourInARow_ComputerPlayer::generate_move() {
    FourInARow_Board* board = dynamic_cast<FourInARow_Board*>(get_board_ptr());
    vector<int> moves;
    
    for (int c = 0; c < 7; c++) {
        if (board->valid_col(c)) moves.push_back(c);
    }
    
    if (!moves.empty()) {
        int idx = rand() % moves.size();
        return new Move<char>(0, moves[idx], get_symbol());
    }
    
    return new Move<char>(0, 0, get_symbol());
}

void playFourInARow() {
    cout << "\n=== FOUR IN A ROW ===\n\n";
    
    int mode;
    cout << "Choose mode:\n";
    cout << "1. Human vs Human\n";
    cout << "2. Human vs Computer\n";
    cout << "3. Computer vs Computer\n";
    cout << "Choice: ";
    cin >> mode;
    
    PlayerType p1_type = PlayerType::HUMAN;
    PlayerType p2_type = PlayerType::HUMAN;
    
    if (mode == 1) {
        p1_type = PlayerType::HUMAN;
        p2_type = PlayerType::HUMAN;
    } else if (mode == 2) {
        p1_type = PlayerType::HUMAN;
        p2_type = PlayerType::COMPUTER;
    } else if (mode == 3) {
        p1_type = PlayerType::COMPUTER;
        p2_type = PlayerType::COMPUTER;
    } else {
        cout << "Defaulting to Human vs Human\n";
    }
    
    FourInARow_Board* board = new FourInARow_Board();
    FourInARow_UI* ui = new FourInARow_UI();
    
    Player<char>* player1;
    Player<char>* player2;
    
    if (p1_type == PlayerType::HUMAN) {
        player1 = new Player<char>("Player 1", 'X', p1_type);
    } else {
        player1 = new FourInARow_ComputerPlayer('X', board);
    }
    
    if (p2_type == PlayerType::HUMAN) {
        player2 = new Player<char>("Player 2", 'O', p2_type);
    } else {
        player2 = new FourInARow_ComputerPlayer('O', board);
    }
    
    player1->set_board_ptr(board);
    player2->set_board_ptr(board);
    
    Player<char>* players[2] = {player1, player2};
    
    GameManager<char> game(board, players, ui);
    game.run();
    
    delete board;
    delete ui;
    delete player1;
    delete player2;
    
    cout << "\nGame over!\n";
}