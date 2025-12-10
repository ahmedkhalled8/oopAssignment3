#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>


class ObstaclesBoard : public Board<char> {
private:
  
    const char OBSTACLE = '#';

public:
    ObstaclesBoard();

    
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool is_lose(Player<char>* p) override; 
    bool game_is_over(Player<char>* p) override;

    
    void add_two_obstacles();
};


class ObstaclesUI : public UI<char> {
public:
    ObstaclesUI();


    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

void launchObstacles();