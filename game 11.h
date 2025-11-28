#pragma once
#ifndef GAME_11_H
#define GAME_11_H

// ======================
//   STANDARD INCLUDES
// ======================
#include <iostream>
#include <string>
#include <vector>
#include <queue>

//
//=============================================================
//                      GAME11PLAYER CLASS
//=============================================================
//  (Renamed to avoid conflicts with other Player classes)
//=============================================================
//

template <typename T>
class Game11Player {
private:
    std::string name;
    T symbol;

public:
    Game11Player(std::string n, T s) : name(n), symbol(s) {}

    std::string getName() const { return name; }
    T getSymbol() const { return symbol; }
};

//
//=============================================================
//                      INFINITY BOARD
//=============================================================
//

class InfinityBoard {
private:
    std::vector<std::vector<char>> board;
    std::queue<std::pair<int, int>> moveHistory;
    int totalMoves;

public:
    InfinityBoard() {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        totalMoves = 0;
    }

    void display() {
        std::cout << "\n   0   1   2\n";
        for (int i = 0; i < 3; i++) {
            std::cout << i << " ";
            for (int j = 0; j < 3; j++) {
                std::cout << " " << board[i][j] << " ";
                if (j < 2) std::cout << "|";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "  ---+---+---\n";
        }
        std::cout << "Total moves: " << totalMoves
            << " (oldest move disappears every 3 moves)\n";
    }

    bool makeMove(int row, int col, char symbol) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            std::cout << "Position out of bounds!\n";
            return false;
        }
        if (board[row][col] != ' ') {
            std::cout << "Cell already occupied!\n";
            return false;
        }

        board[row][col] = symbol;
        moveHistory.push({ row, col });
        totalMoves++;

        if (totalMoves >= 3 && totalMoves % 3 == 0) {
            removeOldestMove();
        }

        return true;
    }

private:
    void removeOldestMove() {
        if (!moveHistory.empty()) {
            auto old = moveHistory.front();
            moveHistory.pop();
            std::cout << "Oldest move removed at (" << old.first << "," << old.second << ")\n";
            board[old.first][old.second] = ' ';
        }
    }

    bool hasThreeInRow(char symbol) {
        // Rows and columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol &&
                board[i][1] == symbol &&
                board[i][2] == symbol)
                return true;

            if (board[0][i] == symbol &&
                board[1][i] == symbol &&
                board[2][i] == symbol)
                return true;
        }

        // Diagonals
        if (board[0][0] == symbol &&
            board[1][1] == symbol &&
            board[2][2] == symbol)
            return true;

        if (board[0][2] == symbol &&
            board[1][1] == symbol &&
            board[2][0] == symbol)
            return true;

        return false;
    }

public:
    bool isGameOver(char currentPlayer) {
        if (hasThreeInRow(currentPlayer)) {
            std::cout << "Player " << currentPlayer << " wins!\n";
            return true;
        }

        if (totalMoves >= 100) {
            std::cout << "Game ended in a draw!\n";
            return true;
        }

        return false;
    }
};

//
//=============================================================
//                        GAME 11 UI
//=============================================================
//

class Game11UI {
public:
    Game11Player<char>** setup_players() {
        Game11Player<char>** players = new Game11Player<char>*[2];

        std::string n1, n2;
        std::cout << "Enter Player 1 (X) name: ";
        std::cin >> n1;

        std::cout << "Enter Player 2 (O) name: ";
        std::cin >> n2;

        players[0] = new Game11Player<char>(n1, 'X');
        players[1] = new Game11Player<char>(n2, 'O');

        return players;
    }

    void getMove(int& row, int& col, Game11Player<char>* p) {
        std::cout << p->getName() << " (" << p->getSymbol() << ") enter row and column: ";
        std::cin >> row >> col;
    }
};

//
//=============================================================
//                     GAME MANAGER CLASS
//=============================================================
//

template <typename T>
class GameManager {
private:
    InfinityBoard* board;
    Game11Player<T>** players;
    Game11UI* ui;

public:
    //  GameManager(InfinityBoard* b, Game11Player<T>** p, Game11UI* u)
        //  : board(b), players(p), ui(u) {
    //  }
    GameManager(InfinityBoard* b, Game11Player<char>** p, Game11UI* u) {
        // assign to internal variables
    }

    void run();
};

//
//=============================================================
//                       TEMPLATE CODE
//=============================================================
//

template <typename T>
void GameManager<T>::run() {
    int turn = 0;

    while (true) {
        board->display();

        int r, c;
        ui->getMove(r, c, players[turn]);

        if (!board->makeMove(r, c, players[turn]->getSymbol())) {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }

        if (board->isGameOver(players[turn]->getSymbol())) {
            board->display();
            return;
        }

        turn = 1 - turn; // switch players
    }
}

#endif // GAME_11_H