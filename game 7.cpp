#include "game 7.h"
#include <iostream>
#include <cmath>

FourByFourBoard::FourByFourBoard() {
    board = std::vector<std::vector<char>>(4, std::vector<char>(4, ' '));
    moveCount = 0;

    xPositions = { {0,0}, {0,2}, {3,1}, {3,3} };
    oPositions = { {0,1}, {0,3}, {3,0}, {3,2} };

    for (auto pos : xPositions) board[pos.first][pos.second] = 'X';
    for (auto pos : oPositions) board[pos.first][pos.second] = 'O';
}

void FourByFourBoard::display() {
    std::cout << "\n   0   1   2   3\n";
    for (int i = 0; i < 4; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 4; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < 3) std::cout << "|";
        }
        std::cout << std::endl;
        if (i < 3) std::cout << "  ---+---+---+---\n";
    }
    std::cout << "Moves: " << moveCount << std::endl;
}

bool FourByFourBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol, char player) {
    if (fromRow < 0 || fromRow >= 4 || fromCol < 0 || fromCol >= 4) {
        std::cout << "Source position out of bounds!\n";
        return false;
    }
    if (toRow < 0 || toRow >= 4 || toCol < 0 || toCol >= 4) {
        std::cout << "Target position out of bounds!\n";
        return false;
    }

    if (board[fromRow][fromCol] != player) {
        std::cout << "You don't have a piece at that position!\n";
        return false;
    }
    if (board[toRow][toCol] != ' ') {
        std::cout << "Target cell is not empty!\n";
        return false;
    }

    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toCol - fromCol);

    if ((rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1)) {
        return true;
    }

    std::cout << "You can only move to adjacent cells (up, down, left, right)!\n";
    return false;
}

bool FourByFourBoard::makeMove(int fromRow, int fromCol, int toRow, int toCol, char player) {
    if (!isValidMove(fromRow, fromCol, toRow, toCol, player)) {
        return false;
    }

    board[fromRow][fromCol] = ' ';
    board[toRow][toCol] = player;

    if (player == 'X') {
        for (auto& pos : xPositions) {
            if (pos.first == fromRow && pos.second == fromCol) {
                pos.first = toRow;
                pos.second = toCol;
                break;
            }
        }
    }
    else {
        for (auto& pos : oPositions) {
            if (pos.first == fromRow && pos.second == fromCol) {
                pos.first = toRow;
                pos.second = toCol;
                break;
            }
        }
    }

    moveCount++;
    return true;
}

bool FourByFourBoard::hasThreeInRow(char player) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player) return true;
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player) return true;
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player) return true;
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 2; j < 4; j++) {
            if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player) return true;
        }
    }

    return false;
}

bool FourByFourBoard::isGameOver(char currentPlayer) {
    if (hasThreeInRow(currentPlayer)) {
        std::cout << "Player " << currentPlayer << " wins!\n";
        return true;
    }

    if (moveCount >= 50) {
        std::cout << "Game ended in a draw (too many moves)!\n";
        return true;
    }

    return false;
}