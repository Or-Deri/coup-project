#pragma once
#include <string>
#include "Player.hpp"


class Spy : public Player {

    public:
    
        std::string name() const override{
            return "Spy";
        }

        void ability (Game& game, Player& self, Player* target)override;    

        
}