

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <limits>
#include <ctime>


#include "BoardGame_Classes.h"
#include "Numerical.h"
#include "Misere.h"
#include "Tic5x5.h"
#include "SUS.h"
#include "FourInARow.h"
#include "Tic4x4.h"
#include "Obstacles.h"
#include "InfinityGame11.h"
#include "memoryTicTacToe.h"
#include "pyramid.h"
#include "UltimateTicTacToe.h"
#include "Word_TicTacToe.h"
#include "diamond.h"

using namespace std;


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseConsole() {
    cout << "\nPress Enter to return to the Arcade Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


int getValidInt(int min, int max) {
    int choice;
    while (true) {
        if (cin >> choice) {
            if (choice >= min && choice <= max) return choice;
            cout << " > Out of range. Please enter (" << min << "-" << max << "): ";
        } else {
            cout << " > Invalid input. Numbers only: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}




// incomplete
void launchDiamond()  { cout << "\nStarting Diamond Tic-Tac-Toe...\n";  }





struct GameEntry {
    string name;
    void (*startFunction)(); // Function pointer
};

void showWelcomeBanner() {
    cout << "#############################################\n";
    cout << "#           THE  G A M E   A R E N A        #\n";
    cout << "#############################################\n";
    cout << "#  Select a challenge from the list below   #\n";
    cout << "#############################################\n\n";
}

int main() {

    vector<GameEntry> arcade = {
        {"SUS Game",                launchSUS},
        {"Connect 4",               launchConnect4},
        {"5x5 Tic-Tac-Toe",         launchTicTacToe5x5},
        {"Word Tic-Tac-Toe",        launchWordTTT},
        {"Misere Tic-Tac-Toe",      launchMisere},
        {"Diamond Tic-Tac-Toe",     launchDiamond},
        {"4x4 Moving Tic-Tac-Toe",  launchMovingTTT},
        {"Pyramid Tic-Tac-Toe",     launchPyramid},
        {"Numerical Tic-Tac-Toe",   launchNumerical},
        {"Obstacles (6x6)",         launchObstacles},
        {"Infinity Tic-Tac-Toe",    launchInfinity},
        {"Ultimate Tic-Tac-Toe",    launchUltimate},
        {"Memory Tic-Tac-Toe",      launchMemory},
        {"Diamond Tic-Tac-Toe",     launchDiamondTTT}
    };

    bool appRunning = true;
    while (appRunning) {
        clearScreen();
        showWelcomeBanner();

     
        for (size_t i = 0; i < arcade.size(); ++i) {
            
            cout << " [" << (i + 1) << "] " << arcade[i].name << endl;
        }
        cout << " [0] Exit Application\n";
        cout << "\nChoose your game > ";

       
        int choice = getValidInt(0, arcade.size());

        if (choice == 0) {
            appRunning = false;
            cout << "\nExiting... See you next time!\n";
        } else {
            
            clearScreen();
            arcade[choice - 1].startFunction(); 
        
            pauseConsole();
        }
    }

    return 0;
}