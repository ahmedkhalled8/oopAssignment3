// SUS_Classes.cpp
#include "SUS.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

SUS_Board::SUS_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

int SUS_Board::count_SUS_including_cell(int x, int y) const {
    int cnt = 0;
    // horizontal (same row - varying columns)
    for (int s = y - 2; s <= y; s++) {
        if (s >= 0 && s + 2 < 3) {
            if (board[x][s] == 'S' && board[x][s + 1] == 'U' && board[x][s + 2] == 'S')
                if (y >= s && y <= s + 2) cnt++;
        }
    }
    // vertical (same column - varying rows)
    for (int s = x - 2; s <= x; s++) {
        if (s >= 0 && s + 2 < 3) {
            if (board[s][y] == 'S' && board[s + 1][y] == 'U' && board[s + 2][y] == 'S')
                if (x >= s && x <= s + 2) cnt++;
        }
    }
    // diagonal top-left -> bottom-right
    for (int d = -2; d <= 0; d++) {
        int sx = x + d, sy = y + d;
        if (sx >= 0 && sx + 2 < 3 && sy >= 0 && sy + 2 < 3) {
            if (board[sx][sy] == 'S' && board[sx + 1][sy + 1] == 'U' && board[sx + 2][sy + 2] == 'S')
                if ((x == sx && y == sy) || (x == sx+1 && y == sy+1) || (x == sx+2 && y == sy+2)) cnt++;
        }
    }
    // diagonal bottom-left -> top-right
    for (int d = -2; d <= 0; d++) {
        int sx = x + d, sy = y - d;
        if (sx >= 0 && sx + 2 < 3 && sy < 3 && sy - 2 >= 0) {
            if (board[sx][sy] == 'S' && board[sx + 1][sy - 1] == 'U' && board[sx + 2][sy - 2] == 'S') {
                if ((x == sx && y == sy) ||
                    (x == sx + 1 && y == sy - 1) ||
                    (x == sx + 2 && y == sy - 2))
                    cnt++;
            }
        }
    }
    return cnt;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char v = move->get_symbol();
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (v != 'S' && v != 'U') return false;
    if (board[x][y] != blank_symbol) return false;
    int playerIndex = (n_moves % 2 == 0 ? 0 : 1);
    board[x][y] = v;
    int add = count_SUS_including_cell(x, y);
    if (playerIndex == 0) score1 += add;
    else score2 += add;
    n_moves++;
    return true;
}

bool SUS_Board::is_win(Player<char>* player) {
    if (n_moves < 9) return false;
    char sym = player->get_symbol();
    int idx = (sym == 'X' ? 0 : 1);
    if (idx == 0) return score1 > score2;
    else return score2 > score1;
}

bool SUS_Board::is_lose(Player<char>* player) {
    if (n_moves < 9) return false;
    char sym = player->get_symbol();
    int idx = (sym == 'X' ? 0 : 1);
    if (idx == 0) return score2 > score1;
    else return score1 > score2;
}

bool SUS_Board::is_draw(Player<char>* /*player*/) {
    return (n_moves == 9 && score1 == score2);
}

bool SUS_Board::game_is_over(Player<char>* /*player*/) {
    return (n_moves == 9);
}

SUS_Player::SUS_Player(std::string name, char symbol, PlayerType type, char fixed)
    : Player<char>(name, symbol, type), fixed_letter(fixed) {}

char SUS_Player::get_fixed_letter() const { return fixed_letter; }
void SUS_Player::set_fixed_letter(char c) { fixed_letter = c; }

SUS_UI::SUS_UI() : UI<char>("Welcome to SUS Game!", 3) {}

Player<char>* SUS_UI::create_player(std::string& name, char symbol, PlayerType type) {
    static int count = 0;       // to know which player is being created
    static char p1_letter = 0;  // stored letter of player 1

    ++count;

    if (count == 1) {
        // Player 1 chooses S or U
        char fixed;
        do {
            cout << "Player 1, choose your letter (S/U): ";
            cin >> fixed;
            fixed = toupper(static_cast<unsigned char>(fixed));
            // clear rest of line so subsequent reads don't get junk
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (fixed != 'S' && fixed != 'U');

        p1_letter = fixed;
        return new SUS_Player(name, symbol, type, fixed);
    }

    // Player 2 always gets the remaining letter
    char fixed = (p1_letter == 'S' ? 'U' : 'S');
    cout << "Player 2 will use: " << fixed << "\n";
    return new SUS_Player(name, symbol, type, fixed);
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x = 0, y = 0;
    SUS_Player* sp = dynamic_cast<SUS_Player*>(player);
    char c = sp ? sp->get_fixed_letter() : 'S';
    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << "Enter x y (0-2): ";
            if (cin >> x >> y && x >= 0 && x < 3 && y >= 0 && y < 3) {
                // consume rest of line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid coordinates. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } else {
        vector<vector<char>> m = player->get_board_ptr()->get_board_matrix();
        vector<pair<int,int>> empty;
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                if (m[i][j] == '.') empty.push_back({i,j});
        if (empty.empty()) { x = rand()%3; y = rand()%3; }
        else {
            auto p = empty[rand() % empty.size()];
            x = p.first;
            y = p.second;
        }
        cout << "Computer plays " << c << " at (" << x << "," << y << ")\n";
    }
    return new Move<char>(x, y, c);
}


void launchSUS() { 
    cout << "\n=== SUS GAME ===\n";
    srand(static_cast<unsigned int>(time(0)));
    UI<char>* ui = new SUS_UI();
    Board<char>* board = new SUS_Board();
    Player<char>** players = ui->setup_players();
    GameManager<char> sus_game(board, players, ui);
    sus_game.run();
    
    
    delete board; delete ui;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
 
}