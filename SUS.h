
#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <vector>


class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.'; 
    int score1 = 0;          
    int score2 = 0;          

public:
    
    SUS_Board();

   
    bool update_board(Move<char>* move) override;

   
    bool is_win(Player<char>* player) override;

   
    bool is_lose(Player<char>* player) override;

    
    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;

    int count_SUS_including_cell(int x, int y) const;
};

class SUS_Player : public Player<char> {
private:
    char fixed_letter;

public:
    
    SUS_Player(std::string name, char symbol, PlayerType type, char fixed);


    char get_fixed_letter() const;

  
    void set_fixed_letter(char c);
};


class SUS_UI : public UI<char> {
public:
    SUS_UI();

    
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

  
    Move<char>* get_move(Player<char>* player) override;
};
void launchSUS();
#endif
