#ifndef DIAMOND_H
#define DIAMOND_H

#include <vector>
#include <string>
#include <iostream>

class DiamondBoard {
public:
    static const int N = 5;
    DiamondBoard();
    void reset();
    bool place(int r, int c, char sym);
    void display() const;
    bool full() const;
    bool checkDiamondWin(char sym) const;
private:
    std::vector<std::vector<char>> g;
    bool validCell(int r, int c) const;
    bool inBounds(int r, int c) const;
    int countAlong(int r, int c, int dr, int dc, char sym) const;
};

class Player {
public:
    Player(std::string n = "Player", char s = 'X');
    std::string name() const;
    char sym() const;
private:
    std::string n;
    char s;
};

class GameManager {
public:
    GameManager();
    void run();
private:
    DiamondBoard board;
    Player p1;
    Player p2;
    Player* cur;
    void switchPlayer();
};

#endif // DIAMOND_H