#include "FourInARow.h"
#include <iostream>
using namespace std;

FourInARow::FourInARow() : Board<char>(6, 7) {
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            board[r][c] = ' ';
}

int FourInARow::get_lowest_empty_row(int col) {
    for (int r = rows - 1; r >= 0; r--) {
        if (board[r][col] == ' ')
            return r;
    }
    return -1;
}

bool FourInARow::update_board(Move<char>* move) {
    int col = move->get_y();
    char symbol = move->get_symbol();

    if (col < 0 || col >= columns) {
        cout << "Invalid column! (0-6 only)\n";
        return false;
    }

    int row = get_lowest_empty_row(col);
    if (row == -1) {
        cout << "Column full! Choose another.\n";
        return false;
    }

    board[row][col] = symbol;
    n_moves++;
    return true;
}

bool FourInARow::check_four(int row, int col, int dr, int dc, char symbol) {
    int count = 0;

    for (int i = -3; i <= 3; i++) {
        int r = row + i * dr;
        int c = col + i * dc;

        if (r >= 0 && r < rows && c >= 0 && c < columns && board[r][c] == symbol) {
            count++;
            if (count == 4) return true;
        } else {
            count = 0;
        }
    }
    return false;
}

bool FourInARow::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            if (board[r][c] == symbol)
                if (check_four(r, c, 0, 1, symbol) ||
                    check_four(r, c, 1, 0, symbol) ||
                    check_four(r, c, 1, 1, symbol) ||
                    check_four(r, c, 1, -1, symbol))
                    return true;

    return false;
}

bool FourInARow::is_draw(Player<char>* player) {
    return n_moves == (rows * columns);
}

bool FourInARow::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void FourInARow::display_board() {
    cout << "\n  0   1   2   3   4   5   6\n";
    cout << "-----------------------------\n";

    for (int r = 0; r < rows; r++) {
        cout << "|";
        for (int c = 0; c < columns; c++) {
            cout << " " << board[r][c] << " |";
        }
        cout << "\n-----------------------------\n";
    }
    cout << endl;
}


void launchConnect4() { 
    
    cout << "\n=== Starting Four-in-a-Row (Connect 4) ===\n";
    cout << "Be the first to connect 4 of your symbols (X or O)!\n\n";

    FourInARow board;

    Player<char> p1("Player 1", 'X', PlayerType::HUMAN);
    Player<char> p2("Player 2", 'O', PlayerType::HUMAN);
    Player<char>* players[2] = { &p1, &p2 };

   
    cout << "   0   1   2   3   4   5   6\n";
    cout << " +---+---+---+---+---+---+---+\n";
    for (int i = 0; i < 6; ++i) {
        cout << " |";
        for (int j = 0; j < 7; ++j) {
            char c = board.get_board_matrix()[i][j];
            cout << " " << (c == ' ' ? '.' : c) << " |";
        }
        cout << "\n +---+---+---+---+---+---+---+\n";
    }
    cout << endl;

    Player<char>* current = &p1;
    bool game_over = false;

    while (!game_over) {
        int col;
        cout << current->get_name() << " (" << current->get_symbol() << "), choose column (0-6): ";
        cin >> col;

        
        while (cin.fail() || col < 0 || col > 6) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid column! Enter a number between 0 and 6: ";
            cin >> col;
        }

        Move<char> move(0, col, current->get_symbol());

        while (!board.update_board(&move)) {
            cout << "Column is full or invalid! Try another: ";
            cin >> col;
            while (cin.fail() || col < 0 || col > 6) {
                cin.clear(); cin.ignore(10000, '\n');
                cout << "Enter valid column (0-6): ";
                cin >> col;
            }
            move = Move<char>(0, col, current->get_symbol());
        }

        
        system("cls"); 
        cout << "\n=== Four-in-a-Row ===\n";
        cout << "   0   1   2   3   4   5   6\n";
        cout << " +---+---+---+---+---+---+---+\n";
        for (int i = 0; i < 6; ++i) {
            cout << " |";
            for (int j = 0; j < 7; ++j) {
                char c = board.get_board_matrix()[i][j];
                cout << " " << (c == ' ' ? '.' : c) << " |";
            }
            cout << "\n +---+---+---+---+---+---+---+\n";
        }
        cout << endl;

        
        if (board.is_win(current)) {
            cout << "Congratulations! " << current->get_name() << " (" << current->get_symbol() << ") WINS!\n";
            game_over = true;
        }
        else if (board.is_draw(current)) {
            cout << "It's a DRAW! No one wins.\n";
            game_over = true;
        }
        else {
           
            current = (current == &p1) ? &p2 : &p1;
        }
    }    
}

