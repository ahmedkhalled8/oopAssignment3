// Word_TicTacToe.cpp
#include "Word_TicTacToe.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
using namespace std;

WordBoard::WordBoard() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' ';
    load_dictionary();
}

void WordBoard::load_dictionary() {
    ifstream file("dic.txt");
    if (!file) {
        cout << "WARNING: dic.txt not found! Loading built-in words...\n";
        string backup[] = { "CAT","DOG","BAT","RAT","FUN","WIN","GOD","YES","ZOO","ANT","FOX","COW","PIG","SUN","CAR","HAT","BAG","TOP","NET" };
        for (auto& w : backup) dictionary.insert(w);
        return;
    }
    string word;
    while (file >> word) {
        if (word.length() == 3) {
            for (char& c : word) c = toupper(c);
            dictionary.insert(word);
        }
    }
    file.close();
    cout << "Loaded " << dictionary.size() << " three-letter words.\n";
}

bool WordBoard::is_valid_word(const string& w) const {
    return dictionary.count(w);
}

bool WordBoard::check_any_word() const {
    string w;
    // Rows
    for (int i = 0; i < 3; ++i) {
        w = board[i][0]; w += board[i][1]; w += board[i][2];
        if (w.find(' ') == string::npos && is_valid_word(w)) return true;
    }
    // Columns
    for (int j = 0; j < 3; ++j) {
        w = board[0][j]; w += board[1][j]; w += board[2][j];
        if (w.find(' ') == string::npos && is_valid_word(w)) return true;
    }
    // Diagonals
    w = board[0][0]; w += board[1][1]; w += board[2][2];
    if (w.find(' ') == string::npos && is_valid_word(w)) return true;
    w = board[0][2]; w += board[1][1]; w += board[2][0];
    if (w.find(' ') == string::npos && is_valid_word(w)) return true;

    return false;
}

bool WordBoard::update_board(Move<char>* move) {
    int x = move->get_x(), y = move->get_y();
    char c = toupper(move->get_symbol());

    if (x < 0 || x > 2 || y < 0 || y > 2 || !isalpha(c) || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = c;
    n_moves++;
    return true;
}

bool WordBoard::is_win(Player<char>* player) {
    return check_any_word();
}

bool WordBoard::is_draw(Player<char>* player) {
    return n_moves == 9 && !check_any_word();
}

bool WordBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ===================== UI =====================
WordUI::WordUI() : UI<char>("\n=== WORD TIC-TAC-TOE ===\nForm a valid 3-letter English word to win!\n", 3) {}

Player<char>* WordUI::create_player(string& name, char symbol, PlayerType type) {
    return new WordPlayer(name, '-', type);
}

Player<char>** WordUI::setup_players() {
    Player<char>** p = new Player<char>*[2];
    string n1, n2;
    cout << "Enter Player 1 name: ";
    getline(cin >> ws, n1);
    cout << "Enter Player 2 name: ";
    getline(cin, n2);
    p[0] = new WordPlayer(n1, '-', PlayerType::HUMAN);
    p[1] = new WordPlayer(n2, '-', PlayerType::HUMAN);
    return p;
}

Move<char>* WordUI::get_move(Player<char>* player) {
    char letter;
    int x, y;
    while (true) {
        cout << "\n" << player->get_name() << ", your turn!\n";
        cout << "Enter letter (A-Z): ";
        cin >> letter;
        letter = toupper(letter);
        if (letter < 'A' || letter > 'Z') {
            cout << "Invalid letter! Try again.\n";
            continue;
        }
        cout << "Enter row (0-2): ";
        cin >> x;
        cout << "Enter column (0-2): ";
        cin >> y;

        if (cin.fail() || x < 0 || x > 2 || y < 0 || y > 2) {
            cout << "Invalid position!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        return new WordMove(x, y, letter);
    }
}

void WordUI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n   0   1   2\n";
    cout << "  +---+---+---+\n";
    for (int i = 0; i < 3; ++i) {
        cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            char c = matrix[i][j];
            cout << "| " << (c == ' ' ? ' ' : c) << " ";
        }
        cout << "|\n  +---+---+---+\n";
    }
    cout << endl;
}

void launchWordTTT()  {
    cout << "\n=== WORD TIC-TAC-TOE ===\n";
    cout << "First to form a valid 3-letter English word (row, column, or diagonal) WINS!\n\n";

    WordBoard* board = new WordBoard();
    WordUI* ui = new WordUI();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

  
    delete board;
    delete ui;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
}