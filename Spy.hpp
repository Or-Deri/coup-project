#pragma once
#include <string>
#include "Player.hpp"


namespace coup {
    
    class Spy : public Player {

        private:

        Player* lastBlockedByArrest;

        public:
        
            Spy(Game& game, const std::string& name);

            void startTurn() override;
            void blockArrest(Player& target);
            int seeCoins(Player& target) const;

            
    };
}