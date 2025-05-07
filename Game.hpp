#pragma once
#include "Player.hpp"
#include <vector>
#include <string>

namespace coup {
    class Player;
    class Game{
        
        private:
            
            std::vector <Player*> PlayersList;
            int PlayerTurn;

        public:
        
            Game();
            void addPlayer(Player* player);
            Player* currentPlayer();
            void nextTurn();
            void turn() const;
            std::vector <std::string> players() const;
            std::string winner() const;
            int playersInTheGame() const;
            

    };
}