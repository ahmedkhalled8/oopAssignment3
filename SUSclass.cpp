#include "SUSclass.h"
#include <iostream>
#include <string>

SUSBoard::SUSBoard() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    xScore = 0;
    oScore = 0;
}

void SUSBoard::display() {
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
    std::cout << "Scores - X: " << xScore << " | O: " << oScore << std::endl;
}

bool SUSBoard::makeMove(int row, int col, char player, char letter) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        std::cout << "Position out of bounds! Use 0-2 for row and column.\n";
        return false;
    }
    if (board[row][col] != ' ') {
        std::cout << "Cell already occupied! Choose another.\n";
        return false;
    }
    if (letter != 'S' && letter != 'U') {
        std::cout << "Invalid letter! You can only place 'S' or 'U'.\n";
        return false;
    }

    board[row][col] = letter;
    updateScores(player);
    return true;
}

void SUSBoard::updateScores(char player) {
    int oldXScore = xScore;
    int oldOScore = oScore;
    xScore = 0;
    oScore = 0;

    std::vector<std::string> sequences;

    for (int i = 0; i < 3; i++) {
        std::string row = "";
        std::string col = "";
        for (int j = 0; j < 3; j++) {
            row += board[i][j];
            col += board[j][i];
        }
        sequences.push_back(row);
        sequences.push_back(col);
    }

    std::string diag1 = "";
    std::string diag2 = "";
    for (int i = 0; i < 3; i++) {
        diag1 += board[i][i];
        diag2 += board[i][2 - i];
    }
    sequences.push_back(diag1);
    sequences.push_back(diag2);

    for (const auto& seq : sequences) {
        if (seq.find("SUS") != std::string::npos) {
            int susCount = countSUS(seq);
            if (player == 'X') {
                xScore += susCount;
            }
            else {
                oScore += susCount;
            }
        }
    }

    if (xScore > oldXScore) {
        std::cout << "Player X found " << (xScore - oldXScore) << " new SUS sequence(s)!\n";
    }
    if (oScore > oldOScore) {
        std::cout << "Player O found " << (oScore - oldOScore) << " new SUS sequence(s)!\n";
    }
}

int SUSBoard::countSUS(const std::string& sequence) {
    int count = 0;
    for (size_t i = 0; i <= sequence.length() - 3; i++) {
        if (sequence.substr(i, 3) == "SUS") {
            count++;
        }
    }
    return count;
}

bool SUSBoard::isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void SUSBoard::declareWinner() {
    std::cout << "\n=== FINAL SCORES ===\n";
    std::cout << "Player X: " << xScore << " SUS sequences\n";
    std::cout << "Player O: " << oScore << " SUS sequences\n";

    if (xScore > oScore) {
        std::cout << "Player X WINS!\n";
    }
    else if (oScore > xScore) {
        std::cout << "Player O WINS!\n";
    }
    else {
        std::cout << "It's a TIE!\n";
    }
}