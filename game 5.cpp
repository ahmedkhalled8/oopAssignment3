#include "game 5.h"
#include <iostream>

MisereBoard::MisereBoard() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    moveCount = 0;
}

void MisereBoard::display() {
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
    std::cout << std::endl;
}

bool MisereBoard::makeMove(int row, int col, char symbol) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        std::cout << "Position out of bounds! Use 0-2 for row and column.\n";
        return false;
    }
    if (board[row][col] != ' ') {
        std::cout << "Cell already occupied! Choose another.\n";
        return false;
    }

    board[row][col] = symbol;
    moveCount++;
    return true;
}

bool MisereBoard::hasThreeInRow(char symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }

    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;

    return false;
}

bool MisereBoard::isGameOver(char currentPlayer) {
    if (hasThreeInRow(currentPlayer)) {
        char winner = (currentPlayer == 'X') ? 'O' : 'X';
        std::cout << "Player " << currentPlayer << " made three in a row! Player " << winner << " wins!\n";
        return true;
    }

    if (moveCount == 9) {
        std::cout << "Game ended in a draw!\n";
        return true;
    }

    return false;
}