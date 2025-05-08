#pragma once
#include <string>
#include "Game.hpp"

namespace coup {

    class Game;

    class Player {
        
        protected:
            int balance;
            std::string name;
            bool inGame;
            Game* game;
    

        public:

            Player( Game& game, const std::string& name);

            std::string getName() const;
            int coins() const;
            void addCoins(int x);
            void subCoins(int x);
            
            bool isInGame() const;
            void lost();
            virtual void startTurn();


            void gather();
            virtual void tax();
            void bribe();
            void arrest(Player& target);
            void sanction(Player& target);
            void coup(Player& target);
        
    };

}