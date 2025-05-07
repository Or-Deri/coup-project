#pragma once
#include <string>
#include "Game.hpp"

namespace coup {

    class Player {
        
        protected:
            int balance = 0;
            std::string name;
            bool inGame = true;
            coup::Game* game;

        public:

            Player(coup::Game* game, const std::string& name);

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
            void sanction(Player& target);
            void coup(Player& target);
        
    };

}