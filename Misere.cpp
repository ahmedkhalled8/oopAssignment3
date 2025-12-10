#include "Misere.h"
#include <iostream>
#include <random>
#include <limits>
#include <algorithm>

using namespace std;



MisereBoard::MisereBoard() : Board<char>(3, 3) {
    
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = ' ';
    n_moves = 0;
}

bool MisereBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Move out of bounds. Try again.\n";
        return false;
    }
    if (board[x][y] != ' ') {
        cout << "Cell already occupied. Try again.\n";
        return false;
    }

    board[x][y] = s;
    ++n_moves;
    return true;
}

bool MisereBoard::is_win(Player<char>* player) {
    // In Misère rules, you don't "win" by making three-in-row.
    // For compatibility with GameManager we return true if the opponent
    // currently has three-in-row (meaning current player effectively wins).
    char opp = opposite_symbol(player->get_symbol());
    return has_three_in_row(opp);
}

bool MisereBoard::is_lose(Player<char>* player) {
    // Player loses if they have three-in-row of their own symbol
    return has_three_in_row(player->get_symbol());
}

bool MisereBoard::is_draw(Player<char>* /*player*/) {
    if (n_moves < rows * columns) return false;
    // draw only when full board and nobody has 3-in-row
    return !has_three_in_row('X') && !has_three_in_row('O');
}

bool MisereBoard::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player) || is_win(player);
}

bool MisereBoard::has_three_in_row(char s) const {
    // rows
    for (int i = 0; i < rows; ++i)
        if (board[i][0] == s && board[i][1] == s && board[i][2] == s)
            return true;

    // columns
    for (int j = 0; j < columns; ++j)
        if (board[0][j] == s && board[1][j] == s && board[2][j] == s)
            return true;

    // diagonals
    if (board[0][0] == s && board[1][1] == s && board[2][2] == s) return true;
    if (board[0][2] == s && board[1][1] == s && board[2][0] == s) return true;

    return false;
}

char MisereBoard::opposite_symbol(char s) const {
    return (s == 'X') ? 'O' : 'X';
}

//////////////////////////////////////////////////////
// MisereUI implementation
//////////////////////////////////////////////////////

MisereUI::MisereUI() : UI<char>(" Avoid making 3-in-a-row.", 3) {}

Player<char>* MisereUI::create_player(string& name, char symbol, PlayerType type) {
    // simply create a Player instance (UI::setup_players will call this)
    return new Player<char>(name, symbol, type);
}

Move<char>* MisereUI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER)
        return get_computer_move(player);
    return get_human_move(player);
}

bool MisereUI::read_int(int &out) {
    // read one integer and ensure no trailing junk on the same line
    while (true) {
        if (!(cin >> out)) {
            cout << "Invalid number. Try again: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // allow trailing whitespace/newline, but if there's other characters it's okay
        return true;
    }
}

Move<char>* MisereUI::get_human_move(Player<char>* player) {
    int x, y;
    cout << player->get_name() << " (" << player->get_symbol() << ") - enter row and column (e.g. 0 2): ";
    while (true) {
        if (!(cin >> x >> y)) {
            cout << "Invalid input. Enter two integers (row col): ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // return move; GameManager -> update_board validates position and occupancy
        return new Move<char>(x, y, player->get_symbol());
    }
}

Move<char>* MisereUI::get_computer_move(Player<char>* player) {
    Board<char>* bp = player->get_board_ptr();
    MisereBoard* mb = dynamic_cast<MisereBoard*>(bp);
    if (!mb) {
        // fallback: random empty
        return random_empty_move(player);
    }

    vector<pair<int,int>> empties;
    auto mat = mb->get_board_matrix();
    for (int i = 0; i < mb->get_rows(); ++i)
        for (int j = 0; j < mb->get_columns(); ++j)
            if (mat[i][j] == ' ')
                empties.emplace_back(i, j);

    char s = player->get_symbol();

    // try moves that do NOT produce three-in-row for the computer (avoid immediate loss)
    vector<pair<int,int>> safe_moves;
    for (auto &p : empties) {
        int r = p.first, c = p.second;
        auto sim = mb->get_board_matrix();
        sim[r][c] = s;
        if (!three_in_row_in_matrix(sim, s)) {
            safe_moves.emplace_back(r, c);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    pair<int,int> choice;
    if (!safe_moves.empty()) {
        std::uniform_int_distribution<> dist(0, (int)safe_moves.size() - 1);
        choice = safe_moves[dist(gen)];
    } else if (!empties.empty()) {
        // no safe moves — pick random (will cause immediate loss)
        std::uniform_int_distribution<> dist(0, (int)empties.size() - 1);
        choice = empties[dist(gen)];
    } else {
        // board full (shouldn't happen because game ends earlier)
        return new Move<char>(0,0,s);
    }

    cout << "Computer (" << s << ") moves at " << choice.first << ", " << choice.second << "\n";
    return new Move<char>(choice.first, choice.second, s);
}

Move<char>* MisereUI::random_empty_move(Player<char>* player) {
    Board<char>* bp = player->get_board_ptr();
    auto mat = bp->get_board_matrix();
    vector<pair<int,int>> empties;
    for (int i = 0; i < (int)mat.size(); ++i)
        for (int j = 0; j < (int)mat[0].size(); ++j)
            if (mat[i][j] == ' ')
                empties.emplace_back(i,j);

    if (empties.empty()) return new Move<char>(0,0,player->get_symbol());
    std::random_device rd; std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, (int)empties.size() - 1);
    auto p = empties[dist(gen)];
    cout << "Computer (" << player->get_symbol() << ") moves at " << p.first << ", " << p.second << "\n";
    return new Move<char>(p.first, p.second, player->get_symbol());
}

bool MisereUI::three_in_row_in_matrix(const vector<vector<char>>& mat, char s) const {
    int n = (int)mat.size();
    if (n == 0) return false;
    int m = (int)mat[0].size();

    // rows
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int j = 0; j < m; ++j) if (mat[i][j] != s) { ok = false; break; }
        if (ok) return true;
    }
    // cols
    for (int j = 0; j < m; ++j) {
        bool ok = true;
        for (int i = 0; i < n; ++i) if (mat[i][j] != s) { ok = false; break; }
        if (ok) return true;
    }
    // diag left-to-right
    bool ok = true;
    for (int i = 0; i < n; ++i) if (mat[i][i] != s) { ok = false; break; }
    if (ok) return true;
    // diag right-to-left
    ok = true;
    for (int i = 0; i < n; ++i) if (mat[i][n - 1 - i] != s) { ok = false; break; }
    if (ok) return true;

    return false;
}

void launchMisere()   {

    cout << "\nStarting Misere Tic-Tac-Toe...\n";
    MisereUI ui;
    MisereBoard board;
    Player<char>** players = ui.setup_players();
    GameManager<char> manager(&board, players, &ui);
    manager.run();
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
    
}