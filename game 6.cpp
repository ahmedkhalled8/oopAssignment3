#include "Diamond.h"
#include <limits>

DiamondBoard::DiamondBoard()
{
    reset();
}

void DiamondBoard::reset()
{
    g.assign(N, std::vector<char>(N, ' '));
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (!validCell(r, c)) g[r][c] = '.';
}

bool DiamondBoard::inBounds(int r, int c) const
{
    return r >= 0 && r < N && c >= 0 && c < N;
}

bool DiamondBoard::validCell(int r, int c) const
{
    int dr = abs(r - 2);
    int dc = abs(c - 2);
    return (dr + dc) <= 2;
}

bool DiamondBoard::place(int r, int c, char sym)
{
    if (!inBounds(r, c)) return false;
    if (!validCell(r, c)) return false;
    if (g[r][c] != ' ') return false;
    g[r][c] = sym;
    return true;
}

void DiamondBoard::display() const
{
    std::cout << "\n   1 2 3 4 5\n";
    for (int r = 0; r < N; ++r) {
        std::cout << r + 1 << "  ";
        for (int c = 0; c < N; ++c) {
            std::cout << g[r][c];
            if (c < N - 1) std::cout << ' ';
        }
        std::cout << "\n";
    }
}

bool DiamondBoard::full() const
{
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            if (validCell(r, c) && g[r][c] == ' ') return false;
    return true;
}

int DiamondBoard::countAlong(int r, int c, int dr, int dc, char sym) const
{
    int cnt = 0;
    int rr = r;
    int cc = c;
    while (inBounds(rr, cc) && validCell(rr, cc) && g[rr][cc] == sym) {
        ++cnt;
        rr += dr;
        cc += dc;
    }
    return cnt;
}

bool DiamondBoard::checkDiamondWin(char sym) const
{
    bool dirHas3[4] = {false,false,false,false};
    bool dirHas4[4] = {false,false,false,false};
    int dirs[4][2] = {{0,1},{1,0},{1,1},{-1,1}};
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (!validCell(r,c)) continue;
            if (g[r][c] != sym) continue;
            for (int d = 0; d < 4; ++d) {
                int dr = dirs[d][0], dc = dirs[d][1];
                int cnt = countAlong(r, c, dr, dc, sym);
                if (cnt >= 3) dirHas3[d] = true;
                if (cnt >= 4) dirHas4[d] = true;
            }
        }
    }
    for (int d3 = 0; d3 < 4; ++d3)
        for (int d4 = 0; d4 < 4; ++d4)
            if (d3 != d4 && dirHas3[d3] && dirHas4[d4]) return true;
    return false;
}

Player::Player(std::string n0, char s0)
    : n(std::move(n0)), s(s0) {}

std::string Player::name() const { return n; }
char Player::sym() const { return s; }

GameManager::GameManager()
    : p1("Player 1", 'X'), p2("Player 2", 'O'), cur(&p1)
{
    board.reset();
}

void GameManager::switchPlayer()
{
    if (cur == &p1) cur = &p2; else cur = &p1;
}

void GameManager::run()
{
    std::cout << "Diamond Tic-Tac-Toe\n";
    std::string tmp;
    std::cout << "Enter name for Player 1 (or Enter): ";
    std::getline(std::cin, tmp);
    if (!tmp.empty()) p1 = Player(tmp, 'X');
    std::cout << "Enter name for Player 2 (or Enter): ";
    std::getline(std::cin, tmp);
    if (!tmp.empty()) p2 = Player(tmp, 'O');
    cur = &p1;
    board.display();
    while (true) {
        std::cout << "\n" << cur->name() << " (" << cur->sym() << ") choose row and col (e.g. 2 3): ";
        int r, c;
        while (true) {
            if (!(std::cin >> r >> c)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter two numbers row col: ";
                continue;
            }
            r -= 1; c -= 1;
            if (!board.place(r, c, cur->sym())) {
                std::cout << "Invalid cell or occupied. Try again: ";
                continue;
            }
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        board.display();
        if (board.checkDiamondWin(cur->sym())) {
            std::cout << "\n" << cur->name() << " wins!\n";
            break;
        }
        if (board.full()) {
            std::cout << "\nDraw. Board full.\n";
            break;
        }
        switchPlayer();
    }
    std::cout << "Game over\n";
}

int main()
{
    GameManager gm;
    gm.run();
    return 0;
}