#include "game 11.h"
#include <iostream>

InfinityBoard::InfinityBoard() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    totalMoves = 0;
}

void InfinityBoard::display() {
    std::cout << "\n   0   1   2\n";
    for (int i = 0; i < 3; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 3; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < 2) std::cout << "|";
        }
        std::cout << std::endl;
        if (i < 2) std::cout << "  ---+---+---\n";
    }
    std::cout << "Total moves: " << totalMoves << " (oldest move disappears every 3 moves)\n";
}

bool InfinityBoard::makeMove(int row, int col, char symbol) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        std::cout << "Position out of bounds! Use 0-2 for row and column.\n";
        return false;
    }
    if (board[row][col] != ' ') {
        std::cout << "Cell already occupied! Choose another.\n";
        return false;
    }

    board[row][col] = symbol;
    moveHistory.push({ row, col });
    totalMoves++;

    if (totalMoves >= 3 && totalMoves % 3 == 0) {
        std::cout << "Removing oldest move...\n";
        removeOldestMove();
    }

    return true;
}

void InfinityBoard::removeOldestMove() {
    if (!moveHistory.empty()) {
        auto oldest = moveHistory.front();
        moveHistory.pop();
        std::cout << "Removed " << board[oldest.first][oldest.second] << " from ("
            << oldest.first << "," << oldest.second << ")\n";
        board[oldest.first][oldest.second] = ' ';
    }
}

bool InfinityBoard::hasThreeInRow(char symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }

    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;

    return false;
}

bool InfinityBoard::isGameOver(char currentPlayer) {
    if (hasThreeInRow(currentPlayer)) {
        std::cout << "Player " << currentPlayer << " wins!\n";
        return true;
    }

    if (totalMoves >= 100) {
        std::cout << "Game ended in a draw (maximum moves reached)!\n";
        return true;
    }

    return false;
}